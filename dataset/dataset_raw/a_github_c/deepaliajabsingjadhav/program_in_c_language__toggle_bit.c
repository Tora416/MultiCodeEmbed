

#include<stdio.h>

int ToggleBit(int iNo, int iPos)
{
    int iMask = 0x00000001;
    
    int iResult = 0;
    if(iNo < 0)
    {
        iNo = -iNo;
    }
    
    if((iPos < 1) || (iPos > 32))
    {
        return 0;
    }
    
    iMask = iMask << (iPos -1);
    
    iResult = iNo ^ iMask;
    
    return iResult;
}

int main()
{
    int iNo = 0, iPos = 0, iRet = 0;
    
    printf("Enter number\n");
    scanf("%d",&iNo);
    
    printf("Enter the position\n");
    scanf("%d",&iPos);
        
    iRet = ToggleBit(iNo,iPos);
    
    printf("Modified number after bit toggle is : %d\n",iRet);

    return 0;
}




