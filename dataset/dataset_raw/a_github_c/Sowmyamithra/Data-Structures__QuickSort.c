#include<stdio.h>
#include<stdlib.h>
int ARR[100];
int Partition(int ARR[],int BEG,int END)
{
    int Left=BEG,Right=END,LOC=BEG,FLAG=0,temp;
    while(FLAG!=1)
    {
        while(ARR[LOC]<=ARR[Right] && LOC!=Right)
        {
            Right=Right-1;
        }
        if(LOC==Right)
        {
            FLAG=1;
        }
        else if(ARR[LOC]>ARR[Right])
        {
            temp=ARR[LOC];
            ARR[LOC]=ARR[Right];
            ARR[Right]=temp;
            LOC=Right;
        }
        if(FLAG!=1)
        {
            while(ARR[LOC]>=ARR[Left] && LOC!=Left)
            {
                Left=Left+1;
            }
            if(LOC==Left)
            {
                FLAG=1;
            }
            else if(ARR[LOC]<ARR[Left])
            {
                temp=ARR[LOC];
                ARR[LOC]=ARR[Left];
                ARR[Left]=temp;
                LOC=Left;
            }
        }
    }
    return(LOC);
}   
void QuickSort(int ARR[],int BEG,int END)
{
    int LOC;
    if(BEG<END)
    {
        LOC=Partition(ARR,BEG,END);
        QuickSort(ARR,BEG,LOC-1);
        QuickSort(ARR,LOC+1,END);
    }
}
void main()
{
    int n,i;
    printf("\nEnter the number of elements in the array:");
    scanf("%d",&n);
    printf("\nEnter the elements of the array:");
    for(i=0;i<n;i++)
    {
        scanf("%d",&ARR[i]);
    }
    QuickSort(ARR,0,n-1);
    printf("\nThe sorted array is:\n");
    for(i=0;i<n;i++)
    {
        printf("\t%d",ARR[i]);
    }
}
