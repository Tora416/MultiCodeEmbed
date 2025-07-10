


































































  









  










  


















#include <stdio.h>
#include <string.h>
 
void main()
{
    int i, j, count = 0, pos, flag = 0;
    char s1[100], s2[10], s3[100];
    char *ptr1, *ptr2, *ptr3;
 
    printf("\nenter the String:");
    scanf(" %[^\n]s", s1);
    printf("\nenter the string to be inserted:");
    scanf(" %[^\n]s", s2);
    printf("\nenter the position you like to insert:");
    scanf("%d", &pos);
 
    ptr1 = s1;
    ptr3 = s3;
    
    for (i = 0, j = 0;*ptr1 != '\0'; ptr1++, i++, j++, ptr3++)
    {
        s3[j] = s1[i];
        if (*ptr1 == ' ' && flag != 1)
            ++count;
        if (flag != 1 && count == pos - 1)
        {
            flag = 1;
            for(ptr2 = s2;*ptr2 != '\0'; ptr2++)
            {
                s3[++j] = *ptr2;
                ptr3++;
            }
            s3[++j] = ' ';
            ptr3++;
        }
    }
    s3[j] = '\0';
    printf("\nthe string after modification is\n\n %s\n", s3);
}