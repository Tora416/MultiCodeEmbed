
                                                         
#include<stdio.h>
void main()
 {int a[10][10],t[10][10],n,m,i,j;
  printf ("Enter numbers of rows:");
  scanf ("%d",&n);
  printf ("Enter numbers of columns:");
  scanf ("%d",&m);
  printf("Enter elements:");
  for(i=0;i<n;i++)            
   {for(j=0;j<m;j++)
     {  scanf("%d",&a[i][j]);
      }
    }
  printf("\n Array is:\n");
  for(i=0;i<n;i++)          
   {for(j=0;j<m;j++)
     {  printf("\t %d",a[i][j]);
      }
      printf("\n");
    }
  printf("\n");  
  for(i=0;i<n;i++)         
   {for(j=0;j<m;j++)
     {   t[j][i]=a[i][j];
      }
    }
  printf("\n Its transpose:\n");
  for(i=0;i<n;i++)           
   {for(j=0;j<m;j++)
     {  printf("\t %d",t[i][j]);
      }
    printf("\n");
    }
  }
  
                                                                      
 
  
  

                                       
