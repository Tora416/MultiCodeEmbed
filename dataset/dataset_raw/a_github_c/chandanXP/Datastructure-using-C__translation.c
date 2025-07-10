#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>

void main(){
     int gd=DETECT,gm;
     int x1,x2,x3,y1,y2,y3,nx1,nx2,nx3,ny1,ny2,ny3;
     int xt,yt,;
     
     initgraph(&gd, &gm, "c:\\tc\\bgi");
     printf("\n\t Enter the points of triangle: ");
     setcolor(5);
     scanf("%d %d %d %d %d %d", &x1, &x2, &x3, &y1, &y2, &y3);

     line(x1,y1,x2,y2);
     line(x2,y2,x3,y3);
     line(x3,y3,x1,y1);

     printf("\nEnter Translation factor \n");
     scanf("%d %d", &xt, &yt);

     nx1 = x1 + xt;
     ny1 = y1 + yt;
     nx2 = x2 + xt;
     ny2 = y2 + yt;
     nx3 = x3 + xt;
     ny3 = y3 + yt;

     line(nx1,ny1,nx2,ny2);
     line(nx2,ny2,nx3,ny3);
     line(nx3,ny3,nx1,ny1);

     getch();


}




