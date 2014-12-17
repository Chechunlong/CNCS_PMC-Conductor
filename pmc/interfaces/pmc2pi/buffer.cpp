#include "precomp.h"
#pragma hdrstop

using namespace std;

#include "buffer.h"

struct ATTR_OF_PI{
	long id;
	char exdesc[81];
	char type;
	long exmin;
	long exmax;
	float excdeveng;
};

struct ATTR_OF_PMC{
	TAG_NAME tn;
	// DYNAMIC_TAG_DATA oldValue;
	// DYNAMIC_TAG_DATA curValue;
	pmc_value_t oldValue;
	pmc_value_t curValue;
	RTK_TIME oldTime;
};

struct PMC2PI_POINT{
	ATTR_OF_PI pi;
	ATTR_OF_PMC pmc;
};

#if defined(USE_STL)
typedef list<PMC2PI_POINT> PTS_BUFFER;
static PTS_BUFFER buffer;
#define TAG_COUNT buffer.size()
#else
#define MAX_TAGS 10240
struct PMC2PI_POINT g_Tags[MAX_TAGS];
int g_iTagCount;
#define TAG_COUNT g_iTagCount
#endif

bool initBuffer()
{
	long status = 0;
	if((status = piut_connect("")) != 0){
		utils_trace("connect to default pi server failed, return code %d\n", status);
		return false;
	}
	utils_trace("connect to default pi server success\n");

	g_iTagCount = 0;

	// get ptsource
	/*
		Jackie, 2004/2/28
		Change configuration file to the standard PMC config file : ``config/pmc.ini''
	*/
	char ptsource[2];
	GetPrivateProfileString(
		"PMC2PI", 
		"DataSource", 
		"P", 
		ptsource, 
		sizeof(ptsource), 
		get_config_file()
		);
	utils_trace("use data source %s\n", ptsource);

	// get points from PI DB 
	long pt = 0;
	TAG_NAME tn;
	PMC2PI_POINT p;

	while(!(status = pipt_nextptwsource ( ptsource[0], &pt ))) {
		p.pi.id = pt;
		if(pipt_exdesc(pt, p.pi.exdesc, sizeof(p.pi.exdesc)) != 0){
			utils_trace("pipt_exdesc error, pt=%d\n", pt);
			continue;
		}
		if(pipt_excspecseng(pt, &p.pi.excdeveng, &p.pi.exmin, &p.pi.exmax) != 0){ 
			utils_trace("pipt_excspecseng error, pt=%d\n", pt);
			continue;
		}
		if(pipt_pointtype(pt, &p.pi.type) != 0){
			utils_trace("pipt_pointtype error, pt=%d\n", pt);
			continue;
		}
		if(p.pi.type != 'R' && p.pi.type != 'I'){
			utils_trace("pmc2pi do not support this point, pt=%d, type=%c\n", pt, p.pi.type);
			continue;
		}
#if defined(USE_STL)
		string temp = p.pi.exdesc;
		int pos = temp.find_last_not_of(' ');
		if(pos >= 0){
			temp = temp.substr(0, pos+1);
		}
		tagname_by_text(&tn, temp.data());
#else
		char * pp = strtok(p.pi.exdesc, " ");
		if(!pp){
			pp = p.pi.exdesc;
		}
		tagname_by_text(&tn, pp);
#endif
		
		p.pmc.tn = tn;
		memset(&p.pmc.oldTime, 0, sizeof(p.pmc.oldTime));
		memset(&p.pmc.oldValue, 0, sizeof(p.pmc.oldValue));

#ifdef USE_STL
		buffer.insert(buffer.end(), p);
#else
		g_Tags[g_iTagCount++] = p;
#endif
	}

	// check the status return
	if ( status != -1 ){
		utils_error("error in 'pipt_nextptwsource', status=%d\n", status);
		return false;
	}else{
		utils_trace("get %d points with source '%c'\n", TAG_COUNT, ptsource[0]);
	}

	if(TAG_COUNT == 0){
		utils_trace("init buffer failed\n");
		return false;
	}else{
		utils_trace("init buffer success\n");
		if(init_proxy(0, PROXY_ENABLE_BGLOADER | PROXY_SILENT)){
			utils_trace("start pmc proxy success\n");
			return true;
		}else{
			utils_trace("start pmc proxy failed\n");
			return true;
		}
	}
}

static bool exceptionHappened(RTK_TIME & curTime, PMC2PI_POINT * it)
{
	if(rtk_time_diff(&curTime, &it->pmc.oldTime) < it->pi.exmin){
		return false;
	}

	if(rtk_time_diff(&curTime, &it->pmc.oldTime) < it->pi.exmax){
		if((it->pmc.curValue.Flags & TF_Valid) != (it->pmc.oldValue.Flags & TF_Valid)){
			return true;
		}
		if((it->pmc.curValue.Flags & TF_Valid) == 0){
			return false;
		}
		if(it->pi.type == 'R'){
			if(fabs(it->pmc.curValue.Value.flt - it->pmc.oldValue.Value.flt) < it->pi.excdeveng){
				return false;
			}
		}else{
			if(it->pmc.curValue.Value.b == it->pmc.oldValue.Value.b){
				return false;
			}
		}
	}

	return true;
}

/*
'Sending and Retrieving Values from PI
'PI-API functions that send and retrieve data from PI typically take a floating point and 
'an integer argument typically referred to as rval and istat, respectively. The interpretation
'of these variables depends on the point type and the PI Systems.
'When retrieving data from PI, the rval and istat are interpreted as follows:
'
'RVal
'   Point Type
'   R
'       value if Istat = 0 otherwise undefined
'   i
'       undefined
'   D
'       undefined
'
'istat
'   R
'      0 if value is good, otherwise digital state
'   i
'      value if >= 0, otherwise digital state code
'   D
'      digital state code
'
'When sending values to PI, the floating point and integer arguments are treated as above 
'for sending real and integer data.
'Digital states can be sent to real and integer tags rather than values to indicate status 
'changes. PI on OpenVMS systems support a single, defined set of valid states. Windows NT 
'and UNIX PI Systemss support a similar set of states called the system set; however the 
'user may also define additional state sets. Any digital point in a Windows NT or UNIX PI 
'Systems may be assigned one of these additional sets. These digital points can accept state 
'values for both their individually assigned state set as well as the system set. 
'For sending digital states, the following applies to the istat parameter:
'
'Meaning of Istat
'   Point Type
'   R
'       All platforms
'           If <> 0 istat is a state in the system set. If = 0 then the rval is considered valid.
'   D
'       OpenVMS
'           If > 0, istat is an offset from the digital start code of the point.
'           If < 0 , istat is an absolute digital state
'       Windows NT, UNIX
'           If > 0, istat is an offset into the points defined state set.
'           If < 0 and > -32768, istat is an offset into the system state set.
'   i
'       All platforms
'           If > 0 istat is an integer value
'           If <0 istat is a system state code
'
'This behavior was designed so that most programs can work with PI Systems on any platform 
'without special logic to account for differences in the implementation of digital states.
*/
#ifdef USE_STL
void updateBuffer()
{
	PTS_BUFFER::iterator it;

	// 1st, get data from pmc
	if(!lock_rtdb(false,1000)){
		return;
	}
	PRTK_TAG p;

	PMC2PI_POINT * pp;
	for(it = buffer.begin(); it != buffer.end(); it++){
		pp = &(*it);
		p = query_tag_f(&(pp->pmc.tn));
		if(!p){
			continue;
		}
		if(get_value_type(p->d.Value.Flags) == dt_bool){
			pp->pmc.curValue = p->d.Value;
		}else{
			pp->pmc.curValue.Flags = p->d.Value.Flags;
			set_value_type(pp->pmc.curValue.Flags, dt_real4);
			pmc_type_cast(&p->d.Value, &pp->pmc.curValue);
		}
	}
	unlock_rtdb();

	// 2nd, put data to snapshot of pi
	RTK_TIME curTime;
	rtk_time_mark(&curTime);
	float rval;
	long istat;
	long status;
	for(it = buffer.begin(); it != buffer.end(); it++){
		pp = &(*it);
		if(!exceptionHappened(curTime, pp)){
			continue;
		}
		pp->pmc.oldValue = pp->pmc.curValue;
		pp->pmc.oldTime = curTime;
		rval = it->pmc.curValue.fltValue;
		if((pp->pmc.curValue.Flags & TF_Valid) == 0){
			istat = -1;
		}else{
			if(it->pi.type == 'R'){
				istat = 0;
			}else{
				// 0 means 'Off' in user defined set - 'pmc'
				// 1 means 'On' in user defined set - 'pmc'
				if(it->pmc.curValue.iValue){
					istat = 1;
				}else{
					istat = 0;
				}
			}
		}
		if((status = pisn_putsnapshot(it->pi.id, rval, istat, 0)) != 0){
			utils_trace(
				"pisn_putsnapshot error, pt=%d, error code=%d\n", 
				it->pi.id, 
				status
				);
		}
	}
}
#else
void updateBuffer()
{
	int i;
	PRTK_TAG p;
	PMC2PI_POINT * pp;
	float rval;
	long istat;
	long status;
	RTK_TIME curTime;

	// 1st, get data from pmc
	if(!lock_rtdb(false,1000)){
		return;
	}
	for(i = 0, pp = g_Tags; i < g_iTagCount; i++, pp++){
		p = query_tag_f(&(pp->pmc.tn));
		if(!p){
			continue;
		}
		if(get_value_type(p->d.Value.Flags) == dt_bool){
			pp->pmc.curValue = p->d.Value;
		}else{
			pp->pmc.curValue.Flags = p->d.Value.Flags;
			set_value_type(pp->pmc.curValue.Flags, dt_real4);
			pmc_type_cast(&p->d.Value, &pp->pmc.curValue);
		}
	}
	unlock_rtdb();

	// 2nd, put data to snapshot of pi
	rtk_time_mark(&curTime);
	for(i = 0, pp = g_Tags; i < g_iTagCount; i++, pp++){
		if(!exceptionHappened(curTime, pp)){
			continue;
		}
		pp->pmc.oldValue = pp->pmc.curValue;
		pp->pmc.oldTime = curTime;
		rval = pp->pmc.curValue.Value.flt;
		if((pp->pmc.curValue.Flags & TF_Valid) == 0){
			istat = -1;
		}else{
			if(pp->pi.type == 'R'){
				istat = 0;
			}else{
				// 0 means 'Off' in user defined set - 'pmc'
				// 1 means 'On' in user defined set - 'pmc'
				if(pp->pmc.curValue.Value.i){
					istat = 1;
				}else{
					istat = 0;
				}
			}
		}
		if((status = pisn_putsnapshot(pp->pi.id, rval, istat, 0)) != 0){
			utils_trace(
				"pisn_putsnapshot error, pt=%d, error code=%d\n", 
				pp->pi.id, 
				status
				);
		}
	}
}
#endif	// USE_RTL

void clearBuffer()
{
	piut_disconnect();
	//uninit_proxy();
#ifdef USE_STL
	buffer.clear();
#else
	g_iTagCount = 0;
#endif
}
