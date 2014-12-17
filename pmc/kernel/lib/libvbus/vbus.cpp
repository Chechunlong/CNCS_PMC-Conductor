/********************************************************************
	PC-Based monitoring & controlling system source
	prodoct version : 2.03
	filename: 	E:\vss\pmc2\src\rtknet\vbus.cpp
	file path:	E:\vss\pmc2\src\rtknet
	author: Jackie Pan, jhunter@tsinghua.org.cn

	purpose:	Virtual bus support	
	history:
	created:	10:11:2002   15:50
	2004/8/2
	jackie, variable fragment size bug fixed
*********************************************************************/
#include "precomp.h"
#pragma hdrstop

#include <zlib.h>
#include <rtk_thread.h>

#ifdef _WIN32
#pragma comment(linker, "/section:rtkshd,rws")
#pragma data_seg("rtkshd")
#endif

#define RTK_PRIVATE_PORT_BASE 128
static __u16 g_iCookiePort = RTK_PRIVATE_PORT_BASE;
static __u8	 g_PortMap[66536 / 8] = {0};

#ifdef _WIN32
#pragma data_seg()
#endif

static char * _bus_name(__uint id)
{
	return "User";
}

class CPortManager : CMutexLock
{
public:
	CPortManager() : CMutexLock("vbus port manager")
	{
	}
	__u16 AllocPort()
	{
		__u16 port;
		Lock();
		g_iCookiePort ++;
		if(g_iCookiePort == 0){
			g_iCookiePort = RTK_PRIVATE_PORT_BASE;
		}
		port = g_iCookiePort;
		UnLock();
		return port;
	}
}portmgr;

__bool CRtkVBus::init()
{
	__bool ok;
	int port;
	
	CRtkVBus * si=this;
	serverGuid.create();
	
	ok = __false;
	port = busid + VBUS_PORT_BASE;
	
	if(this->flag & VBUS_CONNECT_AS_SERVER){
		m_iRtkPort = PORT_ALL_SERVER;
	}else{
		m_iRtkPort = portmgr.AllocPort();
	}
	
	try{
#ifndef USE_MULTICAST
		m_bReuseAddr = true;		
		Create(port);
#else
		char ip[32];
		sprintf(ip, "%s.%d", VBUS_MULTICAST_IP_PREFIX, busid);
		if( !JoinGroup(ip, port, 3, true) ){
			utils_trace("Virtual bus ID %d created.\n", busid);
		}else{
			utils_error("Virtual bus ID %d failed in joining group.\n", busid);
		}
#endif
		int len=65535;
		si->SetSockOpt(SO_RCVBUF, (void *)&len, sizeof(len));
		si->SetSockOpt(SO_SNDBUF, (void *)&len, sizeof(len));
		
		//enable broadcasting
		len=__true;
		si->SetSockOpt(SO_BROADCAST,(void *)&len,sizeof(len));
		ok = __true;
	}catch(int e){
		utils_error("-- CRtkVBus failed, iCode=%d, wCode=%d\n", 
			e, GetLastError()
			);
		ok = __false;
	}
	
	if(ok){
		utils_trace(
			"Virtual Bus %d(%s,0x%x/0x%x,0x%x) initialized OK.\n", 
			busid,
			_bus_name(busid),
			GetCurrentProcessId(),
			id(),
			m_hSocket
			);
	}else{
		utils_trace("Virtual Bus %d initialization failed.\n", busid);
	}

	hIoProcessor = create_rthread_pool(1);	
	notify(EVT_INIT_COMPLETE);
	
	return ok;
    
}

__uint CRtkVBus::run()
{
	if( init() ){
		do_socket_io();
	}

	/* wait 3 seconds for pool worker to terminate */
	{
		__uint (RTK_API *_query_pool_items)(RTK_HANDLE pool);
		(FARPROC&)_query_pool_items=GetProcAddress(GetModuleHandle("LIBRTK.DLL"),"query_pool_items");
		if(_query_pool_items){
			int i=0;
			while(_query_pool_items(hIoProcessor) && i++<3){
				rtk_sleep(1000);
			}
		}
	}
	
	close_handle(hIoProcessor);
	return 0;
}

void CRtkVBus::claimServer()
{
	if((flag & (VBUS_CONNECT_AS_SERVER | VBUS_ACTIVE_SERVER)) ==
		(VBUS_CONNECT_AS_SERVER | VBUS_ACTIVE_SERVER)
	){
		RTK_ADDR addr;
		mk_bcast_addr(&addr.host);
		addr.port = PORT_ALL;
		send_rtk_data(
			this,
			&addr,
			PT_ServerClaim,
			&serverGuid,
			sizeof(serverGuid)
			);
	}
}

#ifdef _WIN32
__bool CRtkVBus::do_socket_io()
{
	MSG			msg;
	__bool		bStop = __false;
	DWORD		dwWait;
	RTK_TIME	wowo, wuwu, now;
	rtk_time_mark(&wowo);
	rtk_time_mark(&wuwu);
	HANDLE hStop = m_EvtStop.Handle();
	while(!bStop){
		dwWait = MsgWaitForMultipleObjects(
			1, &hStop, FALSE, 1000,
			QS_ALLINPUT
			);
		rtk_time_mark(&now);
		switch(dwWait){
		case WAIT_TIMEOUT:
			// fall-through
		case WAIT_OBJECT_0 + 1:
			while(PeekMessage(&msg,NULL,0,0, PM_REMOVE)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			Lock();
			if(rtk_time_diff(&now, &wowo) > 1){
				wowo = now;
				reap_packets();
				claimServer();
			}
			if(rtk_time_diff(&now, &wuwu) > 30){
				wuwu = now;
				broker.reap();
			}
			UnLock();
			// 
			break;
		case WAIT_OBJECT_0:
			bStop = __true;
			break;
		}
	}
	return __true;
}

#else
__bool CRtkVBus::do_socket_io()
{
	fd_set rset;
	struct timeval timeout;
	int ret;	 
	RTK_TIME	wowo, wuwu, now;
	rtk_time_mark(&wowo);
	rtk_time_mark(&wuwu);
	
	FD_ZERO(&rset);	 
	
	while( !m_bStopRequestPending ){
		FD_SET(m_hSocket, &rset);
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		ret = select(m_hSocket+1, &rset, NULL, NULL, &timeout);
		if( ret > 0){
			if( FD_ISSET(m_hSocket, &rset)){
				FD_CLR(m_hSocket, &rset);
				// DEBUG_PRINTF(("Select ok on %d\n", m_hSocket));
				OnReceive(0);
			}			   
		}else if(ret < 0){
		}else{
		}
		
		rtk_time_mark(&now);		  
		// 2003/2/21, Jackie, the following code cannot go along with
		// sending operations		  
		Lock();
		
		if(rtk_time_diff(&now, &wowo) > 1){
			// discard un-constructed packets that ages
			wowo = now;
			reap_packets();
			// DEBUG_PRINTF(("Cleaned aged packets on VBus %d.\n", busid));			   
		}
		if(rtk_time_diff(&now, &wuwu) > 30){
			// discard aged transcations
			wuwu = now;
			// DEBUG_PRINTF(("Cleaning aged transactions on VBus %d.\n", busid));
			broker.reap();
		}
		
		UnLock();		  
	}
	return __true;
}
#endif

CRtkVBus::CRtkVBus( 
	__u16 busid, 
	__uint flags, 
	VBUS_RECEIVE_PROC r_proc, 
	VBUS_EVENT_PROC f_proc
	)
{
	this->busid	 = busid;
	this->flag   = flags;
	this->r_proc = r_proc;
	this->f_proc = f_proc;
	m_iRtkPort = 0;
}

static string _format_integer(__i64 l)
{
	char buf[128];
	if( l > 1024*1024*1024 ){
		sprintf(buf, "%.3f G", (double)l / (1024*1024*1024) );
		return buf;
	}else if( l > 1024*1024){
		sprintf(buf, "%.3f M", (double)l / (1024*1024));
		return buf;
	}
	sprintf(buf, "%.3f K", (double)l / 1024);
	return buf;
}

CRtkVBus::~CRtkVBus()
{
	utils_error(
		"Bus %d(%s), sent=%d(%sB), got=%d(dup=%d, %sB), fragments=%d.\n",
		this->busid,
		_bus_name(busid),
		out_packets,
		_format_integer(out_bytes).data(),
		in_packets,
		duplicated_packets,
		_format_integer(in_bytes).data(),
		this->r_lst.size()
		);
	dbg_dump();
}

static PRTK_PACKET _duplicatePacket(PCRTK_PACKET data)
{
	char * buf;
	buf = new char[sizeof(*data) + data->data_size];
	if(buf){
		memcpy(buf, data, sizeof(*data) + data->data_size);
		return (PRTK_PACKET)buf;
	}
	return 0;
}

struct CPacketIoProcessor{
	static void RTK_API stub(__uint foo)
	{
		CPacketIoProcessor *me;
		me = (CPacketIoProcessor*)foo;
		me->job();
		delete me;
	}

	void job()
	{
		if(p && (p->packet_type & PF_Compressed)){
			// auto decompression
			__u8 * buf;
			PRTK_PACKET np;
			__ulong len;
			
			len=*((__u32*)p->data);
			buf=new __u8[len+sizeof(*p)];
			np=(PRTK_PACKET)buf;
			*np=*p;
			np->data_size=len;
			if(uncompress((__u8*)np->data, &len, (__u8*)p->data+sizeof(__u32), p->data_size-sizeof(__u32)) != Z_OK){
				delete buf;
				return;
			}
			// assert(len==*((__u32*)p->data));
			delete p;
			p=np;
			p->packet_type &= ~PF_Compressed;
		}
		if(t){
#ifndef NDEBUG
			char guid_name[128];
			p->guid.to_string(guid_name);
			DEBUG_PRINTF(("Got event %s\n", guid_name));
#endif
			t->OnEvent(p);
			b->broker._return(t);
		}else if(b->r_proc){
			b->r_proc(p, b);
		}
	}
	
	CPacketIoProcessor(CRtkVBus * b, PRTK_PACKET _p)
	{
		p = _duplicatePacket(_p);
		this->b = b;
		t = b->broker._borrow(p->guid);
	}
	
	~CPacketIoProcessor()
	{
		delete p;
	}
	
	RTK_PACKET *p;
	CRtkVBus * b;
	CTransaction * t;
};

void CRtkVBus::handlePacket(PRTK_PACKET p)
{
	CPacketIoProcessor * io;
	io = new CPacketIoProcessor(this, p);
	if(io){
		if(!queue_pool_item(hIoProcessor, -1, CPacketIoProcessor::stub, (__uint)io)){
			delete io;
		}
	}
}

void CRtkVBus::OnPacket(RTK_PACKET * p, int len)
{
	RECEIVE_ITEM *h = 0;
	
#if !defined(NDEBUG) && 0
	char guid_name[64];
	p->guid.to_string(guid_name);
	DEBUG_PRINTF((
		"Got packet, ID=%s:%d/%d/%d, Type:0x%08x, "
		"Src=%s:%d, Size=%d, Offset=%d\n",
		guid_name, 
		p->grp_id,
		p->frgmt_id, 
		p->total_frag, 
		p->packet_type,
		(char *)CHostName(p->src.host), 
		p->src.port,
		p->data_size, 
		p->offset
		));	
#endif
	p->packet_type &= ~PF_ReSend;

	if(p->packet_type == PT_RequestFragment){
		ResendFragments(p);
		return;
	}

	if(p->packet_type == PT_Ping){
		p->dest = p->src;
		p->src.host = g_ThisNode->key;
		p->src.port = this->m_iRtkPort;
		p->packet_type |= PF_ACK;
#ifdef _WIN32
		char appName[256];
		GetModuleFileName(NULL, appName, sizeof(appName));
#else
		char * appName = program_invocation_name;
#endif
		char *pp;
		pp = strrchr(appName, '\\');
		if(!pp){
			pp = strrchr(appName, '/');
		}
		if(pp){
			strncpy(
				p->data + sizeof(RTK_TIME), 
				pp + 1, 
				p->data_size - sizeof(RTK_TIME)
				);			
		}
		p->data[p->data_size - 1] = 0;
		SendFragment(p);
		return;
	}
	
	if( IsFragment(p)){
		h = MergePacket(p);
		CTransaction * t= broker._borrow(h->header->guid);
		if(t){
			t->OnProgress(
				h->header->total_frag, 
				h->header->total_frag - h->unreceived_fragments,
				h->header
				);
			broker._return(t);
		}
		if(!h->unreceived_fragments){
			handlePacket(h->header);
		}
	}else{
		handlePacket(p);
	}
}

__uint CRtkVBus::SendFragment(PRTK_PACKET packet)
{
	assert(packet->data_size <= m_dwEffectiveLoad);
#ifdef USE_MULTICAST
	return CRtkSocket::Multicast(
		(void *)packet, 
		packet->data_size + m_dwHeaderSize,
		LocalPort()
		);
#else
	return CRtkSocket::SendTo(
		(void *)packet, 
		packet->data_size + m_dwHeaderSize,
		LocalPort(), 
		&packet->dest
		);
#endif
}

/*
	send a packet over the network
	The packet might be split into a number of small ones, in
	that case, a send_item is generated and queued into the
	s_lst.
*/

// BUGBUG: 2004/8/2
// BUGBUG: SendPacket runs with the socket unlocked, 
// BUGBUG: this might be a potential problem.
// BUGBUG: now I've fixed it, hope the performance won't suck
__uint CRtkVBus::SendPacket(PRTK_PACKET packet)
{
	RTK_PACKET *frag;
	__uint i, headersize, bytes;
	SEND_ITEM	*si;

	Lock();
	/*
	packet management layer has a built in limitation on
	size of the largest single packet.
	*/
	if(packet->data_size > VBUS_MAX_PACKET_SIZE*(VBUS_MAX_PACKET_SIZE>>2)){
		UnLock();
		return 0;
	}
	
	packet->src.host = g_ThisNode->key;
	packet->src.port = m_iRtkPort;
	packet->version = VBUS_VERSION;
	
	if( !IsFragmentationNeeded(packet) ){
		packet->total_frag = 1;
		UnLock();
		return SendFragment(packet);
	}
	
	si = SplitPacket(packet);
	if(!si){
		UnLock();
		return 0;
	}
	headersize = sizeof(RTK_PACKET) - sizeof(packet->data);
	bytes = 0;
	UnLock();
	
	for(i=0, frag=si->header; i<si->header->total_frag; i++){
		Lock();
		bytes += SendFragment(frag);
		UnLock();
		rtk_sleep(vbus_delay_between_fragments);
		/*
			2004/8/2
			note now we cannot simply get next fragment by
			adding m_mtu to it, because the fragment can
			vary in size in later.
		*/
		((char *&)frag) += frag->data_size + 
			sizeof(RTK_PACKET) - 
			sizeof(frag->data);
	}

	return bytes;
}

void CRtkVBus::connect(int flags, VBUS_RECEIVE_PROC r, VBUS_EVENT_PROC f)
{
	this->flag = flags;
	r_proc = r;
	f_proc = f;
}

/*
	ResendFragments(...)

	If a client has reported missing fragments, this proc will
	resent the missing parts. It looks into the s_lst to see
	whether the items are still there, it's quite possible that
	the s_lst reaper has removed the items from the queue,
	in that case, we can do nothing but say sorry to the 
	client.

	Parameters :

	src : a packet describing the missing fragments.
	the data portion of the packet is
	RTK_GUID, grp_id, list of frgmt_ids
	
	Environment : must have s_lst locked.
*/
void CRtkVBus::ResendFragments(PCRTK_PACKET src)
{
	SEND_ITEM	*si;
	__uint		items;
	__u16		*rsid;
	PRTK_PACKET p;
	PCRTK_GUID	pGuid;

	pGuid = (PCRTK_GUID)src->data;
	rsid = (__u16*)(pGuid + 1);
	
	items = (src->data_size-sizeof(RTK_GUID)) / sizeof(__u32);

	if(!items){
		return;
	}

	if(items > 10){
		items = 10;
	}
	
	si = GetSendItem(*pGuid, rsid[0]);
	rsid++;

	if(!si){
		return;
	}

	if(items >= si->header->total_frag){
		return;
	}
	
	// reset the send_item's birthday, so that it can live longer
	rtk_time_mark(&si->birthday);
	
#if !defined(NDEBUG) && !defined(UTILS_NODEBUG)
	int j=0;
	char dbg_msg[1024], *dbg_p;
	dbg_msg[0] = 0;
	dbg_p = dbg_msg;
	dbg_p += sprintf(
		dbg_p, "_P: Resend %d/%d fragments of group %d to %s:%d:",
		items,
		si->header->total_frag,
		si->header->grp_id,
		(char*)CHostName(src->src.host),
		src->src.port
		);
#endif

	for(__uint i=0; i<items; i++){
#if !defined(NDEBUG) && !defined(UTILS_NODEBUG)
		DEBUG_PRINTF((
			"Resend %d/%d of total %d to %s:%d\n", 
			si->header->grp_id,
			*rsid,
			si->header->total_frag,
			(char *)CHostName(src->src.host), 
			src->src.port
			));
		dbg_p += sprintf(dbg_p, "%d ", *rsid);
#endif
		if(*rsid < si->header->total_frag){
			// BUGBUG: the fragment is located assuming each fragment is of
			// BUGBUG: the same size except the last one
			(char *&)p = (char*)si->header + (*rsid - si->header->frgmt_id)* m_mtu;
			//3 Note we must have the s_lst locked to modify it
			p->dest = src->src;
			SendFragment(p);
		}else{
			assert(0);
		}
		rsid++;
	}
#if !defined(NDEBUG) && !defined(UTILS_NODEBUG)
	DEBUG_PRINTF(("%s\n", dbg_msg));
#endif	
}

__bool CRtkVBus::WillingToAccept(PCRTK_PACKET p)
{
#if 1
	DEBUG_PRINTF((
		">> (0x%x/0x%x) : Filtering packet %s:%d -> %s:%d, %d bytes, type 0x%08x, %d of %d\n",
		GetCurrentProcessId(),
		id(),
		(char*)CHostName(p->src.host),
		p->src.port,
		(char*)CHostName(p->dest.host),
		p->dest.port,
		p->data_size,
		p->packet_type,
		p->frgmt_id,
		p->total_frag
		));
#endif
	// check validity of the packet
	if(p->version != VBUS_VERSION
		// can only communicate with peers of the same version
		||
		p->data_size > VBUS_MAX_PACKET_SIZE*(VBUS_MAX_PACKET_SIZE>>2)
		||
		p->total_frag >= (VBUS_MAX_PACKET_SIZE>>2)
		||
		p->frgmt_id >= p->total_frag
	){
		return 0;
	}
	
	if(is_same_key(&p->src.host, &g_ThisNode->key) && p->src.port == m_iRtkPort){
		if(p->packet_type == PT_ServerClaim){
			if(!(*((RTK_GUID*)p->data) == serverGuid) ){
				if((flag & (VBUS_CONNECT_AS_SERVER | VBUS_ACTIVE_SERVER)) == 
					(VBUS_CONNECT_AS_SERVER | VBUS_ACTIVE_SERVER)
				){
					if(f_proc){
						f_proc(this, VBUS_EVT_COLLISION, (int)p);
					}
					return __true;
				}
			}
		}
		
		return __false;
	}

	if(PACKET_TYPE(p) == PT_Debug){
		extern void net_debug();
		net_debug();
		return __false;
	}
	
	if(f_proc){
		return f_proc(this, VBUS_EVT_GOT_FRAGMENT, (int)p)? __true : __false;
	}
	
	return r_proc? __true : __false;
}

VBUS_API __u16 RTK_API alloc_vbus_port()
{
	return portmgr.AllocPort();
}

VBUS_API __uint RTK_API get_vbus_flag(
	HVBUS handle
	)
{
	return ((CRtkVBus*)handle)->flag;
}

VBUS_API __uint RTK_API set_vbus_flag(
	HVBUS handle,
	__uint flag
	)
{
	CRtkVBus * bus = (CRtkVBus*)handle;
	bus->flag |= (flag & 0xff000000);
	return bus->flag;
}

VBUS_API __uint RTK_API reset_vbus_flag(
	HVBUS handle,
	__uint flag
	)
{
	CRtkVBus * bus = (CRtkVBus*)handle;
	bus->flag &= ~(flag & 0xff000000);
	return bus->flag;
}



