

#include<stdio.h>
#include<string.h>
void main()
 {
  char st[100],ch;
  printf("Enter string:");
  gets(st);
  for(int i=0;st[i]!='\o';i++)
   {
    if (st[i]>='A' && st[i]<='Z')
     {
      st[i]=st[i]+32;
      }
    if (st[i]>='a' && st[i]<='z')
     {
      st[i]=st[i]-32;
      }
    }
  printf("Opposite case of the string:");
  puts(st);
  }







