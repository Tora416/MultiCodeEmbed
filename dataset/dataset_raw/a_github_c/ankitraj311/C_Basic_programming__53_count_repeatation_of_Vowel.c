#include<stdio.h>
#include<string.h>
int main()
{
  int i,j,k, count = 0;
  char str_arr[100], f;
  printf("Enter Character to find out Vowel/Consonant");
  scanf("%[^\n]s",str_arr);



  printf("Enter Vowel whose count you want to find\n");
  scanf(" %c",&f);
  for(i=0; str_arr[i] != '\0'; i++)
  {
    if(str_arr[i] == f)
    {
      count++;
    }
  }
  if(count ==  0)
  {
    printf("Not even a Single Time Vowel is Found");
  }
  else
  {
    printf("Vowel is Found %d Times",count);
  }


}
