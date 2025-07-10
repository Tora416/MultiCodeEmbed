
#include <stdio.h>

int ft_strlen(char *);
int ft_strlen(char *dato){
    int i = 0;
    while(dato[i] != '\0')++i;
    return i;
}

char *ft_strrev (char *);
char *ft_strrev (char * str){
    int longitud = ft_strlen(str);
    char *string; 

    for(int i = 1; i <= longitud + 1; i++){
        if(i > longitud)
            string[longitud] = '\0';
        else
            string[i -1] = str[longitud - i];
    }
    return string;
}



int main(){
    char *palabra = "casa";
    palabra = ft_strrev(palabra);
    printf("%s", palabra);
    return 0;
}