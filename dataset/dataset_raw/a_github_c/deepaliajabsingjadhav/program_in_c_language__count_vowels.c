

#include<stdio.h>

int CountVowels(char str[])
{
    int iCnt = 0, i = 0;
    
    if(str == NULL)
    {
        return -1;
    }
    
    while(str[i] != '\0')
    {
        if(
           (str[i] == 'a') || (str[i] == 'A') || (str[i] == 'e') || (str[i] == 'E') || (str[i] == 'i') || (str[i] == 'I') || (str[i] == 'o')||(str[i] == 'O') || (str[i] == 'u')||(str[i] == 'U') )
        {
            iCnt++;
        }
        i++;
    }
    
    return iCnt;
}

int main()
{
    char arr[30];
    int iRet = 0;
    
    printf("Please enter the string\n");
 
    scanf("%[^'\n']s",arr);
    
    iRet = CountVowels(arr);
    
    printf("Total number vowels are %d\n",iRet);
    
    return 0;
}
