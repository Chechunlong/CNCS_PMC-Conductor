/********************************************************************
	PC-Based monitoring & controlling system source
	prodoct version : 2.03
	filename:	E:\vss\pmc2\src\s960npu\npu.cpp
	file path:	E:\vss\pmc2\src\s960npu
	author:		Jackie Pan, jhunter@tsinghua.org.cn
	
	purpose:	S960 device driver	
	history:
	created : by J.Hunter,Jul.,2001
	revised : by Jackie, 10:10:2002	  16:06
	revised : by Jackie, 11/1/2002, 11:12, CRtkThread based sampling
	revised : by Jackie, 3/5/2003, 17:04, linux version
	revised : by Jackie, 5/22/2003, master/slave mode support
	revised : by jackie, 6/3/2003, RTK_LIST_ENTRY added to CS960Port
*********************************************************************/
#include <pmc.h>
#include <object.h>
#include <rtk_list_entry.h>

#define DEFAULT_WAKEUP	10
#define DEFAULT_DELAY	150

static const int max_ports	  = 16;
static const int max_devices  = 100;
static const int max_channels = 60;

static int	_read_s960(int pno,int d_id);
static void _add_lrc_and_cr(char * buf,int len);
static void _dump(char * buf,int l);

// #define rtkm_check_error

/*
	S960_DEVICE NPU hardware buffer format
*/
#include <pshpack1.h>
struct hbuf_entry_a_part_t{
	char sign;
	char digits;
	char bcd[4];	
}PACKED;
struct hbuf_entry_l_part_t{
	char value[2];
	char unused[4];
}PACKED;

struct hbuf_entry_t {
	union{
		struct hbuf_entry_a_part_t a;	/* analog */
		struct hbuf_entry_l_part_t l;	/* logical */
	}PACKED;
}PACKED;
#include <poppack.h>

#pragma comment(lib, "libutils.lib")
#pragma comment(lib, "libspac.lib")
#pragma comment(lib, "libpowermgr.lib")
#pragma comment(lib, "librtk.lib")

class CS960Port : public CPeriodicThread
{
private:
	struct S960_DEVICE{
		int			 device_no;
		int			 fail_count; 
		RTK_LIST_ENTRY	 link;
		hbuf_entry_t h_buffer[max_channels];
	};
	int m_dwPortNo;
	int m_iWakeup;
	int m_iDelay;
	int m_dwDeviceCount;
private:
	S960_DEVICE	 m_Devices[max_devices];
	RTK_LIST_ENTRY	 m_Connected, *m_CurrentDevice;
public:
	CS960Port(__uint pno)
	{
		m_dwPortNo = pno;
		init();
	}
	void init()
	{
		int i;
		m_iWakeup = DEFAULT_WAKEUP;
		m_iDelay  = DEFAULT_DELAY;
		memset(m_Devices, 0, sizeof(m_Devices));
		for(i=0; i<max_devices; i++){
			m_Devices[i].device_no = i+1;
			RtkInitializeListHead(&m_Devices[i].link);
		}
		RtkInitializeListHead(&m_Connected);
		m_Redundant = 0;
		m_CurrentDevice = 0;
	}
	virtual void task();
	__bool update_h_buffer_phase_1(S960_DEVICE * s960);
	__bool update_h_buffer_phase_2(S960_DEVICE * s960);
	__bool read_tag(
		PCRTK_TAG tte,
		pmc_value_t &pt,
		int dno, int cno
		);
	int	 config(int c, char **);
	int	 config(const CS960Port & s);

	PDEVICE_INFO m_Handle;

	CS960Port * m_Redundant;
};

/* 向前端设备发送读数据命令. */
__bool CS960Port::update_h_buffer_phase_1(S960_DEVICE *s960)
{
	char cmd[32];
	sprintf(cmd,":%02d42013C", s960->device_no);
	_add_lrc_and_cr(cmd,strlen(cmd));
#ifdef rtkm_check_error
	_dump(cmd,strlen(cmd));
#endif
	return write_port(m_dwPortNo, cmd, strlen(cmd), 10);
}

/* 从前端设备读取数据 */
__bool CS960Port::update_h_buffer_phase_2(S960_DEVICE *s960)
{
	int			size;
	char		buf[8192];	  
	hbuf_entry_t	*hbuf = s960->h_buffer;
	size = sizeof(buf);

	read_port(m_dwPortNo, buf, &size,100);
#ifdef rtkm_check_error
	utils_error(">> s960 port %d, ID %d, %d bytes.\n",
		m_dwPortNo, s960->device_no, size
		);
#endif
	/*
		inspect buffer
	*/
	// check buffer length
	if(size<8)				{
#ifdef rtkm_check_error		   
		utils_error(
			">> s960 port %d, ID %d-->data too small(%d bytes).\n",
			m_dwPortNo, s960->device_no, size
			);
#endif
		goto __err;
	}
	if(size>(8+sizeof(hbuf_entry_t)*max_channels)) {
#ifdef rtkm_check_error
		utils_error(">> s960 --> data too big.\n");
#endif
		goto __err;
	}
	// check head and tail
	if(buf[0] != ':')		{
#ifdef rtkm_check_error
		utils_error(">> s960 --> invalid data, no ':' found.\n");
#endif
		goto __err;
	}
	if(buf[size-1] != '\r') {
#ifdef rtkm_check_error
		utils_error(">> s960 --> invalid data, no cr found.\n");
#endif
		goto __err;
	}
	// check LRC
	char h,l;
	h=buf[size-3];
	l=buf[size-2];
	_add_lrc_and_cr(buf, size-3);
	if(h!=buf[size-3] || l!=buf[size-2]) {
#ifdef rtkm_check_error
		utils_error(">> s960 --> invalid data, LRC error.\n");
#endif
		goto __err;
	}
	/*
	// check function code
	if(buf[2] & 0x8) {
		utils_error(">> s960 --> invalid data, function code.\n");
		return;
	}
	*/
	/* ok, a good response */
#ifdef rtkm_check_error
	utils_error(
		">> s960 port %d, ID %d--> data OK(%d bytes).\n",
		m_dwPortNo, s960->device_no, size
		);
#endif
	memcpy(hbuf,buf+5,size-8);
	s960->fail_count = 0;
	return __true;
__err:
	s960->fail_count++;
	if(s960->fail_count >= 3){
		// invalidate data
		memset(hbuf,'4', sizeof(s960->h_buffer));
	}
	return __false;
}

void CS960Port::task()
{
	S960_DEVICE *s960;

	if(!m_CurrentDevice){
		return;
	}
	assert(m_dwDeviceCount);
	s960 = SAFE_CONTAINING_RECORD(m_CurrentDevice, S960_DEVICE, link);
	if(get_power_state() != PWR_RUNNING){
		return;
	}
	if(!lock_port(m_dwPortNo, 100)){
		// wperror(">> lock_port failed.");
		return;
	}
	if(update_h_buffer_phase_1(s960) ){
		Sleep(m_iDelay);
		update_h_buffer_phase_2(s960);		
	}
	unlock_port(m_dwPortNo);

	m_CurrentDevice = m_CurrentDevice->Flink;
	if(m_CurrentDevice == &m_Connected){
		m_CurrentDevice = m_Connected.Flink;
		assert(m_CurrentDevice != &m_Connected);
	}
}

int CS960Port::config(int c, char **v)
{
	m_dwDeviceCount=0;
	int j;

	/* 
	possible bug!! extra 'delay=' statements in config string
	may cause crash. Jackie, 11/5/2002
	*/
	if(c > max_devices){
		utils_error(
			"Wow !!! How can u put that many devices on one line(%d max)\n",
			max_devices
			);
		c = max_devices;
	}

	for(j=0; j<c; j++){
		if(!strnicmp(v[j],"delay=",6)){
			m_iDelay=atoi(v[j] + 6);
			if(m_iDelay <= 0){
				utils_error(
					">> s960, port %d, delay=%d, invalid, set to 150.\n",
					m_dwPortNo, m_iDelay
					);
				m_iDelay = DEFAULT_DELAY;
			}
		}else if(!strnicmp(v[j], "refresh=", 7)){
			m_iWakeup = atoi(v[j] + 7);
			if(m_iWakeup <= 0){
				utils_error(
					">> s960, port %d, refresh=%d, invalid, set to %d.\n",
					m_dwPortNo, m_iWakeup, DEFAULT_WAKEUP
					);
				m_iWakeup = DEFAULT_WAKEUP;
			}
		}else{
			int did=atoi(v[j]);
			if(did<1 || did>max_devices){
				utils_error(
					">> s960, port %d, %d is not a good device ID.\n",
					m_dwPortNo, did
					);
			}else{
				m_Devices[did - 1].device_no = did;
				RtkInsertTailList(&m_Connected, &m_Devices[did - 1].link);
				m_dwDeviceCount++;
			}
		}
	}

	if(m_dwDeviceCount){
		m_CurrentDevice = m_Connected.Flink;
	}else{
		m_CurrentDevice = 0;
	}
	utils_trace(
		">> Ok, port %d, %d s960 device(s) connected.\n",
		m_dwPortNo, m_dwDeviceCount
		);

	m_dwPeriod = m_iWakeup;

	return 1;
}

int CS960Port::config(const CS960Port & s)
{
	init();
	m_iDelay = s.m_iDelay;
	m_iWakeup = s.m_iWakeup;
	m_dwPeriod = m_iWakeup;
	m_dwDeviceCount = s.m_dwDeviceCount;
	// build device links parallel to that of the master port
	PRTK_LIST_ENTRY	lnk;
	lnk = s.m_Connected.Flink;
	while(lnk != &s.m_Connected){
		S960_DEVICE *s960, *s960_master;
		s960_master = SAFE_CONTAINING_RECORD(lnk, S960_DEVICE, link);
		s960 = &m_Devices[s960_master - s.m_Devices];
		RtkInsertTailList(&m_Connected, &s960->link);
		lnk = lnk->Flink;
	}
	if(m_dwDeviceCount){
		m_CurrentDevice = m_Connected.Flink;
	}else{
		m_CurrentDevice = 0;
	}
	return 1;
}

/*
	从硬件缓冲区中得到变量的工程值
	输入：
	ni	-->	 NPU名
	tte -->	 变量
	he	-->	 硬件缓冲区
*/
__bool CS960Port::read_tag(
	PCRTK_TAG tte, 
	pmc_value_t &pt,
	int did,
	int cno)
{
	char	c;
	double	val;
	int		ret;
	hbuf_entry_t *he;
	TAG_TYPE tp;

	he = &m_Devices[did-1].h_buffer[cno-1];

	memset(&pt,0,sizeof(pt));
	val=0;
	try{
		tp = get_value_type(tte->s.Flags);
		if(tp == dt_real4){
			c=he->a.bcd[0];
			if(c<'0' || c>'9') throw(-1);
			val=val*10+c-'0';
			c=he->a.bcd[1];
			if(c<'0' || c>'9') throw(-1);
			val=val*10+c-'0';
			c=he->a.bcd[2];
			if(c<'0' || c>'9') throw(-1);
			val=val*10+c-'0';
			c=he->a.bcd[3];
			if(c<'0' || c>'9') throw(-1);
			val=val*10+c-'0';
			c=he->a.digits;
			if(c<'0' || c>'9') throw(-1);
			val=val/pow(10,c-'0');
			c=he->a.sign;
			if(c!='0' && c!='8') throw(-1);
			if(c=='8') val=-val;
			pt.Value.flt = (__r4)val;
		}else if(tp == dt_bool){
			c=he->l.value[0];
			if(c<'0' || c>'9') throw(-1);
			c=he->l.value[1];
			if(c<'0' || c>'9') throw(-1);
			c=(he->l.value[0]-'0')*10+he->l.value[1]-'0';
			pt.Value.b = c? 1 : 0;
		}
		pt.Flags |= TF_Valid;
		ret=1;
	}catch(int){
		pt.Flags &= ~TF_Valid;
		ret=0;
	}
	return ret;
}

static void _dump(char * buf, int l)
{
	int i,j;
	char  * p;
	for(i=0,p=buf; i<(l>>4); i++){
		for(j=0; j<16; j++,p++){
			*p=='\r'? 0:utils_debug("%c ",(unsigned)*p);
		}
		utils_debug("\n");
	}
	for(i=0; i<(l%16); i++,p++){
		*p=='\r'? 0:utils_debug("%c ",(unsigned)*p);
	}
	utils_debug("\n");
}

/*
	添加设备接口
	对于s960前端，address的格式必须为 "COM%d", 其中%d部分必须在
	1到16之间
*/
IOSS_DLL_EXPORT __bool start_device(PDEVICE_INFO handle)
{
	int pno;
	CArgs args;
	char * address = handle->address;
	char * parameter = handle->parameter;

	if(strlen(address) < 4){
		return __false;
	}
	if(strnicmp(address, "com", 3)){
		return __false;
	}
	pno = atoi(address + 3);
	if(pno <1 || pno > max_ports){
		return __false;
	}
	if(!(pno & 1)){
		utils_error(
			"S960 must be connected to an odd-numbered serial port!\n"
			);
		return __false;
	}

	CS960Port *port, *port_1;
	port = new CS960Port(pno);
	port_1 = new CS960Port(pno + 1);
	if(!port || !port_1){
		utils_error(">> s960, new struct ap failed.\n");
		if(port)	delete port;
		if(port_1)	delete port_1;
		return __false;
	}
	parse_arg_ex(parameter, &args, ",");
	if(!port->config(args.argc, args.argv)){
		delete port;
		delete port_1;
		return __false;
	}
	port_1->config(*port);
	port->m_Handle = handle;
	port_1->m_Handle = handle;
	port->m_Redundant = port_1;	
	handle->OwnerField = port;

	if( !port->start() || !port_1->start() ){
		delete port;
		delete port_1;
		return __false;
	}

	return __true;
}

IOSS_DLL_EXPORT __bool stop_device(PDEVICE_INFO handle)
{
	CS960Port *port, *pr;

	port = (CS960Port*)handle->OwnerField;
	assert(port->m_Handle == handle);
	pr = port->m_Redundant;	
	port->stop(INFINITE);
	if(pr){
		pr->stop(INFINITE);
	}
	delete port;
	delete pr;
	return __true;
}

static void _add_lrc_and_cr(char * buf, int len)
{
	int i,A;
	if(len<2) return;
	A = 0;
	for(i=1;i<len;i++){
	   A = A ^ buf[i];
	}
	sprintf(buf+len,"%02X",A);
	len+=2;
	buf[len++]=13;
	buf[len++]=0;
}

IOSS_DLL_EXPORT __bool load(PDRIVER_INFO)
{
	return __true;
}

IOSS_DLL_EXPORT __bool unload()
{
	return __true;
}

/*
	Address format differs from version 1.0:
	DEVICE_ID.CHANNEL_ID
*/
IOSS_DLL_EXPORT __bool address_translate(PRTK_TAG tte)
{
	CArgs args;
	int   dno,cno;

	parse_arg_ex(tte->s.Address,&args,".;!*-");
	memset(tte->d.BinaryAddress,0,sizeof(tte->d.BinaryAddress));
	if(utils_argc == 2){
		dno=atoi(utils_argv[0]);
		cno=atoi(utils_argv[1]);
		if( dno<1 || cno<1 || 
			dno>max_devices || 
			cno>max_channels
		){
			return __false;
		}else{
			tte->d.BinaryAddress[0]=dno;
			tte->d.BinaryAddress[1]=cno;
		}
	}else{
		return __false;
	}
	return __true;
}

IOSS_DLL_EXPORT void update_tag(PCRTK_TAG tte, pmc_value_t * pt, PCRTK_TIME)
{
	__bool ret;
	int dno, cno;
	CS960Port * port;
	PCDYNAMIC_TAG_DATA d = &tte->d;

	port = (CS960Port*)tte->d.DeviceObj->OwnerField;
	dno = d->BinaryAddress[0];
	cno = d->BinaryAddress[1];		
	if( dno<1 || cno<1 || 
		dno>max_devices || 
		cno>max_channels
	){
		return;
	}
	
	ret = port->read_tag(tte, *pt, dno, cno);
	// check redundant port
	if(!ret && port->m_Redundant){
		ret = port->m_Redundant->read_tag(tte, *pt, dno, cno);
	}

	if(ret){
		pt->Flags |= TF_Valid;
	}
}
