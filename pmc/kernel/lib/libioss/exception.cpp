/********************************************************************
	PC-Based monitoring & controlling system source
	prodoct version : 2.03
	filename:	E:\vss\pmc2\src\pmcd\alarm.cpp
	file path:	E:\vss\pmc2\src\pmcd
	author:		Jackie Pan, jhunter@tsinghua.org.cn
	
	purpose :	This module provide support alarm checking/raising
	history :
	created :	by J.Hunter,jhunter@263.net,May 2001
	revised :	10:10:2002	 16:11
	2003/5/22	Jackie, master/slave mode support added
*********************************************************************/
#include "precomp.h"

#include <math.h>
#include <string>
#include <time.h>

#ifdef _WIN32
#pragma comment(linker, "/base:0x76530000")
#endif

#define UTILS_NODEBUG

static std::string texttime()
{
#ifdef _WIN32
	#define localtime(a,b) *(b)=*localtime(a)
#else	
	#define localtime(a,b) localtime_r(a,b)
#endif
	time_t tmt;
	struct tm ltm;
	time(&tmt);
	localtime(&tmt, &ltm);
	char buf[128];	  
	sprintf(
		buf,
		"%d年%d月%d日 %02d:%02d:%02d",
		ltm.tm_year+1900,
		ltm.tm_mon+1,
		ltm.tm_mday,
		ltm.tm_hour,
		ltm.tm_min,
		ltm.tm_sec
		);
#ifndef _WIN32
	#undef localtime
#endif	  
	return std::string(buf);
}

/*
	given an alarm condition, and a alarm mask
	check if the mask if effective.
	in previous version (GD99 project)
	the alarm mask is an integer, so only a bitwise and
	will be ok, but now the mask is a structure, we have
	to use a switch..case... block to do the save work.
	returns:
		true : if the alarm should be _masked(not to raise alarm)
		false: if the alarm should not be _masked(raise alarm)
*/
static bool _masked(__uint a_mask, ALARM_TYPE at)
{
	bool m=false;
	switch(at){
	case AT_HiHi:
		m=a_mask & TF_HiHi? true : false;
		break;
	case AT_Hi:
		m=a_mask & TF_Hi? true : false;
		break;
	case AT_Lo:
		m=a_mask & TF_Lo? true : false;
		break;
	case AT_LoLo:
		m=a_mask & TF_LoLo? true : false;
		break;
	case AT_On2Off:
		m=a_mask & TF_On2Off? true : false;
		break;
	case AT_Off2On:
		m=a_mask & TF_Off2On? true : false;
		break;
	case AT_SharpChange:
		m=a_mask & TF_Rate? true : false;
		break;
	}
	return m;
}

/*
	check alarm for analog tags
*/
static int _get_exception_analog(
	RTK_TAG * tte, 
	PCpmc_value_t val, 
	PCRTK_TIME now
	)
{
	bool alarm_masked=false;
	RTK_TAG * cutoff;
	TAG_FLAGS af;
	TAG_FLAGS gf;
	int  at,at_old;

	pmc_value_t Value, OldValue;	
	__r8 span;
	__r8 hihi, hi, lo, lolo;
	__r8 deadband;

	af = tte->s.Flags;
	gf = tte->d.Value.Flags;
	at_old = tte->d.AlarmStatus;
	
	at = AT_NoAlarm;
	
	Value.Flags = OldValue.Flags = dt_real4;
	pmc_type_cast(val, &Value);
	pmc_type_cast(&tte->d.Value, &OldValue);
	
	switch(get_value_type(tte->s.Flags)){
	case dt_real4:
	case dt_real8:
	case dt_int64:
	case dt_uint64:
		span = fabs(tte->s.fltMaxValue-tte->s.fltMinValue);
		hihi = tte->s.fltHiHi;
		hi = tte->s.fltHi;
		lo = tte->s.fltLo;
		lolo = tte->s.fltLoLo;
		deadband = tte->s.fltAlarmDeadband;
		break;

	case dt_int32:
	case dt_int16:
	case dt_int8:
	case dt_uint32:
	case dt_uint16:
	case dt_uint8:
		span = abs(tte->s.u_max.i - tte->s.u_min.i);
		hihi = tte->s.u_hihi.i;
		hi = tte->s.u_hi.i;
		lo = tte->s.u_lo.i;
		lolo = tte->s.u_lolo.i;
		deadband = tte->s.u_deadband.i;
		break;
		
	default:
		assert(0);
	}

	if(span < 1e-5){
		span = 10;
	}
	
	/* alarm dead-band */
	__r8 foo;
	foo = deadband * span /100;
	if( (af & TF_HiHi) && Value.Value.flt > hihi){
		tte->d.Value.Flags |= TF_HiHi;
		at=AT_HiHi;
	}else if( (af & TF_Hi) && Value.Value.flt > hi){
		tte->d.Value.Flags |= TF_Hi;
		if(at_old==AT_HiHi && Value.Value.flt > hihi - foo){
			at=AT_HiHi;
		}else{
			at=AT_Hi;
		}
	}else if((af & TF_LoLo) && Value.Value.flt < lolo){
		tte->d.Value.Flags |= TF_LoLo;
		at=AT_LoLo;
	}else if((af & TF_Lo) && Value.Value.flt < lo){
		tte->d.Value.Flags |= TF_Lo;
		if(at_old==AT_LoLo && Value.Value.flt < lolo + foo){
			at=AT_LoLo;
		}else{
			at=AT_Lo;
		}
	}else{
		if(at_old==AT_Lo && Value.Value.flt < lo+ foo){
			at=AT_Lo;
		}else if(at_old==AT_Hi && Value.Value.flt > hi - foo){
			at=AT_Hi;
		}
	}
	
	__r8 seconds = rtk_time_diff(now, &tte->d.Time);
	if( (gf & TF_Valid) && span > 1e-5 && seconds > 1e-5){
		__r8 rate;
		__r8 dev;
		dev = fabs (Value.Value.flt -OldValue.Value.flt);
		rate = dev /span*100;
		rate=(float)fabs(rate/seconds);
		if((rate > tte->s.fltRate) && (af & TF_SharpChange)){
			tte->d.Value.Flags |= TF_SharpChange;
			at = AT_SharpChange;
		}
		// TODO: Uncomment this when we provide HMI for
		// TODO: the ExcDev and ExcMax, for now, ExcDev and
		// TODO: ExcMax are specified globally for all tags
#if 0
		if(dev > tte->s.ExcDev){
			tte->d.Value.Flags |= TF_Rate;
		}
#else
		if(tte->s.Flags & TF_Step){
			if(dev > span){
				tte->d.Value.Flags |= TF_Rate;
			}
		}else {
			if(dev*100 > span * g_fltMaxChangeRate){
				tte->d.Value.Flags |= TF_Rate;
			}
		}
#endif
	}

#if 0
	if(seconds > tte->s.ExcMax){
			tte->d.Value.Flags |= TF_Expired;
	}
#else
	if((seconds > g_fltTagLife/2.) || (seconds < -g_fltTagLife/2.)){
		tte->d.Value.Flags |= TF_Expired;
	}
#endif

	/* get locking tag's address */
	if(tte->s.CutOffTagName.group.Data[0]){
		cutoff = query_tag(HNODE_LOCAL_MACHINE, &tte->s.CutOffTagName);
	}else{
		cutoff = 0;
	}
	
	if(cutoff && (at!=AT_NoAlarm) ){
		/* check cut off condition */
		if(_masked(tte->s.CutOffMask, cutoff->d.AlarmStatus)){
			/*
			when cutoff is in any alarm state indicated by
			tte->AlarmMask, the alarm will be _masked out
			*/
			alarm_masked=true;
		}
	}
	
	/*
		ok, we reach here
		now, the new flags of the tag have been set
		new tagtime NOT set(i feel it would be better to set it out somewhere,
		say,in the WriteTag(...))
		ready? then we return with the new alarm status
	*/
	if(alarm_masked) {
		return AT_NoAlarm;
	}

	return at;
}

/*
	check alarm for logical tags
*/
static int _get_exception_bool(RTK_TAG * tte, const TAG_VALUE * val)
{
	bool				alarm_masked=false;
	RTK_TAG				*cutoff;
	TAG_FLAGS			af, gf;
	ALARM_TYPE			at;

	gf = tte->d.Value.Flags;
	
	/* get locking tag's address */
	if(tte->s.CutOffTagName.group.Data[0]){
		cutoff=query_tag(HNODE_LOCAL_MACHINE, &tte->s.CutOffTagName);
	}else{
		cutoff=0;
	}
	af=tte->s.Flags;

	at=AT_NoAlarm;	  

	/* check general flags */
	if(val->b){
		if(af & TF_Off2On){
			at=AT_Off2On;
			tte->d.Value.Flags |= TF_Off2On;
		}
	}else{
		if(af & TF_On2Off){
			at=AT_On2Off;
			tte->d.Value.Flags |= TF_On2Off;
		}
	}

	if(gf & TF_Valid){
		if(val->b ^ tte->d.Value.Value.b){
			tte->d.Value.Flags |= TF_Expired;
		}
	}
	
	if(cutoff && at!=AT_NoAlarm){
		/* check cut off condition */
		if(_masked(tte->s.CutOffMask,cutoff->d.AlarmStatus)){
			/*
			when cutoff is in any alarm state indicated by
			tte->AlarmMask, the alarm will be _masked out
			*/
			alarm_masked=true;
		}
	}

	if(alarm_masked) {
		return AT_NoAlarm;
	}

	return at;
}

/*
	this function is to generate an alarm packet on the network
	inputs:
		gk -- group key of the tag
		tk -- tag key of the tag
		ac -- alarm class
		at -- alarm type
		val -- new value of the alarm, will be used as alarm parameter
*/
static int _send_alarm(
	const GROUP_KEY * gk, 
	RTK_TAG * tte, 
	ALARM_CLASS ac, 
	ALARM_TYPE at, 
	PCpmc_value_t val
	)
{
	int			res;
	char		buf[2048];
	RTK_ALARM_PACKET &ap = *((RTK_ALARM_PACKET *)buf);

	/*
		the line below indicates that this packet is from a PCMS server.
		in this version of PCMS daemon, the servers are unaware
		of what NodeKeys they are assigned, only clients know
		this information.
		So, setting the nodekey to a null string helps the codes who
		receive the alarm packets to identify if the incoming alarm
		is an Alarm(sent by server) or an alarm confirmation (by
		some clients)
	*/
	ap.Tag.node.Data[0] = 0;
	ap.Tag.sname.group = *gk;
	ap.Tag.sname.tag = tte->key;
	ap.Class = ac;
	ap.Rank = tte->s.AlarmRank;
	ap.Value = val->Value;

	/* since Jul 11,2001, alarm is formatted into a message string */
	/*
		报警信息格式：

		1 开关量：
		时间，名称（中文），报警信息，状态,(操作员站：)
		其中报警信息由组态确定（OnMsg, OffMsg）

		2 模拟量：
		时间，变量名，当前值，报警属性（高高、高、低、低低、速率），
		状态（报警、撤消、操作）,(操作员站：)
	*/
	const char * strCls= ac==AC_Alarm? "报警" : 
		ac==AC_CancelAlarm? "取消" :
		ac==AC_AckAlarm? "确认" : "";	 
	
	char * _name,name[128];
	if(0 && strlen(tte->s.Description) < 32){		
		memset(name,' ',sizeof(name));
		strncpy(name,tte->s.Description,strlen(tte->s.Description));
		name[sizeof(name) - 1] = 0;
		_name=name;
	}else{
		_name=tte->s.Description;
	}
	if(get_value_type(tte->s.Flags) == dt_bool){
		const char *strAt;
		strAt = at == AT_DFault? "数据采样失败" :
			at == AT_On2Off? tte->s.SwitchMsg.OffMsg : tte->s.SwitchMsg.OnMsg,
		sprintf(ap.Msg,"%s;%s(%s.%s.%s);%s;%s",
			texttime().data(),
			_name,
			(char*)CHostName(g_ThisNode->key),
			(char*)CGroupName(tte->group),
			(char*)CTagName(tte->key),
			strAt,
			strCls
			);
	}else{
		const char * strAt;
		strAt=at==AT_HiHi? "高高报警":
		at==AT_Hi? "高报警":
		at==AT_Lo? "低报警":
		at==AT_LoLo? "低低报警":
		at==AT_SharpChange? "速率报警":
		at==AT_DFault? "数据采样失败" :
		"";
		pmc_value_t valueStr;
		set_value_type(valueStr.Flags, dt_string);
		pmc_type_cast(val, &valueStr);
		sprintf(
			ap.Msg,
			"%s;%s(%s.%s.%s);%s %s;%s;%s;",
			texttime().data(),_name,
			(char*)CHostName(g_ThisNode->key),
			(char*)CGroupName(tte->group),
			(char*)CTagName(tte->key),
			valueStr.Value.str? valueStr.Value.str : "(<Unknown>)",
			tte->s.AnalogMsg.EU,
			strAt, strCls
			);
		pmc_clear(&valueStr);
	}	 

	res = broadcast_rtk_data(
		vbus_alarm, 
		PORT_ALL_CLIENT, 
		PT_Alarm,
		&ap, 
		sizeof(RTK_ALARM_PACKET)+strlen(ap.Msg)+1
		);
#if 0
	//if(debug_level >= dbg_level_trace){
		utils_debug(
			"Raise alarm Tag:%s.%s,%s\n",
			(char *)CGroupName(*gk),
			(char *)CTagName(tte->key),
			ap.Msg
		);
	//}
#endif

	return res;
}

#define ALARM_FLAGS \
	(TF_SharpChange | TF_HiHi | TF_Hi | TF_Lo |TF_LoLo | TF_On2Off | TF_Off2On)

/*
	This function is called whenver a new value is
	written to a tag in the system database.
	
	It checks various conditions to see if an alarm
	is to be generated, if yes, the alarm is sent over
	the network, using the alarming channel, which is
	is multicast channel, otherwise nothing is done.

	This function will also determine if an exception
	is to be generated, and set the various flags,
	these flags will guide the IOSS to keep the
	distributed database synchronized.

	returns : 1 -- if alarm is raised
			  0 -- if no alarm is to be raised
	inputs	:
*/
int PMC_API get_exception(
	const GROUP_KEY * gk, 
	PRTK_TAG tte, 
	PCpmc_value_t val, 
	PCRTK_TIME now
	)
{
	int at,at_old;
	at_old = tte->d.AlarmStatus;

	// clear some flags, then we'll re-generate them if necessary
	tte->d.Value.Flags &= ~(ALARM_FLAGS | TF_Rate | TF_Expired);
	
	/* case 1, valid flag changes --> broadcast it */
	if( (val->Flags & TF_Valid) ^ (tte->d.Value.Flags & TF_Valid)){
		tte->d.Value.Flags |= TF_Expired;
	}

	__r8 seconds = rtk_time_diff(now, &tte->d.BroadcastTime);
	if((seconds > g_fltTagLife/2.) || (seconds < -g_fltTagLife/2.)){
		tte->d.Value.Flags |= TF_Expired;
	}
	
	if(val->Flags & TF_Valid){
		switch(get_value_type(tte->s.Flags)){
			
		case dt_bool:
			// most likely branch
			at=_get_exception_bool(tte, &val->Value);
			break;

		case dt_date:
			at = 0;
			break;

		default:		
			at=_get_exception_analog(tte, val, now);
			break;
		}
	}else{
		at = AT_DFault;
	}

	/* ok, set new alarm status */
	tte->d.AlarmStatus = at;

#if 0
	if(!(tte->d.Value.Flags & TF_Shutdown)){
		if(at != at_old){
			/* the same type of alarm will not be reported twice*/
			if(at == AT_NoAlarm){
				/* cancel alarm */
				if(at_old != AT_DFault){
					_send_alarm(gk, tte, AC_CancelAlarm, at_old, val);
				}
			}else{
				if(at != AT_DFault){
					_send_alarm(gk, tte, AC_Alarm, at, val);
				}else if(tte->s.Flags & TF_AlarmIfNA){
					_send_alarm(gk, tte, AC_Alarm, at, val);
				}
			}
		}
	}else{
		if(tte->d.Value.Flags & TF_Valid){
			tte->d.Value.Flags |= TF_Expired;
		}
	}
#endif

	return at;
}
