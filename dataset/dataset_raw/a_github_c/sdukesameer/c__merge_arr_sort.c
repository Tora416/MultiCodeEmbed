#include <stdio.h>
void merge(int a[], int m, int b[], int n, int sorted[]);
int main()
{
  int a[100], b[100], m, n, c, sorted[200];
  
  scanf("%d", &m); 
  for (c = 0; c < m; c++){
    scanf("%d", &a[c]); 
  }
  scanf("%d", &n); 
  for (c = 0; c < n; c++){
    scanf("%d", &b[c]); 
  }
  merge(a, m, b, n, sorted);
  
  printf("Sorted array:\n");
  for (c = 0; c < m + n; c++) {
    printf("%d\n", sorted[c]);
  }
  return 0;
}
void merge(int a[], int m, int b[], int n, int sorted[])
{
    int i,j,f;
    for(i=0;i<m;i++)
        sorted[i]=a[i];
    for(j=m,i=0;j<m+n;j++,i++)
        sorted[j]=b[i];
    for(i=0;i<m+n;i++)
    {
        for(j=0;j<(m+n)-i-1;j++)
        {
            if(sorted[j]>sorted[j+1])
            {
                f=sorted[j];
                sorted[j]=sorted[j+1];
                sorted[j+1]=f;
            }
        }
    }
}
