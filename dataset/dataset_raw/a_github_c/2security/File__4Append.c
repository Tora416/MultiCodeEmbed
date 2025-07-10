#include<stdio.h>
#include<stdlib.h>
int main()
    {
        FILE *fptr;
        char str[100];
        int n;
        
        fptr=fopen("File4.txt","a");
    
        if(fptr==NULL)
            {
                perror("File openning error(:");
                getch();
                exit(0);
            }
            
        
        printf("\n Enter contents to append in file4::");
        fflush(stdin);
        fgets(str,100,stdin);   
        
        
        fputs(str,fptr);
        
        printf("\n Successfully append into file...");
        
        fclose(fptr);
        
        return 0;
    }

