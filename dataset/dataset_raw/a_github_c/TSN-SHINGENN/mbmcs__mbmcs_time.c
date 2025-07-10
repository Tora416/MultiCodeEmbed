



#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#include "libmbmcs_libmultios_bridge.h"


#include "mbmcs_platform.h"
#include "mbmcs_unistd.h"
#include "mbmcs_time.h"


#ifdef __GNUC__
__attribute__ ((unused))
#endif
#ifdef DEBUG
static int debuglevel = 1;
#else
static const int debuglevel = 0;
#endif
#include "dbms.h"

#if defined(_MULTIOS_DMSG_IS_UART)
#define EOL_CRLF "\n\r"
#else
#define EOL_CRLF "\n"
#endif


#if defined(__GNUC__)

extern void mbmcs_msleep( const unsigned int)
    __attribute__ ((optimize("Os")));
extern unsigned int mbmcs_sleep( const unsigned int)
    __attribute__ ((optimize("Os")));
extern int mbmcs_clock_gettime_clock_monotonic(mbmcs_timespec_t *const)
    __attribute__ ((optimize("Os")));

#endif 


void mbmcs_msleep( const unsigned int milisec )
{
#ifndef MBMCS_ENABLE_FIT1_JIFFIES_COUNTER
    DMSG(stderr,"mbmcs_msleep : FIT1_JIFFIES_COUNTER function is not enabled" EOL_CRLF);
    abort();
#else
    const uint64_t mbmcs_jiffies = *mbmcs_jiffies_p;
    uint64_t endtime = mbmcs_jiffies + milisec;

    while ( endtime > *mbmcs_jiffies_p );

    return;
#endif
}


unsigned int mbmcs_sleep( const unsigned int seconds)
{
#ifndef MBMCS_ENABLE_FIT1_JIFFIES_COUNTER
    DMSG(stderr,"mbmcs_sleep : FIT1_JIFFIES_COUNTER function is not enabled" EOL_CRLF);
    abort();
#else

    const uint64_t mbmcs_jiffies = *mbmcs_jiffies_p;
    uint64_t endtime = mbmcs_jiffies + ((uint64_t)seconds * 1000);

    while ( endtime > *mbmcs_jiffies_p );

    return 0;
#endif
}


int mbmcs_clock_gettime_clock_monotonic(mbmcs_timespec_t * const mts_p)
{
#ifndef MBMCS_ENABLE_FIT1_JIFFIES_COUNTER
    DBMS1(stderr,"mbmcs_clock_gettime_clock_monotonic : FIT1_JIFFIES_COUNTER function is not enabled" EOL_CRLF);
    return EINVAL;
#else
    const uint64_t mbmcs_jiffies = *mbmcs_jiffies_p;
    mbmcs_timespec_t ts;

    if( NULL == mts_p ) {
    return  EFAULT;
    }

    ts.tv_sec = mbmcs_jiffies / HZ;
    ts.tv_nsec = (mbmcs_jiffies % HZ) * 1000 * 1000;

    *mts_p = ts;

    return 0;
#endif
}



