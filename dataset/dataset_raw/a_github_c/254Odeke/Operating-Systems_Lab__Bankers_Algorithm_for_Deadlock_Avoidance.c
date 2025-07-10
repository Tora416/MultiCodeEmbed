#include<stdio.h>
int f[50],i,k,j,inde[50],n,c,count=0,p;
main(){

for(i=0;i<50;i++)
f[i]=0;
x:
printf("\nEnter index block:\t");
scanf("%d",&p);
if(f[p]==0){
f[p]=1;
printf("\nEnter no of files on index:\t");
scanf("%d",&n);
}
else
{
printf("\nBlock already allocated\n");
goto x;
}
for(i=0;i<n;i++)
scanf("%d",&inde[i]);
for(i=0;i<n;i++)
if(f[inde[i]]==1){
printf("\nBlock already allocated");
goto x;
}
for(j=0;j<n;j++)
f[inde[j]]=1;
printf("\nAllocated");
printf("\nFile indexed");
for(k=0;k<n;k++)
printf("\n%d->%d:%d",p,inde[k],f[inde[k]]);
printf("\nEnter 1 to enter more files and 0 to exit:\t");
scanf("%d",&c);
if(c==1)
goto x;
else
close();
getch();
}
