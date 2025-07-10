



#include<stdio.h>

int SumI(int iNo)
{
    int iSum = 0;
   
    while(iNo != 0)
   
    {
   
            iSum = iSum + (iNo % 10);
       
        iNo = iNo / 10;
    }
    return iSum;
}

int SumR(int iNo)
{
    static int iSum = 0;
 
    if(iNo != 0)
 
    {
 
            iSum = iSum + (iNo % 10);
     
        iNo = iNo / 10;
        
        SumR(iNo);
    }
    return iSum;
}

int main()
{
    int no = 0, iRet = 0;

    printf("Enter first number\n");
 
    scanf("%d",&no);
 
    iRet = SumR(no);
 
    printf("Result is %d",iRet);
    
    return 0;
}
