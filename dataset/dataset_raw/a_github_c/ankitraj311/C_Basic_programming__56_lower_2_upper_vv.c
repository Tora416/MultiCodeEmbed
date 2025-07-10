#include<stdio.h>
#include<string.h>
int main()
{
  int i,j,k, count = 0, frequency[26] = {0};
  char str_arr[100], str_arr1[100], f;
  printf("Enter String to convert Upper to Lower & Lower to Upper");
  scanf("%[^\n]s",str_arr);


  
  printf("%s",str_arr);
  for(i=0; str_arr[i] != '\0'; i++)
  {
    if(str_arr[i] > 'a' && str_arr[i] < 'z')
    {
      str_arr1[i] = (char)str_arr[i] - 32;
    }

    else if(str_arr[i] > 'A' && str_arr[i] < 'Z')
    {
      str_arr1[i] = (char)str_arr[i] + 32;
    }
    else
    {
      str_arr1[i] = str_arr[i];
    }
  }

  printf("\nAfter Conversion String is %s\n",str_arr1);
}
