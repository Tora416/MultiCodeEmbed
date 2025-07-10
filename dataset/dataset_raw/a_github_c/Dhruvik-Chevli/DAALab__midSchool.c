#include<stdio.h>
#include<stdlib.h>
int power(int a,int b)
{
    int ans=1;
    for(int i=0;i<b;i++)
    {
        ans*=a;
    }
    return ans;
}
int main()
{
    int sieve[10000];
    for(int i=0;i<10001;i++)
    {
        sieve[i]=0;
    }
    sieve[1]=1;
    sieve[0]=1;
    int count=0;
    for(int i=2;i<10001;i++)
    {
        if(sieve[i]==0)
        {
            count+=1;
            for(int j=i*i;j<10001;j+=i)
            {
                sieve[j]=1;
            }
        }
    }
    int primes[count];
    int j=0;
    for(int i=0;i<10001;i++)
    {
        if(sieve[i]==0)
        {
            primes[j]=i;
            j+=1;
        }
    }
    
    int a[count];
    int b[count];
    int c,d;
    scanf("%d %d",&c,&d);
    int x,y;
    x=c;
    y=d;
    int count1=0;
    while(c>0)
    {
        int counts=0;
        while(c>0)
        {
            if(c%primes[count1]!=0)
            {
                a[count1]=counts;
                count1+=1;
                break;
            }
            else
            {
                c/=primes[count1];
                counts+=1;
            }
        }
        if(count1==count)
        {
            break;
        }
    }
    int count2=0;
    while(d>0)
    {
        int counts=0;
        while(d>0)
        {
            if(d%primes[count2]!=0)
            {
                b[count2]=counts;
                count2+=1;
                break;
            }
            else
            {
                d/=primes[count2];
                counts+=1;
            }
        }
        if(count2==count)
        {
            break;
        }
    }
    
    int pow;
    int gcd=1;
    for(int i=0;i<count;i++)
    {
        if(b[i]<a[i])
        {
            pow=b[i];
        }
        else
        {
            pow=a[i];
        }
        gcd*=(power(primes[i],pow));
    }
    printf("The GCD is %d \n",gcd);
    return 0;
}