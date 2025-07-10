#include<stdio.h>
#include<stdlib.h>
int isEven(int n)
    {
        if(n%2==0)
            return 1;
        else 
            return 0;
    }
int isPrime(int n)
    {
        int i,flag=0;
        for(i=2;i<n/2;i++)
            {
                if(n%i==0)
                    {
                        return 0;
                    }
            }
        return 1;
    }
int main()
    {
        FILE *fptr,*eptr,*optr,*pptr;
        int n;
        
        fptr=fopen("File3.txt","r");
        eptr=fopen("FIle3Even.txt","w");
        optr=fopen("FIle3Odd.txt","w");
        pptr=fopen("FIle3Prime.txt","w");
        if(fptr==NULL||eptr==NULL||optr==NULL||pptr==NULL)
            {
                perror("File openning error(:");
                getch();
                exit(0);
            }
            
        while(fscanf(fptr,"%d",&n)!=EOF)
            {
                if(isPrime(n))
                    fprintf(pptr,"%d ",n);
                if(isEven(n))
                    fprintf(eptr,"%d ",n);
                else
                    fprintf(optr,"%d ",n);  
            }
            
        printf("\n Successfully written into file...");
        
        fclose(fptr);
        fclose(eptr);
        fclose(optr);
        fclose(pptr);
        
        return 0;
    }

