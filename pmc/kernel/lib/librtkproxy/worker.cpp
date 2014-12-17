#include "precomp.h"
#pragma hdrstop

#include <algorithm>
#include <time.h>

#if 0
#define WORKER_DEBUG(x) DEBUG_PRINTF(x)
#else
#define WORKER_DEBUG(x) utils_debug x
#endif

/* convert time_t to string */
/* use the "YYYY/MM/DD hh:mm:ss" format */

static char *strtime (time_t *t)
{
	struct tm	*local;
	static char result[32];

	local = localtime(t);
	sprintf(result,"%4d/%02d/%02d %02d:%02d:%02d",
		  local->tm_year+1900, local->tm_mon+1, local->tm_mday,
		  local->tm_hour, local->tm_min, local->tm_sec);
	return result;
}

static char * now()
{
	time_t t;
	time(&t);
	return strtime(&t);
}

__uint CProxyWorker::m_MaxBgLoads;

bool operator ==(const struct task_item_t & a, const struct task_item_t & b)
{
	return a.tag == b.tag;
}

/*
	determine if a loading requesting is pending
	environment : db lock held 
*/
__bool CProxyWorker::is_loading(PCTAG_NAME n)
{
#if 1
	CWaitingList::reverse_iterator p;
	task_item_t key;
	key.tag = *n;
	p = find(m_Tasks.rbegin(), m_Tasks.rend(), key);
	return p == m_Tasks.rend()? __false : __true;
#else
	WORKER_DEBUG((
		">>T%08x, %d, checking: '%s.%s.%s'\n",
		id(),
		m_Tasks.size(),
		(char*)CNodeName(n->node),
		(char*)CGroupName(n->sname.group),
		(char*)CTagName(n->sname.tag)
		));

	CWaitingList::iterator p;
	task_item_t key;
	key.tag = *n;
	p = m_Tasks.begin();
	for(int i=m_Tasks.size(); i; i--, p++){
		if(*p == key){
			return __true;
		}
	}
	return __false;
#endif
}

/*
	....
	cancel_load : remove an entry from the loading list
	Parameters:
	...
	Environment :
	database unlocked.
*/
__bool CProxyWorker::cancel_load(PCTAG_NAME tk)
{
	bool ret = __false;
	CWaitingList::iterator p;
	
	if(!lock_rtdb(__true, 1000)){
		return __false;
	}
	task_item_t key;
	key.tag = *tk;
	p = find(m_Tasks.begin(), m_Tasks.end(), key);
	if(p != m_Tasks.end()){
		m_Tasks.erase(p);
		ret = __true;
	}
	unlock_rtdb();

	if(ret){
		WORKER_DEBUG((
			">>T%08x, task cancelled: '%s.%s.%s'\n",
			id(),
			(char*)CNodeName(tk->node),
			(char*)CGroupName(tk->sname.group),
			(char*)CTagName(tk->sname.tag)
			));
	}

	return ret;
}

/*
	....
	Environment :
	database unlocked.
*/
__bool CProxyWorker::inform_load(PCTAG_NAME jobs, __uint count, bool bForce)
{
	__uint		i;
	TAG_NAME	tk;
	PCTAG_NAME	j;
	task_item_t task;

	if(!lock_rtdb(__true, 1000)){
		return __false;
	}

	if(m_Tasks.size() > m_MaxBgLoads){
		unlock_rtdb();
		return __false;
	}
	
	for(i=0, j=jobs; i<count; i++, j++){
		memset(&tk, 0, sizeof(TAG_NAME));
		if(!bForce){
			tk.node = j->node;
			// check if pertaining node is being loaded
			if(is_loading(&tk)){
				continue;
			}
			// check if pertaining group is being loaded
			if(j->sname.group.Data[0]){
				tk.sname.group = j->sname.group;
				if(is_loading(&tk)){
					continue;
				}
				// check if already being loaded
				if(j->sname.tag.Data[0]){
					tk.sname.tag = j->sname.tag;
					if(is_loading(&tk)){
						continue;
					}
				}
			}else{
			}
		}else{
			tk = *j;
		}
		WORKER_DEBUG((
			">>T%08x, %d, inform loading: '%s.%s.%s'\n",
			id(),
			m_Tasks.size(),
			(char*)CNodeName(tk.node),
			(char*)CGroupName(tk.sname.group),
			(char*)CTagName(tk.sname.tag)
			));
		task.tag = tk;
		task.failCount = 0;
		m_Tasks.insert(m_Tasks.end(), task);
	}

	unlock_rtdb();
	
	return __true;
}

__bool CProxyWorker::load_node(PNODE_KEY nk)
{
	RTK_CURSOR hNode;

	if(!nk){
		return __false;
	}

	WORKER_DEBUG((
		">>BGLoader, %d, loading node '%s'\n",
		m_Tasks.size(),
		(char*)CNodeName(*nk)
		));

	if(!lock_rtdb(__true, 2000)){
		return __false;
	}
	hNode = create_node(nk, 0);
	close_handle(hNode);
	unlock_rtdb();
	if(!hNode){
		return __false;
	}

	discover_groups_ex(nk, 3000, NULL, __false);
	
	RTK_CURSOR hGroup;
	PRTK_GROUP pGroup;
	int i, count;
	PTAG_NAME pNames = 0;

	if(!lock_rtdb(__false, 2000)){
		return __false;
	}
	hNode = open_node(nk);
	if(hNode){
		count = cursor_get_subitem_count(hNode);
		pNames = new TAG_NAME[count];
		memset(pNames, 0, sizeof(TAG_NAME) * count);
		i = 0;
		if(pNames){
			hGroup = cursor_open_first_subitem(hNode);
			while(!cursor_is_end(hGroup)){
				pGroup = (PRTK_GROUP)cursor_get_item(hGroup);
				pNames[i].node = *nk;
				pNames[i].sname.group = pGroup->key;
				cursor_move_next(hGroup);
				i++;
			}
			close_handle(hGroup);
			assert(i == count);
		}
		close_handle(hNode);
	}
	unlock_rtdb();
	if(pNames){
		inform_load(pNames, count, true);
		delete pNames;
	}

	return __true;
}

__bool CProxyWorker::load_group(PRTK_GROUP_NAME gn)
{
	__bool ret = __false;
	
	if(!gn){
		return __false;
	}

	WORKER_DEBUG((
		">>BGLoader, %d, loading group '%s.%s'\n",
		m_Tasks.size(),
		(char*)CNodeName(gn->node),
		(char*)CGroupName(gn->group)
		));
	ret = discover_tags_ex(&gn->node, &gn->group, 5000, NULL, __false);

	return ret;
}

__bool CProxyWorker::load_tag(PCTAG_NAME n)
{
	WORKER_DEBUG((
		">>BGLoader, %d, loading tag : '%s.%s.%s'\n",
		m_Tasks.size(),
		(char*)CNodeName(n->node),
		(char*)CGroupName(n->sname.group),
		(char*)CTagName(n->sname.tag)
		));
	reload_tags(1, n, 1000);
	return __true;
}

void CProxyWorker::do_load()
{
	CWaitingList::iterator p;
	task_item_t task;
	__bool ret;

	if(!(m_TaskFlag & PROXY_ENABLE_BGLOADER)){
		return;
	}
	while(true){
		kill_nodes();

		if(!lock_rtdb(__false, 1000)){
			break;
		}
		if(!m_Tasks.size()){
			unlock_rtdb();
			break;
		}
		p = m_Tasks.begin();
		task = *p;
		unlock_rtdb();

		if(task.tag.sname.tag.Data[0]){
			ret = load_tag(&task.tag);
		}else if(task.tag.sname.group.Data[0]){
			RTK_GROUP_NAME	gn;
			gn.node = task.tag.node;
			gn.group = task.tag.sname.group;
			ret = load_group(&gn);
		}else if(task.tag.node.Data[0]){
			ret = load_node(&task.tag.node);
		}else{
			// assert(false);
			ret = __true;
		}

		/* 2005-10-26 this sleep proves to be vital for large 
		system(greater than 7000 points)
		*/
		rtk_sleep(g_QueryInterval);
		
		if(!lock_rtdb(__true, 1000)){
			break;
		}

		// p might have already been removed from the list by other thread
		// note the check must be made while db lock is held
		// 2003/7/14, Jackie
		p = find(m_Tasks.begin(), m_Tasks.end(), task);
		// 2004/10/15, jackie, fixed a bug here
		if(p != m_Tasks.end()){
			if(!ret){
				(*p).failCount++;
				if((*p).failCount >= 3){
					m_Tasks.erase(p);
				}
			}else{
				m_Tasks.erase(p);
			}
		}
		
		unlock_rtdb();
	}
}

/* cancel un-loaded entries for this node */
void CProxyWorker::purge_load_queue(PCNODE_KEY nk)
{
	CWaitingList::iterator it;
	it = m_Tasks.begin();
	while(it != m_Tasks.end()){
		task_item_t * ti;
		ti = &(*it);
		if(ti->tag.node == *nk){
			it = m_Tasks.erase(it);
		}else{
			it++;
		}
	}
}

void CProxyWorker::kill_nodes()
{
	if(!lock_rtdb(__true, 1000)){
		return;
	}
	RTK_CURSOR	hNode;
	PRTK_NODE	pNode;
	NODE_KEY	nk;
__oops_a_guy_is_murdered:
	hNode = open_first_node();
	while(!cursor_is_end(hNode)){
		pNode = (PRTK_NODE)cursor_get_item(hNode);
		pNode->dogcount -= m_dwPeriod;
		if(pNode->dogcount < 0){
			nk = pNode->key;
			utils_debug(
				"Kicking '%s' off the shelf.\n",
				(char*)CNodeName(nk)
				);
			cursor_delete(hNode);
			/*
			rtk_queue_event(
				PT_Alarm, 
				0,
				AC_Offline,
				"Site idle too long, kicked out.",
				&nk
				);				
			*/
			goto __oops_a_guy_is_murdered;
		}
		cursor_move_next(hNode);
	}
	close_handle(hNode);
	unlock_rtdb();
}

void CProxyWorker::kill_tags()
{
}

void CProxyWorker::task()
{
	extern void _load_settings(__bool bSilent);
	_load_settings(__true);
	do_load();
}

CProxyWorker::CProxyWorker(int flags)
{
	m_dwPeriod = GetPrivateProfileInt(
		"PMC",
		"BGLoaderInterval",
		1000,
		get_config_file()
		);
	if(m_dwPeriod < 20 || m_dwPeriod > 30000){
		utils_error(
			"BGLoaderInterval = %d is not valid, reset to %d.\n",
			m_dwPeriod,
			1000
			);
		m_dwPeriod = 1000;
	}
	m_TaskFlag = flags;
}

