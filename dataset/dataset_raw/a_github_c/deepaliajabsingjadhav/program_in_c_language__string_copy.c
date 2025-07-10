

#include<stdio.h>

void StrcpyX(char Src[], char Dest[])
{
    int i = 0;
    
    if( (Src == NULL) ||(Dest == NULL))
    {
        return;
    }
    while(Src[i] != '\0')
    {
        Dest[i] = Src[i];
        i++;
    }
    Dest[i] = '\0';
}

int main()
{
    char arr[30] = {'\0'};   
    char brr[30] = {'\0'};   
    
    printf("Please enter the string\n");

    scanf("%[^'\n']s",arr);
        
    StrcpyX(arr,brr);
    
    printf("String after copy : %s\n",brr);
    
    return 0;
}

