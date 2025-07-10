#include<stdio.h>
void main()
{
  int a[2][2], b[2][2], c[2][2], i, j, p1, p2, p3, p4 , p5, p6, p7,az,bz,cz,d,e,f,g,h;
  printf("Enter elements of first matrix: ");
  for(i = 0;i < 2; i++)
  {
      for(j = 0;j < 2; j++)
      {
           scanf("%d", &a[i][j]);
      }
  }
  printf("Enter elements of second matrix: ");
  for(i = 0; i < 2; i++)
  {
      for(j = 0;j < 2; j++)
      {
           scanf("%d", &b[i][j]);
           
      }
  }

  az=a[0][0];
  bz=a[0][1];
  cz=a[1][0];
  d=a[1][1];
  e=b[0][0];
  f=b[0][1];
  g=b[1][0];
  h=b[1][1];
  p1=az*(f-h);
  p2=(az+bz)*h;
  p3=(cz+d)*e;
  p4=d*(g-e);
  p5=(az+d)*(e+h);
  p6=(bz-d)*(g+h);
  p7=(az-cz)*(e+f);
  
  c[0][0] = p5+p4-p2+p6;
  c[0][1] = p1+p2;
  c[1][0] = p3+p4;
  c[1][1] = p1+p5-p3-p7;
 
   printf("\nAfter multiplication\n");
   for(i = 0; i < 2 ; i++){
      printf("\n");
      for(j = 0;j < 2; j++)
           printf("%d\t", c[i][j]);
   }
 
}
