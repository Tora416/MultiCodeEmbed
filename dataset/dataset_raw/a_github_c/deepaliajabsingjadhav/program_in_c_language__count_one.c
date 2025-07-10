

#include<stdio.h>

int CountOne(int iValue)
{
    int iRem = 0;

    int iCnt = 0;

    if(iValue < 0)
    {
        iValue = -iValue;
    }
    
    while(iValue != 0)
    {
        iRem = iValue % 2;

    if(iRem == 1)
        {
            iCnt++;
        }
        iValue = iValue / 2;
    }
    return iCnt;
}
int main()
{
    int iNo = 0;

    int iRet = 0;
    
    printf("Enter number\n");

    scanf("%d",&iNo);
        
    iRet = CountOne(iNo);
    
    printf("Number of 1's in the numer is : %d\n",iRet);
    
    return 0;
}

