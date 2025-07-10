#include<stdio.h>
int main()
{
  int i,j,k,choice;
  printf("Enter the choice to find the Area \n1. Triangle \n2. Circle \n3. Rectangle \n4. Square \n5. Parallelogram\n");
  scanf("%d",&choice);
 
 
 
 
 
 
  switch(choice)
  {
    case 1:
      {
        int a, b, c;
    float Area;
    printf("Enter the sides of the triangle");
    scanf("%d%d%d",&a,&b,&c);
    Area = (a*b*c);
    printf("Area of the triangle is %.2f",Area);
    break;
      }
    case 2:
      {
        int r;
    float Area;
    printf("Enter the radius of circle");
    scanf("%d",&r);
    Area = (3.14 * r * r);
    printf("Area of the circle is %.2f",Area);
    break;
      }
    case 3:
      {
        int a, b;
    float Area;
    printf("Enter the sides of the Rectangle");
    scanf("%d%d",&a,&b);
    Area = (a*b);
    printf("Area of the Rectangle is %.2f",Area);
    break;
      }
    case 4:
      {
        int a;
    float Area;
    printf("Enter the side of square");
    scanf("%d",&a);
    Area = (a*a);
    printf("Area of the square is %.2f",Area);
    break;
      }
    case 5:
      {
        int breath, height;
    float Area;
    printf("Enter the sides of the Parallelogram");
    scanf("%d%d",&breath,&height);
    Area = (breath*height);
    printf("Area of the  Parallelogram is %.2f",Area);
    break;
      }
    default :
      {
        printf("Invalid Result");
    break;
      }
  }
}
