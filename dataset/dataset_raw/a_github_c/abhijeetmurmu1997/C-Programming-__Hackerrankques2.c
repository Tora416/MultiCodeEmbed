#include<stdio.h>
int gateOperation();
int main()
{
    int k,n;
    scanf("%d", &n);
    scanf("%d", &k);
    gateOperation(n,k);
    return 0;
}
int gateOperation(int n, int k)
{
    int i,j;
    int maxAND = 0;
    int maxOR = 0;
    int maxEXP = 0;
    for(i=1;i<=n;i++)
    {
        for(j=i+1;j<=n;j++)
        {
            if(((i & j) > maxAND) && ((i & j) < k))
            {
                maxAND = i & j;
            }
            if(((i | j) > maxOR) && ((i | j) < k))
            {
                maxOR = i | j;
            }
            if(((i ^ j) > maxEXP) && ((i ^ j) < k))
            {
                maxEXP = i ^ j;
            }
        }
    }
    printf("%d \n%d\n%d", maxAND, maxOR, maxEXP);
}
