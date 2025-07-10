#include<stdio.h>


int ekok(int x, int y);
           

int main()
{
  int num1,num2,ek=0;

  printf("%s\n","EKOK almak istediğiniz iki pozitif tam sayı giriniz:");
  scanf("%d%d",&num1,&num2);

  if(num1>num2)
    ek=ekok(num1,num2);

  else
    ek=ekok(num2,num1);

  printf("girilen değerlerin EKOK u:%d\n",ek);  

  return 0;
}

int ekok(int x, int y)
{
  static int temp=1;
  
    if(temp%y==0 && temp%x==0)  
      return temp;
    
    temp++;
    ekok(x,y);

    return(temp);

}