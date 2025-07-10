



#include <stdio.h>
#include <stdlib.h>



unsigned int My_strlen( char string[] , int size );


int main()
{
    char my_string[ 100 ];

    printf("Enter Your String : ");
    scanf("%99[^\n]s" , my_string);

    printf("\nLength Of Your String Is : %u\n" , My_strlen( my_string , sizeof(my_string)/sizeof(char) ));

    return 0;
}

unsigned int My_strlen( char string[] , int size )
{
    for(int i = 0;i < size;i++)
        if(string[ i ] == '\0')                                 
            return i;
}
