
                                                         
#include<stdio.h>
#include<string.h>
void main()
 {
  char st[100],ch;
  printf("Enter string:");
  gets(st);
  int i,n,j;
  n=strlen(st);
  i=0;
  j=n-1;
  while(i<j) 
   { 
    ch=st[i];
    st[i]=st[j];
    st[j]=ch;
    j--;
    i++;
    }
  printf("Reverse of the string:");
  puts(st);
  } 
  
                                                                      
 
  
  

                                       
