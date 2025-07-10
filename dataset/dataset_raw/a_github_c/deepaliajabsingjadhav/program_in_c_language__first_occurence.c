

#include<stdio.h>

int SearchFirstOcc(char str[], char ch)
{
    int i = 0;
    
    if((str == NULL) || (ch == '\0'))
    {
        return -1;
    }
    
    while(str[i] != '\0')
    {
            if(str[i] == ch)
            {
                break;
            }
        i++;
    }
    
    if(str[i] == ch)        
    {
        return i;
    }
    else                        
    {
        return -1;
    }

}





int main()
{
    char arr[30];

    char cValue = '\0';
    
    int iRet = 0;
    
    printf("Please enter the string\n");

    scanf("%[^'\n']s",arr);
        
    printf("Please enter the character\n");

    scanf(" %c",&cValue);
    
    iRet = SearchFirstOcc(arr,cValue);
    
    if(iRet == -1)
    {
        printf("There is no such character\n");
    }
    else
    {
        printf("First occurance of character at : %d\n",iRet);
    }
    
    return 0;
}



