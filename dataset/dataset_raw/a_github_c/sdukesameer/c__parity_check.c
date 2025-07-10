#include<stdio.h>
#include<math.h>
long convert(int decimalnum)
{
    long binarynum = 0;
    int rem, temp = 1;
    while (decimalnum!=0)
    {
        rem = decimalnum%2;
        decimalnum = decimalnum / 2;
        binarynum = binarynum + rem*temp;
        temp = temp * 10;
    }
    return binarynum;
}
int check(int num)
{
    long bin=convert(num);
    int last = bin%10;
    if(last==0)
        return 1;
    else
        return 2;
}
int main()
{
    int t,n,i,j,parity,chk;
    scanf("%d",&t);
    for (int i = 0; i < t; i++)
    {
        scanf("%d",&n);
        int arr[n];
        for (int j = 0; j < n; j++)
            scanf("%d",arr+j);
        for (int j = 0; j < n; j++)
        {
            chk=check(arr[j]);
            if(j==0)
                parity=chk;
            else if(parity!=chk)
            {
                parity=0; 
                break;
            }
            else 
                continue;
        }
        if(parity==0)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}