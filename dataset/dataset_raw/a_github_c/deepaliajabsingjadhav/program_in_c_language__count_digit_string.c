

#include<stdio.h>

int DigitCount(char *str)
{
    int iCnt = 0;
    
    if(str == NULL)
    {
        return -1;
    }
    
    while(*str != '\0')
    {
        if((*str >= '0') && (*str <= '9'))
        {
            iCnt++;
        }
        str++;
    }
        
    return iCnt;
}

int main()
{
    char arr[30] = {'\0'};
    
    int iRet = 0;
    
    printf("Please enter string\n");
    
    scanf("%[^'\n']s",arr);
    
    iRet = DigitCount(arr);
    
    printf("Number of digits are %d\n",iRet);
    
    return 0;
}


