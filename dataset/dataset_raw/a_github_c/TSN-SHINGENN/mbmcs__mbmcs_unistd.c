

#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#include <xparameters.h>


#include "multios_lite_mallocater.h"


#include "libmbmcs_libmultios_bridge.h"
#include "mbmcs_stdio.h"
#include "mbmcs_platform.h"
#include "mbmcs_unistd.h"


#ifdef __GNUC__
__attribute__ ((unused))
#endif
#ifdef DEBUG
static int debuglevel = 4;
#else
static int debuglevel = 0;
#endif
#include "dbms.h"

#if defined(_MULTIOS_DMSG_IS_UART)
#define EOL_CRLF "\n\r"
#else
#define EOL_CRLF "\n"
#endif


int64_t mbmcs_sysconf_pagesize(void)
{
    return XPAR_CPU_MICROBLAZE_I_DATA_SIZE;
}


int64_t mbmcs_sysconf_nprocessor_conf(void)
{
    return 1; 
}


int64_t mbmcs_sysconf_nprocessor_onln(void)
{
    return 1; 
}


int64_t mbmcs_sysconf_phys_pages(void)
{
    return 2 * 0xffff / XPAR_CPU_MICROBLAZE_I_DATA_SIZE;
}


int64_t mbmcs_sysconf_avphys_pages(void)
{
    return multios_lite_mallocater_avphys_with_obj(&_multios_lite_mallocater_heap_emulate_obj) / XPAR_CPU_MICROBLAZE_I_DATA_SIZE;

}
