
#include<stdio.h>

typedef int BOOL;

# define TRUE 1

#define FALSE 0

BOOL CheckBit(int iNo)
{
    int iMask = 0X00000860;
    
    int iResult = 0;
    if(iNo < 0)
    {
        iNo = -iNo;
    }
    iResult = iNo & iMask;
    
    if(iResult == iMask)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int main()
{
    int iNo = 0;
    BOOL bRet = FALSE;
    
    printf("Enter number\n");
    scanf("%d",&iNo);
        
    bRet = CheckBit(iNo);
    if(bRet == TRUE)
    {
        printf("10th,11th and 12th bit is on\n");
    }
    else
    {
        printf("One of the bit or all bits are Off\n");
    }
    return 0;
}




