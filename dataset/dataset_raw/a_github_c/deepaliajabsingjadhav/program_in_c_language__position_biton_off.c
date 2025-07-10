

#include<stdio.h>
typedef int BOOL;
# define TRUE 1
#define FALSE 0

BOOL CheckBit(int iNo, int iPos)
{
    int iMask = 0x00000001;
    
    int iResult = 0;
    if(iNo < 0)
    {
        iNo = -iNo;
    }
    
    if((iPos < 1) || (iPos > 32))
    {
        return FALSE;
    }
    
    iMask = iMask << (iPos -1);
    
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
    int iNo = 0, iPos;
    BOOL bRet = FALSE;
    
    printf("Enter number\n");
    scanf("%d",&iNo);
    
    printf("Enter the position\n");
    scanf("%d",&iPos);
        
    bRet = CheckBit(iNo,iPos);
    if(bRet == TRUE)
    {
        printf("Bit is on\n");
    }
    else
    {
        printf("Bits is Off\n");
    }
    return 0;
}


