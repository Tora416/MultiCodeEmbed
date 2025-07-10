

#include<stdio.h>
#include<string.h>
#define TRUE 1
#define FALSE 0

int CheckString(char s[]){
    int i=0 ,j=0;
    int result = TRUE;

    
    while(s[i] != '\0'){

        j = i+1;  
            while(s[j] != '\0'){
                
                if(s[i] == s[j]){
                    result = FALSE;
                }
                j++;
            }
            i++;
        }

        return result;
}

int main(void){
    int result;
    char str[20];
    gets(str);                       

    
    result = CheckString(str);

    if(result == TRUE){
        printf("All Characters are distinct");
    }
    else if(result == FALSE){
        printf("Repeated characters exist");
    }
    return 0;
}
