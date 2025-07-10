#include<stdio.h>
#include<string.h>
int main()
{
  int i,j,k, count = 0;
  char str1[100][100], s[100];
  printf("Enter Number of word you want to Enter\n");
  scanf("%d",&count);




  printf("Enter Words, which you to be sorted Alphabatically\n");
  for(i=0; i<count; i++)
  {
    scanf("%s",str1[i]);
  }
  printf("\n");
  for(i=0; i<count; i++)
  {
    printf("%s\n",str1[i]);
  }

  for(i = 0; i<count; i++)
  {
    for(j = i+1; j< count; j++)
    {
      if(strcmp(str1[i],str1[j])>0)
      {
        strcpy(s,str1[i]);
    strcpy(str1[i],str1[j]);
    strcpy(str1[j],s);
      }
    }
  }
  printf("Sorted Alphatically\n");
  for(i=0; i<count; i++)
  {
    printf("%s\n",str1[i]);
  }
}
