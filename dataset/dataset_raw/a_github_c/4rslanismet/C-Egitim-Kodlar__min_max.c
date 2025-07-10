#include <stdio.h> 


int main()
{
    int n,i ; 
    int max,min,maxIndis,minIndis;
    
    

    printf("%s","dizinin boyutunu giriniz:")   ;
    scanf("%d",&n);

    int arr[n];

    for(i=0;i<n;i++)
    {
        printf("%s\n","eleman giriniz:");
        scanf("%d",&arr[i]);
    }

    max=min=arr[0];
    maxIndis=minIndis=0;

    for(i=1;i<n;i++)
    {
        if(min>arr[i])
        {
            min=arr[i];
            minIndis=i;
        }

        if(max<arr[i])
        {
            max=arr[i];
            maxIndis=i;
        }
    }

    printf("en büyük değer:%d\nen büyük değer sırası:%d\n",max,maxIndis+1);
    printf("en küçük değer:%d\nen küçük değer sırası:%d\n",min,minIndis+1);

    return 0;
}


