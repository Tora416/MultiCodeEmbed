#include<stdio.h>
int main()
{
  int i,j=0,k,O_no,D_no,a,b,arr[100];
  int new[10]={0};
  printf("Enter the number to find the repeatation in it");
  scanf("%d",&O_no);






            

  while( O_no > 0 )
  {
    i = O_no % 10;
    arr[j] = i;
    O_no = O_no / 10;
    j++;
  }
  
  for(i=0; i<j; i++)
  {
    new[arr[i]]++;
  }
    
  for(i=0; i<10; i++)
  {
    if(new[i]!=0)
      printf("%d  frequency is %d \n",i, new[i]);
  }

}
