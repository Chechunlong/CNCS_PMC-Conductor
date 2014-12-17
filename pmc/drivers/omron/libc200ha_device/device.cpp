/********************************************************************
	PC-based Monitoring & Controlling system source
	prodoct version : 2.03
	author:		Jackie Pan, jhunter@tsinghua.org.cn
	
	purpose:	Omron C200H-Alpha series PLC device driver

	history:
	
	created:	by J.Hunter,Jul.,2001
	
	upgraded:	Jackie, version 2.03, 10/23/2002
	
	revised:	Jackie, 11:1:2002	14:31, 
	
	bug fixed:	Jackie, 2003/9/4
	
	unit number config added: Jackie, 2004/7
	
	hr section bitwise write added: Jackie, 2004/7/14
	
	batch number changed from 30 to 25: Jackie, 2004/7/15

	bug fixed : change the device mode to monitor mode before write.
*********************************************************************/
#include <pmc.h>
#include <ddk.h>
#include <object.h>

#include "c200h_a.h"

#pragma comment(lib, "libutils.lib")
#pragma comment(lib, "libspac.lib")
#pragma comment(lib, "libpowermgr.lib")
#pragma comment(lib, "librtk.lib")

struct hw_addr_t{
	__u8 sno;		// section
	__u8 rno;		// register
	__i8 bno_hex;	// bit no, or hex-mode for analog
	__u8 scaling;		// use scaling
	__r4  a;			// a*x + b
	__r4  b;
};

static int add_fcs_and_cr(char * buf,int len)
{
	int i,A;
	if(len<2) return 0;
	A = 0;
	for(i=0;i<len;i++){
		A = A ^ buf[i];
	}
	sprintf(buf+len,"%02X",A);
	len+=2;
	buf[len++]='*';
	buf[len++]=13;
	buf[len++]=0;
	return 1;
}

OMRON_SECTION::OMRON_SECTION(SECTION_TYPE t)
{
	m_curRegister=0;
	this->m_sectionType=t;
	switch(t){
	case ost_dm_section:
		m_readCmdPrefix="RD";
		m_writeCmdPrefix="WD";
		break;
	case ost_hr_section:
		m_readCmdPrefix="RH";
		m_writeCmdPrefix="WH";
		break;
	case ost_ir_section:
		m_readCmdPrefix="RR";
		m_writeCmdPrefix="WR";
		break;
	};
	//hbuf_length=0;
	memset(m_cacheFlags,0,sizeof(m_cacheFlags));
}

int OMRON_SECTION::check_error(char * buf)
{
	if(buf[5] == '0' && buf[6]=='0') return 0;
	if(buf[5]=='1'){
		switch(buf[6]){
		case '3':
			utils_error("FCS error.");
			break;
		case '4':
			utils_error("Format error.");
			break;
		case '5':
			utils_error("Input parameter error.");
			break;
		case '8':
			utils_error("Frame length error.");
			break;
		}
	}else if(buf[5]=='A'){
		switch(buf[6]){
		case '3':
			utils_error("Error calculating FCS.");
			break;
		case '8':
			utils_error("Error in generating frame length.");
			break;
		}
	}
	return 1;
}

int OMRON_SECTION::invalidate_cache()
{
	memset(
		m_cacheFlags+m_curRegister,
		false,
		sizeof(m_cacheFlags[0])*m_lastReadRegisters
	);
	// increse internal OMRON_SECTION pointer
	m_curRegister += m_parent->m_iBatchCount;
	if(m_curRegister >= m_nRegisters){
		m_curRegister = 0;
	}
	return 0;
}

void OMRON_SECTION::comm_fault_handler()
{
	m_failCount++;
	if(m_failCount >= 3){
		invalidate_cache();
		m_failCount = 3;
	}
}

int OMRON_SECTION::update_cache(char * buf,int len)
{
	// check validity
	char fcs[2];
	int	ret_code;
	//int i;
	//int hex;
	//char dt[5];
	try{
		if(buf[0] != '@') {
			throw(-1);
		}
		if( check_error(buf) ) {
			throw(-2);
		}
		if(len != m_lastReadRegisters*4+11) {
			throw(-3);
		}
		if(buf[len-1] != '\r') {
			throw(-4);
		}
		if(buf[len-2] != '*') {
			throw(-5);
		}
		if(buf[3] != m_readCmdPrefix[0] || buf[4] != m_readCmdPrefix[1]) {
			throw(-6);
		}
		fcs[0]=buf[len-4];
		fcs[1]=buf[len-3];
		add_fcs_and_cr(buf,len-4);
		if( fcs[0] != buf[len-4] || fcs[1] != buf[len-3]) {
			throw(-7);
		}
		//ok,all passed
		memset(
			m_cacheFlags+m_curRegister,
			true,
			sizeof(m_cacheFlags[0])*m_lastReadRegisters
		);
		m_failCount=0;

		memcpy(m_cache + m_curRegister*4,buf+7, m_lastReadRegisters*4);
		ret_code=1;			   
	}catch(int /* err */){
		ret_code=0;
	}
	
	// increse internal OMRON_SECTION pointer
	m_curRegister += m_parent->m_iBatchCount;
	if(m_curRegister >= m_nRegisters){
		m_curRegister = 0;
	}

	return ret_code;
}

/*
	write a register into dm/ir/hr section
*/
__bool OMRON_SECTION::write_register(PCRTK_TAG tte, PCTAG_VALUE tv)
{
	hw_addr_t * addr;
	char cmd[32],buf[128];
	int l;
	float fv;
	char na[4];
	char ascValue[5];
	__u16 iValue;
	TAG_TYPE tp;

	memset(na, -1 ,4);
	addr = (hw_addr_t*)tte->d.BinaryAddress;

	if(addr->rno >= m_nRegisters){
		return __false;
	}

	m_parent->set_mode(COmronDevice::monitor_mode);
	
	ZeroMemory(cmd, sizeof(cmd));

	tp = get_value_type(tte->s.Flags);
	switch(tp){
	case dt_real4:
		fv = tv->flt;
		break;
	case dt_int32:
		iValue = (__u16)tv->i32;
		break;
	case dt_bool:
		if(-1 == addr->bno_hex){
			/* the whole register is used as a boolean */
			iValue = tv->b? 1 : 0;
		}else{
			if(m_sectionType != ost_hr_section){
				// only hr section can be written bitwise
				// just a warning : 
				// return 0;
			}
			/* bit variable */
			ascValue[4] = 0;
			memcpy(ascValue, &m_cache[addr->rno * 4], 4);
			__uint x;
			sscanf(ascValue, "%x", &x);
			iValue = x;
			if(tv->i32){
				iValue |= 1 << addr->bno_hex;
			}else{
				iValue &= ~(1 << addr->bno_hex);
			}
		}
		break;
	default:
		/* other types not supported */
		return __false;
	}

	/* compute the 16-bit register value to be written */
	switch(tp){
	case dt_real4:
		/* scaling for real numbers */
		if(addr->scaling){
			if(fabs(addr->a) > 1e-10){
				fv = (fv - addr->b) / addr->a;
			}
		}

		// convert into ascii string
		
		if(is_dm_section() && !addr->bno_hex){ 
			// bcd
			if(fv < 0 || fv > 9999){
				return 0;
			}else{
				// sprintf(cmd,"@%02d%s%04d%04.0f", m_parent->m_iUnitNo, m_writeCmdPrefix,rno,fv);
				sprintf(ascValue, "%04.0f", fv);
			}
		}else{ 
			// hex
			if(fv <0 || fv > 65535){
				return 0;
			}else{
				iValue = (short)fv;
				// sprintf(cmd,"@%02d%s%04d%04x", m_parent->m_iUnitNo, m_writeCmdPrefix,rno,usv);
				sprintf(ascValue, "%04X", iValue);
			}
		}
		break;
	case dt_int32:
	case dt_bool:
		sprintf(ascValue, "%04X", iValue);
		break;
	}


	if(m_parent->m_deviceType == COmronDevice::c1000_device &&
		m_sectionType == ost_hr_section
	){
		// fuck c1000, the documented 'WH' got
		// an '0D' error code
		sprintf(
			cmd,
			"@%02dMB0E87020003%02X01,%s",
			m_parent->m_iUnitNo,
			addr->rno,
			ascValue
			);
	}else{
		sprintf(
			cmd,
			"@%02d%s%04d%04X", 
			m_parent->m_iUnitNo, 
			m_writeCmdPrefix,
			addr->rno,
			iValue
			);
	}
	
	add_fcs_and_cr(cmd, strlen(cmd));
	
	// send the write command
	if(!lock_port(m_parent->m_iPortNo, 3000)){
		utils_error("LockOmron failed on port %d\n", m_parent->m_iPortNo);
		return __false;
	}
	
	for(int i=0; i<3; i++){
		utils_debug("WriteOmron: %s\n", cmd);
		write_port(m_parent->m_iPortNo,cmd,strlen(cmd),500);
		Sleep(250);
		l=sizeof(buf);
		// clean the response data
		ZeroMemory(buf, sizeof(buf));
		read_port(m_parent->m_iPortNo,buf,&l,500);
		utils_debug("WriteOmron returns : %s\n", buf);
		if(l > 0){
			break;
		}
	}
	
	unlock_port(m_parent->m_iPortNo);

	return __true;
}

/*
	for HR/IR section, do a force set/reset operation
	packet format :
	@  xx KS OP1 OP2 OP3 OP4 xxxx xx FCS * 0xd
	1   2   3   4----------------  5---  6   7    8  9
	1 : leading byte
	2 : unit id
	OP1/2/3/4 : operation code, 
		'CIO ' for IR
		'HR  ' for HR
	5 : word address
	6 : bit address
	7 : check sum
	8,9 : trailing bytes

	2004/7/14
	the KS primitive is documented but has no effect
	in experiment, fuck omron.

	so we have to do a `read/set(clear) bit/write' sequence

	this function is obsolete.
*/
__bool OMRON_SECTION::write_bit(__uint wordAddr, __uint bitAddr, __bool value)
{
	char cmdBuf[48];
	char responseBuf[32];
	int l;
	char * kskr = value? "KS" : "KR";

	if(ost_hr_section == m_sectionType){
		sprintf(
			cmdBuf, 
			"@%02d%sHR  %04d%02d", 
			m_parent->m_iUnitNo, 
			kskr,
			wordAddr, 
			bitAddr
			);
	}else if(ost_ir_section == m_sectionType){
		sprintf(
			cmdBuf, 
			"@%02d%sCIO %04d%02d", 
			m_parent->m_iUnitNo, 
			kskr,
			wordAddr, 
			bitAddr
			);
	}else{
		return __false;
	}
	add_fcs_and_cr(cmdBuf, strlen(cmdBuf));
	if(!lock_port(m_parent->m_iPortNo, 2000)){
		return __false;
	}
	utils_debug("WriteOmron: %s\n", cmdBuf);
	write_port(m_parent->m_iPortNo, cmdBuf, strlen(cmdBuf), 100);
	Sleep(60);
	l = sizeof(responseBuf);
	// clean the response data
	ZeroMemory(responseBuf, sizeof(responseBuf));
	read_port(m_parent->m_iPortNo, responseBuf, &l, 100);
	utils_debug("WriteOmron returns : %s\n", responseBuf);
	unlock_port(m_parent->m_iPortNo);

	return __true;
}

void OMRON_SECTION::update_tag(PCRTK_TAG tte, pmc_value_t & pt)
{
	//	register no, bit  no
	hw_addr_t * addr;
	char dt[5];
	int	ival;
	__r4 fv;

	char na[4];
	memset(na, -1, 4);

	addr = (hw_addr_t*)tte->d.BinaryAddress;
	
	if(addr->rno<0 || addr->rno>=m_nRegisters){
		return;
	}

	dt[4]=0;
	memcpy(dt, &m_cache[addr->rno*4], 4);

	pt.Flags &= ~TF_Valid;
	pt.Flags |= m_cacheFlags[addr->rno]? TF_Valid : 0;
	if(pt.Flags & TF_Valid){
		/* cast to desired type */
		switch(get_value_type(tte->s.Flags)){
		case dt_bool:
			if(addr->bno_hex > 15){ 
				//register digital value
				pt.Value.b = atoi(dt) ? 1 : 0;
			}else{
				// bit digital value
				// flags=(int)(((short*)m_cache)[rno]);
				// pt.Value.iValue=flags & (1<<bno) ? true : false;				
				sscanf(dt, "%x", &ival);
				pt.Value.b=ival & (1<<addr->bno_hex) ? 1 : 0;				
			}
			break;
			
		case dt_real4:
			if(!addr->bno_hex){
				/* BCD format real number */
				fv = (__r4)atof(dt);
			}else{ // hex
				sscanf(dt, "%x", &ival);
				fv = ival;
			}
			if(addr->scaling){
				fv = addr->a * fv + addr->b;
			}
			pt.Value.fltValue = fv;
			break;
						
		case dt_int32:
			if(addr->bno_hex == 0){
				/* BCD format integer number */
				ival = atoi(dt);
			}else{ 
				// hex
				sscanf(dt, "%x", &ival);
			}
			pt.Value.iValue = ival;
			break;
			
		default:
			/* other types not supported */
			pt.Flags &= ~TF_Valid;
			break;
		}
	}else{
		// debugBreak()
#ifndef NDEBUG
		fv = fv;
#endif
	}
}

void OMRON_SECTION::check_state()
{
	char cmd[32];
	char buf[128];
	int	 l;
	sprintf(cmd,"@%02dMS", m_parent->m_iUnitNo);
	add_fcs_and_cr(cmd,5);
	write_port(m_parent->m_iPortNo,cmd,9,100);
	Sleep(60);
	l=sizeof(buf);
	read_port(m_parent->m_iPortNo,buf,&l,10);
	if(!l) {			
		return;
	}
#if 0
	if(strncmp(buf, "@%02dMS0003", m_parent->m_iUnitNo, 9)){
		sprintf(cmd, "@%02dSC02", m_parent->m_iUnitNo);
		add_fcs_and_cr(cmd,7);
		write_port(m_parent->m_iPortNo,cmd,11,100);
		Sleep(200);
		l=sizeof(buf);
		read_port(m_parent->m_iPortNo,buf,&l,200);
	}
#endif
}

int OMRON_SECTION::read_section_phase_1()
{
	char cmd[32];		
	
	if(m_sectionType == ost_dm_section){
		check_state();
	}

	if(m_nRegisters >= m_curRegister + m_parent->m_iBatchCount){
		m_lastReadRegisters = m_parent->m_iBatchCount;
	}else{
		m_lastReadRegisters = m_nRegisters - m_curRegister;			
	}
	sprintf(
		cmd,"@%02d%s%04d%04d",
		m_parent->m_iUnitNo, 
		m_readCmdPrefix,
		m_curRegister,
		m_lastReadRegisters
		);		
	add_fcs_and_cr(cmd,13);
	// utils_trace("%s\n", cmd);
	write_port(m_parent->m_iPortNo,cmd, 17, 10);

	return 1;
}

/* 从 Omron PLC 读取数据 */
void OMRON_SECTION::read_section_phase_2()
{
	char buf[8192];
	int	 len;

	len = sizeof(buf);

	read_port(m_parent->m_iPortNo, buf, &len, 250);

	if(len>0){	
		len = update_cache(buf,len);
	}
	
	if(!len){
		comm_fault_handler();
	}
}

void COmronDevice::pre_run()
{
	set_mode(monitor_mode);
}

void COmronDevice::task()
{	 
	OMRON_SECTION * section;
   
	if(get_power_state() != PWR_RUNNING){
		return;
	}
	section = m_pSections[m_iCurrentSection];
	if(section->m_nRegisters){
		if(!lock_port(m_iPortNo, 500)){
			return;
		}
		section->read_section_phase_1();
		rtk_sleep(m_iDelay[m_iCurrentSection]);
		section->read_section_phase_2();
		unlock_port(m_iPortNo);
	}
	m_iCurrentSection++;
	if(m_iCurrentSection == 3){
		m_iCurrentSection = 0;
	}
}

COmronDevice::device_mode_t COmronDevice::get_mode()
{
	char cmd[32];
	char buf[128];
	int  l;
	int mode;
	
	sprintf(cmd,"@%02dMS", m_iUnitNo);
	add_fcs_and_cr(cmd,5);
	write_port(m_iPortNo,cmd,9,100);
	Sleep(60);
	l=sizeof(buf);
	read_port(m_iPortNo,buf,&l,10);
	if(!l) {			
		return unknown_mode;
	}
	if(l != 15){
		return unknown_mode;
	}

	buf[9] = 0;
	sscanf(buf + 7, "%x", &mode);
	switch(mode & 0x3){
	case 0:
		return program_mode;
	case 2:
		return run_mode;
	case 3:
		return monitor_mode;
	}
	
	return unknown_mode;
}

void COmronDevice::set_mode(COmronDevice::device_mode_t  newMode)
{
	// put the device into motoring mode
	char cmd[32];
	int sz;
	__u16 mode;

	switch(newMode){
	case run_mode:
		mode = 3;
		break;
	case program_mode:
		mode = 0;
		break;
	case monitor_mode:
		mode = 2;
		break;
	default:
		return;
	}
	
	sprintf(cmd, "@%02dSC%02d", m_iUnitNo, mode);
	add_fcs_and_cr(cmd, 7);
	lock_port(m_iPortNo, 1000);
	write_port(m_iPortNo, cmd, 11, 0);
	rtk_sleep(500);
	sz = sizeof(cmd);
	read_port(m_iPortNo, cmd, &sz, 0);
	unlock_port(m_iPortNo);
}

int COmronDevice::config(int c, char **v)
{
	int dm, hr, ir, j, wakeup;

	wakeup = DEFAULT_WAKEUP;
	m_iBatchCount = DEFAULT_BATCH_COUNT;
	dm=200,hr=100,ir=60;
	m_iDelay[0]=m_iDelay[1]=m_iDelay[2]=150;
	m_iUnitNo = 0;

	for(j=0; j<c; j++){
		if(!strnicmp(v[j], "wakeup=", 7)){
			wakeup = atoi(v[j] + 7);
			if(wakeup < 0){
				utils_error(">> Omron %d, Wakeup=%d invalid, set to %d.\n",
					m_iPortNo, DEFAULT_WAKEUP);
				wakeup = DEFAULT_WAKEUP;
			}
		}else if(!strnicmp(v[j],"dm=",3)){					  
			dm=atoi(v[j]+3);
		}else if(!strnicmp(v[j],"hr=",3)){
			hr=atoi(v[j]+3);
		}else if(!strnicmp(v[j],"ir=",3)){
			ir=atoi(v[j]+3);
		}else if(!strnicmp(v[j],"dmtime=",7)){
			m_iDelay[0]=atoi(v[j]+7);
			if(m_iDelay[0]<=0) {
				utils_error(
					">> omron,port%d,dmtime=%d is invalid,set to 150.\n",
					m_iPortNo, m_iDelay[0]
					);
				m_iDelay[0]=150;
			}
		}else if(!strnicmp(v[j],"hrtime=",7)){
			m_iDelay[1]=atoi(v[j]+7);
			if(m_iDelay[1]<=0) {
				utils_error(
					">> omron,port%d,dmtime=%d is invalid,set to 150.\n",
					m_iPortNo,m_iDelay[1]
					);
				m_iDelay[1]=150;
			}
		}else if(!strnicmp(v[j],"irtime=",7)){
			m_iDelay[2]=atoi(v[j]+7);
			if(m_iDelay[2]<=0) {
				utils_error(
					">> omron, port%d,dmtime=%d is invalid,set to 150.\n",
					m_iPortNo, 
					m_iDelay[2]
					);
				m_iDelay[2]=150;
			}
		}else if(!strnicmp(v[j], "unit=", 5)){
			m_iUnitNo = atoi(v[j] + 5);
			if(m_iUnitNo < 0 || m_iUnitNo > 99){
				utils_error(
					">> omron, port%d, unitNo=%d invalid.\n",
					m_iPortNo,
					m_iUnitNo
					);
				m_iPortNo = 0;
			}
		}else if(!strnicmp(v[j], "batch=", 6)){
			m_iBatchCount = atoi(v[j] + 5);
			if(m_iBatchCount < 0 || m_iBatchCount > 30){
				utils_error(
					">> Omron, port%d, batch=%d invalid.\n",
					m_iPortNo,
					m_iBatchCount
					);
				m_iBatchCount = DEFAULT_BATCH_COUNT;
			}
		}else if(!strnicmp(v[j], "device=", 7)){
			const char * dt = v[j] + 7;
			if(!strcmpi(dt, "c200")){
				m_deviceType = c200_device;
			}else if(!strcmpi(dt, "c1000")){
				m_deviceType=  c1000_device;
			}else if(!strcmpi(dt, "c2000")){
				m_deviceType = c2000_device;
			}
		}
	}

	m_dwPeriod = wakeup;

	dmSection.m_parent = this;
	hrSection.m_parent = this;
	irSection.m_parent = this;

	dmSection.config(dm, m_iDelay[0]);
	hrSection.config(hr, m_iDelay[1]);
	irSection.config(ir, m_iDelay[2]);

	utils_trace(">> Ok, port %d, OMRON-PLC connected.\n", m_iPortNo);

	return 1;
}

IOSS_DLL_EXPORT __bool start_device(
	PDEVICE_INFO dev
	)
{
	COmronDevice * devobj;

	char * address = dev->address;
	char * parameter = dev->parameter;
	int pno;
	CArgs args;
	if(strlen(address) < 4){
		return __false;
	}
	if(strnicmp(address, "com", 3)){
		return __false;
	}
	pno = atoi(address + 3);
	if(pno <1 || pno > MAX_PORTS){
		return __false;
	}

	devobj = new COmronDevice(pno);
	if(!devobj){
		utils_error(">> Omron, new %d failed.\n", pno);
		return __false;
	}
	devobj->m_Handle = dev;
	dev->OwnerField = devobj;
	parse_arg_ex(parameter, &args, ",;");
	
	if(!devobj->config(args.argc, args.argv)){
		delete devobj;
		return __false;
	}	

	if(!devobj->start()){
		delete devobj;
		return __false;
	}
	
	return __true;
}

IOSS_DLL_EXPORT __bool stop_device(
	PDEVICE_INFO handle
	)
{
	COmronDevice * d;
	
	d = (COmronDevice*)handle->OwnerField;

	d->stop(INFINITE);
	
	delete d;

	return __true;
}

/*

	adress format:

	ADDRESS_DECLARATION ::=
		SECTION '.' REGISTER_NO ['.' BIT_NO] |
		SECTION '.' REGISTER_NO ['.' (bcd|hex).[a/b]]

	SECTION ::= dm | hr | ir

	BinaryAddress allocate:
		
		0 : bScale
		1 : sno
		2 : rno
		3 : bno (or format DM only)
		4 - 7  : a
		8 - 11 : b
*/
IOSS_DLL_EXPORT __bool address_translate(
	PRTK_TAG tte
	)
{
	CArgs args;
	int sno,rno,bno;
	bool b_scale=false;
	OMRON_SECTION * sec;
	float fa,fb;
	COmronDevice *port;
	int end;
	TAG_TYPE tp;

	parse_arg_ex(tte->s.Address, &args, ". ");

	//预先假定为非法地址
	memset(tte->d.BinaryAddress, -1, sizeof(tte->d.BinaryAddress));

	tp = get_value_type(tte->s.Flags);
	if(tp != dt_bool && tp != dt_real4 && tp != dt_int32){
		return __false;
	}
	
	if(args.argc < 2){
		//must contain at least a register number field
		return __false;
	}
	sno = rno = bno = -1;
	port = (COmronDevice*)tte->d.DeviceObj->OwnerField;
	if( !port ){
		return __false;
	}
	if(!strcmpi(args.argv[0],"dm")){
		sno=ost_dm_section;
	}else if(!strcmpi(args.argv[0],"hr")){
		sno=ost_hr_section;
	}else if(!strcmpi(args.argv[0],"ir")){
		sno=ost_ir_section;
	}else{
		return __false;
	}
	
	sec=port->m_pSections[sno];
	if(!sec){
		return __false;
	}

	// expect register number
	rno=atoi(args.argv[1]);
	if(rno<0 || rno>=100 || rno>=sec->m_nRegisters){
		return __false;
	}

	// expect bit number or 'bcd', 'hex'
	if(args.argc == 2){
		// is a analog value, default to 'hex'
		bno = 1;
	}

	if(args.argc > 2){
		if(isdigit(args.argv[2][0])){
			// only digital tags can be specified with a bit number field
			if(tp != dt_bool){
				return __false;
			}
			// logical tag
			bno=atoi(args.argv[2]);
			if(bno>=16){
				return __false;
			}
		}else{
			// analog tag
			if(tp == dt_bool){
				return __false;
			}
			if(0 == strcmpi(args.argv[2], "bcd")){
				bno=0;
			}else if(0 == strcmpi(args.argv[2], "hex")){
				bno=1;
			}else{
				// default to 'bcd'
				bno = 0;
			}
			/* is there anything to the end of the string? */
			end = args.arg_idx[2] + strlen(args.argv[2]) + 1;
			if(tte->s.Address[end]){
				CArgs argsAb;
				//got ax+b
				parse_arg_ex(
					tte->s.Address + end,
					&argsAb,
					"/ "
					);
				if(argsAb.argc == 2){
					fa=atof(argsAb.argv[0]);
					fb=atof(argsAb.argv[1]);
					if(fabs(fa) > 1e-10){
						b_scale = true;
					}else{
						return __false;
					}
				}
			}
		}
	}

	hw_addr_t * addr = (hw_addr_t*)tte->d.BinaryAddress;
	addr->sno = sno;
	addr->rno = rno;
	addr->bno_hex = bno;
	addr->scaling = b_scale;
	addr->a = fa;
	addr->b = fb;	

	return __true;
}

IOSS_DLL_EXPORT __bool write_device(
	PRTK_TAG tte, 
	PCTAG_VALUE tv
	)
{
	hw_addr_t * addr = (hw_addr_t*)tte->d.BinaryAddress;

	if(addr->sno >= ost_max_section){
		return __false;
	}
	
	//	sno<ost_dm_section || sno>=ost_ir_section){
	COmronDevice * port = (COmronDevice*)tte->d.DeviceObj->OwnerField;
	if(!port){
		return __false;
	}
	OMRON_SECTION * sec = port->m_pSections[addr->sno];
	__bool res = sec->write_register(tte, tv);
	
	return res;
}

IOSS_DLL_EXPORT void update_tag(
	PCRTK_TAG tte, 
	pmc_value_t * pt, 
	PCRTK_TIME now
	)
{
	COmronDevice  * d;
	OMRON_SECTION * sec;
	hw_addr_t * addr;

	d = (COmronDevice*)tte->d.DeviceObj->OwnerField;

	addr = (hw_addr_t*)tte->d.BinaryAddress;
	switch(addr->sno){
	case ost_dm_section:
		sec = &d->dmSection;
		break;
	case ost_hr_section:
		sec = &d->hrSection;
		break;
	case ost_ir_section:
		sec = &d->irSection;
		break;
	default:
		sec = 0;
	}

	if(sec){
		sec->update_tag(tte, *pt);
	}
}
