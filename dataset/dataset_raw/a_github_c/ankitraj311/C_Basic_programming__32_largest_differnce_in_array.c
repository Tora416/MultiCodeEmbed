#include<stdio.h>
int main()
{
  int i=0,j=0,k=0,array[100]={0},lar_dif = 0, no = 0;
  printf("Enter Length of Array");
  scanf("%d",&no);





  for(i=0; i<no; i++)
  {
    scanf("%d",&array[i]);
  }
  
  
  for(i=0; i<no; i++)
  {
    for(j=i+1; j<no; j++)
    {
      if( (array[j] - array[i]) > lar_dif)
       {
         lar_dif = (array[j] - array[i]);
       }
    }
  }

  printf("Value of Lar_dif is %d",lar_dif);

}
