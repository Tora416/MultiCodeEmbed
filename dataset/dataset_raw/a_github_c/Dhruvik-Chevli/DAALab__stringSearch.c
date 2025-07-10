#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    char str[50],substr[50];
    int a,b,c,k=0,flag=0;
    clock_t t1,t2;

    printf("\nEnter a string: ");
    scanf("%[^\n]%*c",str);

    printf("\nEnter the substring to search: ");
    scanf("%[^\n]%*c",substr);

    t1=clock();
    int opcount=0;
    for (a=0;a<strlen(str);a++)
    {
        ++opcount;
        c=a;
        if (str[a]==substr[k])
        {
            for (b=0;b<=strlen(substr);b++)
            {
                ++opcount;
                if (b==strlen(substr))
                {
                    flag=1;
                    break;
                }
                if (str[c]==substr[b])
                    c++;             
                else if (str[c]!=substr[b])
                {
                    flag=0;
                    break;
                }             
            }
        }
        if ( flag==1 ) break;
    }
    t2=clock();
    printf("\ntime taken is %ld\n",(t2-t1));

    printf("\nOpcount: %d",opcount);
    if (flag==1)
        printf("\nfound\n");
    else 
        printf("\nnot found\n");
    
    return 0;

}
