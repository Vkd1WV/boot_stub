/* The <time.h> header is used by the procedures that deal with time.
 * Handling time is surprisingly complicated, what with GMT, local time
 * and other factors.  Although the Bishop of Ussher (1581-1656) once
 * calculated that based on the Bible, the world began on 12 Oct. 4004 BC
 * at 9 o'clock in the morning, in the UNIX world time begins at midnight, 
 * 1 Jan. 1970 GMT.  Before that, all was NULL and (void).
 */

#ifndef _TIME_H
#define _TIME_H

#define CLOCKS_PER_SEC    60	/* MINIX always uses 60 Hz, even in Europe */
#include "sys/typedefs.h"

typedef enum { // 13 months of 28 days
	April=1, May, June,
	July, August, Hexember,
	September, October, November,
	December, January, February,
	March
} months;

typedef enum {
	Monday=1, Tuesday, Wednesday, Thursday, Friday,
	Saturday, Sunday
} wdays;

struct time {
	unsigned int sec;  /* seconds after the minute GMT [0, 59] */
	unsigned int min;  /* minutes after the hour   GMT [0, 59] */
	unsigned int hour; /* hours since midnight     GMT [0, 23] */
	unsigned int mday; /* day of the month [1, 30] */
	months       mon;  // month of the year [1, 13]
	int          year; // year HE
	unsigned int qtr;  // quarter [1, 4]
	wdays        wday; // day of the week [1, 7]
	unsigned int yday; // day of the year [1, 366]
	time_t       sys_seconds;
};

struct tm {
	int tm_sec;			/* seconds after the minute [0, 59] */
	int tm_min;			/* minutes after the hour [0, 59] */
	int tm_hour;		/* hours since midnight [0, 23] */
	int tm_mday;		/* day of the month [1, 31] */
	int tm_mon;			/* months since January [0, 11] */
	int tm_year;		/* years since 1900 */
	int tm_wday;		/* days since Sunday [0, 6] */
	int tm_yday;		/* days since January 1 [0, 365] */
	int tm_isdst;		/* Daylight Saving Time flag */
};


clock_t clock   (void                        );
double  difftime(time_t _time1, time_t _time0);
time_t  mktime  (struct tm *_timeptr         );
time_t  time    (time_t *_timeptr            );
//char*      asctime  (const struct tm *_timeptr   );
//char*      ctime    (const time_t *_timer        );
//struct tm* gmtime   (const time_t *_timer        );
//struct tm* localtime(const time_t *_timer        );
size_t  strftime(
		char *_s, size_t _max, const char *_fmt, const struct tm *_timep);

//#ifdef _MINIX
//int stime, (time_t *_top	);
//#endif

#endif /* _TIME_H */
