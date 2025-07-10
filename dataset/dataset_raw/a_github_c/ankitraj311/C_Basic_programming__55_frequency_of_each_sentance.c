#include<stdio.h>
#include<string.h>
int main()
{
  int i,j,k, count = 0, frequency[26] = {0};
  char str_arr[100], f;
  printf("Enter String to find Frequency");
  scanf("%[^\n]s",str_arr);


  
  for(i=0; str_arr[i] != '\0'; i++)
  {
    if(str_arr[i] >= 'a' && str_arr[i] <= 'z')
    {
      frequency[str_arr[i] - 'a']++;   
    }

    if(str_arr[i] >= 'A' && str_arr[i] <= 'Z')
    {
      frequency[str_arr[i] - 'A']++;   
    }
  }

  for(i=0; i<26; i++)
  {
    if(frequency[i] != 0)
    {
      printf("%c is Repeated %d times\n",i+'a',frequency[i]);
    }
  }

}
