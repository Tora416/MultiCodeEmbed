



#include<stdio.h>

int StrlenI(char *str)
{
    int i = 0;
    
    while(str[i] != '\0')
    {
        i++;
    }
    return i;
}

int StrlenR(char *str)
{
    static int i = 0;
    
    if(str[i] != '\0')
    {
        i++;
        StrlenR(str);
    }
    return i;
}

int main()
{
    int iRet = 0;
 
    char Arr[30] = {'\0'};
    
 
    printf("Enter string\n");
 
    scanf("%[^'\n']s",Arr);
    
    iRet = StrlenR(Arr);
 
    printf("Length is %d\n\n",iRet);
    
    return 0;
}
