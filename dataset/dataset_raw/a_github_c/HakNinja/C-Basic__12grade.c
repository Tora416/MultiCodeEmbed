
 
#include<stdio.h>
void main()
 {
  float m1,m2,m3,m4,m5,per;
  printf("Enter marks of five subject=");
  scanf("%f%f%f%f%f",&m1,&m2,&m3,&m4,&m5);
  per=(m1+m2+m3+m4+m5)/5;
  printf("percentage=%f\n",per);
  if(per<=100&&per>=85)
   {
    printf("Grade=A");
    }
  else if(per<85&&per>=75)
   {
    printf("Grade=B");
    }
  else if(per<75&&per>=55)
   {
    printf("Grade=C");
    }
  else if(per<55&&per>=40)
   {
    printf("Grade=D");
    }
  else
   {
    printf("FAIL");
    }
  }


                                       
