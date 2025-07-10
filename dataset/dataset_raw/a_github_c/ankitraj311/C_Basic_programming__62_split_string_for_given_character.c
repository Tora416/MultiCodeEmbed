#include<stdio.h>
#include<string.h>
int main()
{
int i = 0, j = 0, k = 0;
char str1[100] = {0},str_sub[100][100] = {0},c;
printf("Enter a string\n");
scanf("%[^\n]s",str1);



printf("Enter character From where you want to Split\n");
scanf(" %c",&c);

while(str1[k] != '\0')
{
  j = 0;
  while(str1[k] != c && str1[k] != '\0')
  {
    str_sub[i][j] = str1[k];
    j++;
    k++;
  }
  str_sub[i][j] = '\0';
  i++;
  if(str1 != '\0')
  {
    k++;
  }
}
int len = i;
printf("Words after Splitting are:\n");
for(i=0; i<len; i++)
{
  printf("%s\n",str_sub[i]);
}


}
