/* 
 * rtc.c - Real Time Clock for IBM AT compatible PC. 
 * 
 * Derived from Linux kernel source code (linux/kernel/time.c).   
 * See also DS12887 (or MC146818) data sheets. 
 * 
 * $Id: rtc.c,v 1.3 1997/07/10 18:17:28 dzhu Exp $ 
 */
#include <vxWorks.h> 
#include <sysLib.h> 
#include <time.h>
#include "rtc.h" 


/* Converts Gregorian date to seconds since 1970-01-01 00:00:00. 
 * Assumes input in normal date format, i.e. 1980-12-31 23:59:59 
 * => year=1980, mon=12, day=31, hour=23, min=59, sec=59. 
 * 
 * [For the Julian calendar (which was used in Russia before 1917, 
 * Britain & colonies before 1752, anywhere else before 1582, 
 * and is still in use by some communities) leave out the 
 * -year/100+year/400 terms, and add 10.] 
 * 
 * This algorithm was first published by Gauss (I think). 
 * 
 * WARNING: this function will overflow on 2106-02-07 06:28:16 on 
 * machines were long is 32-bit! (However, as time_t is signed, we 
 * will already get problems at other places on 2038-01-19 03:14:08) 
 */ 
static unsigned long convertTime(unsigned int year, unsigned int mon, 
                                 unsigned int day, unsigned int hour, 
                                 unsigned int min, unsigned int sec) 
{ 
    if (0 >= (int) (mon -= 2)) {     /* 1..12 -> 11,12,1..10 */ 
        mon += 12;      /* Puts Feb last since it has leap day */ 
        year -= 1; 
    } 
    return 
        ((((unsigned long)(year/4 - year/100 + year/400 + 367*mon/12 + day) 
           + year*365 - 719499 
           )*24 + hour /* now have hours */ 
          )*60 + min /* now have minutes */ 
         )*60 + sec; /* finally seconds */ 
} 

static unsigned long dayOfTheYear (int year, int mon, int day) 
{   
    /* Days since Jan. 1 in non-leap yr */ 
    static unsigned short jdays[12] = { 
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 }; 

    /* leap year is divisible by 4 but not by 100, or by 400 */ 
    return ( jdays[mon-1] + day 
             + ((( (((year%4) == 0) && ((year%100) != 0)) 
                   || ((year%400) == 0)) 
                && (mon>2)) ? 1 : 0) ); 
} 


int rtc_settime (const struct tm *tp) 
{ 
	unsigned char save_control; 
	int year,mon,day,hour,min,sec;

	save_control = CMOS_READ(RTC_CONTROL); /* tell the clock it's being set */ 
	// save_control |= RTC_DM_BINARY;
	CMOS_WRITE((save_control|RTC_SET), RTC_CONTROL); 

	year=tp->tm_year;
	mon=tp->tm_mon+1;
	day=tp->tm_mday;
	hour=tp->tm_hour;
	min=tp->tm_min;
	sec=tp->tm_sec;
	if(year>=100)
		year-=100;
	if (!(save_control & RTC_DM_BINARY)){ 
		year=BIN_TO_BCD(year);
		mon=BIN_TO_BCD(mon);
		day=BIN_TO_BCD(day);
		hour=BIN_TO_BCD(hour);
		min=BIN_TO_BCD(min);
		sec=BIN_TO_BCD(sec);
	}
	CMOS_WRITE(sec, RTC_SECONDS); 
	CMOS_WRITE(min, RTC_MINUTES); 
	CMOS_WRITE(hour, RTC_HOURS); 
	CMOS_WRITE(day, RTC_DAY_OF_MONTH); 
	CMOS_WRITE(mon, RTC_MONTH); 
	CMOS_WRITE(year, RTC_YEAR); 

	CMOS_WRITE(save_control, RTC_CONTROL);

	return OK; 
} 


int rtc_gettime (struct tm *tp) 
{ 

    /* should check UIP for the most consistent time reading */ 
#if 0 
    int i; 
    /* The Linux interpretation of the CMOS clock register contents: 
     * When the Update-In-Progress (UIP) flag goes from 1 to 0, the 
     * RTC registers show the second which has precisely just started. 
     * Let's hope other operating systems interpret the RTC the same way. 
     */ 
    /* read RTC exactly on falling edge of update flag */ 
    for (i = 0 ; i < 1000000 ; i++)  /* may take up to 1 second... */ 
        if (CMOS_READ(RTC_FREQ_SELECT) & RTC_UIP) 
            break; 
    for (i = 0 ; i < 1000000 ; i++)  /* must try at least 2.228 ms */ 
        if (!(CMOS_READ(RTC_FREQ_SELECT) & RTC_UIP)) 
            break; 
#endif

    tp->tm_sec = CMOS_READ(RTC_SECONDS); 
    tp->tm_min = CMOS_READ(RTC_MINUTES); 
    tp->tm_hour = CMOS_READ(RTC_HOURS); 
    tp->tm_mday = CMOS_READ(RTC_DAY_OF_MONTH); 
    tp->tm_mon = CMOS_READ(RTC_MONTH); 
    tp->tm_year = CMOS_READ(RTC_YEAR); 
    tp->tm_wday = CMOS_READ(RTC_DAY_OF_WEEK); 

    if (!(CMOS_READ(RTC_CONTROL) & RTC_DM_BINARY)) { 
        tp->tm_sec = BCD_TO_BIN(tp->tm_sec); 
        tp->tm_min = BCD_TO_BIN(tp->tm_min); 
        tp->tm_hour = BCD_TO_BIN(tp->tm_hour); 
        tp->tm_mday = BCD_TO_BIN(tp->tm_mday); 
        tp->tm_mon = BCD_TO_BIN(tp->tm_mon); 
        tp->tm_year = BCD_TO_BIN(tp->tm_year); 
    } 

    if (tp->tm_year < 70) 
        tp->tm_year += 100; 

    tp->tm_yday = dayOfTheYear(tp->tm_year+1900, tp->tm_mon, tp->tm_mday); 
    tp->tm_isdst = 0; 

// adjust for 0-11 month encoding
    tp->tm_mon--;

    return OK; 
} 


int rtc_SetSysTimeFromCmos() 
{ 
    struct tm tmBuf; 
    struct timespec tspec; 

    rtc_gettime (&tmBuf); 
    /* tspec.tv_sec = mktime (&tmBuf);*/ 
    tspec.tv_sec = convertTime(tmBuf.tm_year+1900, tmBuf.tm_mon+1, 
                               tmBuf.tm_mday, tmBuf.tm_hour, 
                               tmBuf.tm_min, tmBuf.tm_sec); 
    tspec.tv_nsec = 0; 
    clock_settime (CLOCK_REALTIME, &tspec); 
    return OK; 
} 

int rtc_SetCmosFromSysTime() 
{ 
    struct tm tmBuf; 
    struct timespec tspec; 

    clock_gettime (CLOCK_REALTIME, &tspec); 
    localtime_r (&(tspec.tv_sec), &tmBuf); 
    rtc_settime (&tmBuf); 

    return OK; 
} 

