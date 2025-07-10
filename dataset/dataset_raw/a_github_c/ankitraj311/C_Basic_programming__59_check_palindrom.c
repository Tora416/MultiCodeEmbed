#include<stdio.h>
#include<string.h>
int main()
{
  int i,j = 0,k, count = 0, count1 = 0;
  char str_arr[100], str_arr1[100], f;
  printf("Enter String to find It's palindrom or Not\n");
  scanf("%[^\n]s",str_arr);


  
  for(i=0; str_arr[i] != '\0'; i++)
  {
    count++;
  }
  for(i=count-1; i>=0; i--)
  {
    str_arr1[j] = str_arr[i];
    j++;
  }
  str_arr1[i] = '\0';
  printf("String After Reverse is %s\n",str_arr1);

  for(i=0; str_arr[i] != '\0'; i++)
  {
    if(str_arr[i] == str_arr1[i])
    {
    count1++;
    }
  }
  printf("Value of Count1 is %d Count is %d\n",count1,count);
  if(count1 == count)
  {
    printf("String is Palindrom\n");
  }
  else
  {
    printf("Not a Palindrom String\n");
  }
}
