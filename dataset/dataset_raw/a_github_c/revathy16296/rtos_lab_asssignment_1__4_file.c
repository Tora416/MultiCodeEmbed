#include<stdio.h>
#include<stdlib.h>
#define SI 10



int i;

int main()
{ 
FILE *fp;
int n,sum=0;
float product=1,average;
int array[SI];

fp=fopen("file.txt","w+");
printf("inside the file called 'file.txt'");
printf("\n ------writing to the file------\n");
printf("enter the  number of elements in array\n");
scanf("%d",&n);
printf("enter the elements in the array\n");
for(i=0;i<n;i++)
{
    scanf("%d",&array[i]);
}

    for(i=0;i<n;i++)
    {
        sum=sum+array[i];
    }


    average=sum/n;
    
    for(i=0;i<n;i++)
    {
        product=product*array[i];
    }

fclose(fp);

fp=fopen("file.txt","r");
printf("\n----reading from the file----\n");
printf("the array elements are \n");
for(i=0;i<n;i++)
{
    printf("%d\t",array[i]);
}
printf("\nthe sum of number is %d\n",sum);
printf("the average is %f\n",average);
printf("product of number is %f",product);
fclose(fp);


return 0;
}