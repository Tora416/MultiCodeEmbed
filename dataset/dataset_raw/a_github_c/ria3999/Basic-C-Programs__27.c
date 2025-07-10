# include<stdio.h>
int compare(char[],char[]);
void main()
{
    char str1[90],str2[90];
    int z;
    printf("enter string1");
    gets(str1);
    printf("enter string2");
    gets(str2);
    z=compare(str1,str2);
    if(z==1)
        printf("equal");
    else
        printf("notequal");
}
int compare(char str1[],char str2[])
{
    int i=0,j=0,f=0;
   while(str1[i]==str2[j])
   {
       if(str1[i]!='\0'||str2[j]!='\0')
       {
           f=1;
           break;
       }
       i++;
       j++;
   }
   if(f==1)
    return 1;
   else
    return 0;
}
