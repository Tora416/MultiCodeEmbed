

#include<stdio.h>

int Frequency(char str[], char ch)
{
    int iCnt = 0, i = 0;
    
    if(str == NULL)
    {
        return -1;
    }
    
    
    while(str[i] != '\0')
    {
        if(str[i] == ch)
        {
            iCnt++;
        }
        i++;
    }
    
    
    for(i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == ch)
        {
            iCnt++;
        }
    }
    
    while(*str != '\0')
    {
        if(*str == ch)
        {
            iCnt++;
        }
        str++;
    }
    
    
    return iCnt;
}

int main()
{
    char arr[30];
    char cValue = '\0';
    
    int iRet = 0;
    
    printf("Please enter the string\n");
    scanf("%[^'\n']s",arr);
    
    
    
    printf("Please enter the character to calculate the frequency\n");
    scanf(" %c",&cValue);       
    
    iRet = Frequency(arr,cValue);
    
    printf("Total Frequency is %d\n",iRet);
    
    return 0;
}






























