
 
#include<stdio.h>
void main()
 {int a[10],n,s,first,middle,last;
  printf("Enter no of element:");
  scanf("%d",&n);
  printf("Enter element in ascending order:");
  for(int i=0;i<n;i++)
   {scanf("%d",&a[i]);
    }
  printf("Enter element to be search:");
  scanf("%d",&s);
  first=0;
  last=n-1;
  middle=(first+last)/2;
  while(first<=last)
   {if(a[middle]<s)
     { first=middle+1;
      }
    else if(a[middle]==s)
     {printf("Number is present\n");
      break;         
      }
    else
     {last=middle-1;
      }
    middle=(first+last)/2;
    }
  if (first>last)
   { printf("not found!!!");
    }
  }

