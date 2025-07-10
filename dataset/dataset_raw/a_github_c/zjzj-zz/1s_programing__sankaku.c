#include <stdio.h>
#include <math.h>

double dist(double x1, double y1, double x2, double y2);


int main(){
 double a, b, c, d, e, f;
 double z[3], k, o, p, q;
 int i, j;
 printf("3点の座標を入力して下さい\n");
 printf("1つめの座標:");
 scanf("%lf%lf", &a, &b);
 printf("2つめの座標:");
 scanf("%lf%lf", &c, &d);
 printf("3つめの座標:");
 scanf("%lf%lf", &e, &f);
 

 z[0]=dist(a, b, c, d);
 z[1]=dist(c, d, e, f);
 z[2]=dist(e, f, a, b);

 for(i=0; i<3; i++){
  for(j=0; j<3; j++){
   if(z[i]<z[j]){
    k=z[i];
    z[i]=z[j];
    z[j]=k;
   }
  }
 }

 if(z[0]+z[1]>z[2] && z[1]+z[2]>z[0] && z[2]+z[0]>z[1]){
  printf("3つの辺の長さは\n");
  o=z[0];
  p=z[1];
  q=z[2];

  printf("a=%.2f\nb=%.2f\nc=%.2f\n", o, p, q);
  printf("この3辺で結ばれた図形は");

  if(o == p && o == q/sqrt(2)){
   printf("直角三角形です\n"); 
   return 0; 
  }else if(sqrt(o*o+p*p) == q){
   printf("直角三角形です\n"); 
   return 0; 
  }
   o*=o;
   p*=p;
   q*=q;
  
  if(q==o+p){
   printf("直角三角形です\n");
  }else if(q < o+p){
   printf("鋭角三角形です\n");
  }else if(q > o+p){
   printf("鈍角三角形です\n");
  }
 }
 else{
  printf("三角形ではない\n");
 }

 return 0;
}

double dist(double x1, double y1, double x2, double y2){
 double r;
 r=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
 return r;
}
