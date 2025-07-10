

#include<stdio.h>

void StrrevX(char str[])
{
    int iStart = 0, iEnd = 0;
    char temp = '\0';
    
    if(str == NULL)
    {
        return;
    }
    
    
    while(str[iEnd] != '\0')        
    {
        iEnd++;
    }
    iEnd --;
    
    while(iStart < iEnd)            
    {
        temp = str[iStart];
        str[iStart] = str[iEnd];
        str[iEnd] = temp;
        
        iStart++;
        iEnd--;
    }
}

int main()
{
    char arr[30];
    
    printf("Please enter the string\n");

    scanf("%[^'\n']s",arr);
        
    StrrevX(arr);
    
    printf("Reverse string is %s\n",arr);
    
    return 0;
}

