#include<stdio.h>
#include<string.h>
int main()
{
int i;
char str[100],c;
printf("Enter a string\n");
scanf("%[^\n]s",str);




printf("%c\n",str[0]);
printf("%d",str[0]-32);
for(i=0;i<strlen(str);i++)
{
    
    
  if(str[i]>='A'&&str[i]<='Z')
  {
      c=str[i];
      break;
  }
  else
  {
      continue;
  }
}

printf("\nFirst capital letter of string %s is %c\n",str,c);

}
