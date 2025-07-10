#include<stdio.h>
#include<string.h>
int main()
{
  int i,j = 0,k, count = 0, count1 = 0, len1 = 0, len2 = 0, flag = 0;
  char str[100], str_sub[100];
  printf("Enter a Universal string to find Substring\n");
  scanf("%[^\n]s",str);


  
  printf("Enter a Substring\n");
  scanf(" %[^\n]s",str_sub);
  len1 = strlen(str);
  len2 = strlen(str_sub);
  for(i=0; i<=(len1 - len2); i++)
  {
    for(j=i; j<(i+len2); j++)
    {
      flag = 1;
      if( str[j] != str_sub[j-i])
      { 
        flag = 0;
    break;
      }
    }
    if(flag == 1)
    break;
  }
  
  if(flag == 1)
  {
    printf("\nSub_String Found");
  }
  else
  {
    printf("Sub_String Not FOund");
  }
}
