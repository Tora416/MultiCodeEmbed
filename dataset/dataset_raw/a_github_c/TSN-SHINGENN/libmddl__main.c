#if defined(WIN32) || 1

#define _CRT_SECURE_NO_WARNINGS
#if _MSC_VER >= 1400            
#pragma warning ( disable:4996 )
#pragma warning ( disable:4819 )
#endif
#endif

#include <stdio.h>
#include <string.h>

#include "mddl_printf.h"

static int putch(int code)
{
    return fputc(code, stdout);
}


int
main(int ac, char **av)
{
    int a = 12345, b = 987654;
    int len;
    char C = 'C';
    const char *txt="chat put acbde";
    size_t n;
    char buf[128];

    double d[] = {
        0.0,
        42.0,
        1234567.89012345,
        0.000000000000018,
        555555.55555555555555555,
        -888888888888888.8888888,
        111111111111111111111111.2222222222
    };

    mddl_printf_init(putch);

    for(n=0;n<100;n++) {
        len = sprintf(buf, "%% %d %c %d %s %d buf=%p\n", a, (int)n, b, txt, a, buf);
    printf("sprintf=%s",buf);
    printf("len=%llu\n", (unsigned long long)len);

        len = mddl_printf("%% %d %c %d %s %d buf=%p\n", a, (int)n, b, txt, a, buf);
    mddl_printf("len=%llu\n", (unsigned long long)len);

    len = sprintf(buf, "%f %f %f\n", d[0], d[1], d[2]);
    printf("float sprintf=%s",buf);
    printf("len=%d\n", len);

        len = mddl_printf("%f %f %f\n", d[0], d[1], d[2]);
    printf("len=%d\n", len);
    }

    return 0;
}
