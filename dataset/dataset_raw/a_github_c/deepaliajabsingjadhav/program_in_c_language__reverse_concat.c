

#include<stdio.h>

void StrcatXX(char *Src, char *Dest)
{
    if(  (Src == NULL) ||  (Dest == NULL)   )
    {
        return;
    }
    
    
    
    while(*Dest != '\0')   
    {
        Dest++;                
    }
        
    *Dest = ' ';        
    
    Dest++;
   
    while(*Src != '\0')
   {
       *Dest = *Src;
       Src++;
       Dest++;
   }
    
    *Dest = '\0';
}

int main()
{
    char arr[30] = {'\0'};   

    char brr[30] = {'\0'};   
    
    printf("Please enter first string\n");

    scanf("%[^'\n']s",arr);
    
    printf("Please enter second string\n");
  
    scanf(" %[^'\n']s",brr);
        
    StrcatXX(arr,brr);       
    
    printf("String after concatination %s\n",brr);
    
    return 0;
}


