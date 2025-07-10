
#include<stdio.h>
typedef int BOOL;
# define TRUE 1
#define FALSE 0

BOOL CheckBit(int iNo)
{
    int iMask = 0X00800000;
    
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
        printf("Fourth bit is on\n");
    }
    else
    {
        printf("Fourth bit is Off\n");
    }
    return 0;
}
















