




#include "multios_endian.h"


#include "libmbmcs_revision.h"
#include "libmbmcs.h"

#if defined(__GNUC__)
extern const char *mbmcs_get_lib_revision(void)
    __attribute__ ((optimize("Os")));
extern const char *mbmcs_get_lib_name(void)
    __attribute__ ((optimize("Os")));
#endif



const char *mbmcs_get_lib_revision(void)
{
    return LIB_MBMCS_REVISION;
}


const char *mbmcs_get_lib_name(void)
{
    return LIB_MBMCS_NAME;
}

const char *const _libmbmcs_idkeyword =
    "@(#)libmultios_idkeyword : " LIB_MBMCS_NAME " revision"
    LIB_MBMCS_REVISION
    " CopyRight TSN.SHINGENN All Rights Reserved.";


const char *mbmcs_get_idkeyword(void)
{
    return _libmbmcs_idkeyword;
}
