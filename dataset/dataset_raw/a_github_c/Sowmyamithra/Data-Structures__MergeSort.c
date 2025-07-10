#include<stdio.h>
#include<stdlib.h>
int ARR[100];
int TEMP[100];
void Merge(int ARR[],int BEG,int MID,int END)
{
    int k=0,I=BEG,J=MID+1,INDEX=BEG;
    while(I<=MID && J<=END)
    {
        if(ARR[I]<ARR[J])
        {
            TEMP[INDEX]=ARR[I];
            I=I+1;
        }
        else
        {
            TEMP[INDEX]=ARR[J];
            J=J+1;
        }
        INDEX=INDEX+1;
    }
    if(I>MID)
    {
        while(J<=END)
        {
            TEMP[INDEX]=ARR[J];
            J=J+1;
            INDEX=INDEX+1;
        }
    }
    else
    {
        while(I<=MID)
        {
            TEMP[INDEX]=ARR[I];
            I=I+1;
            INDEX=INDEX+1;
        }
    }
    for(k=BEG;k<INDEX;k++)
    {
        ARR[k]=TEMP[k];
    }
}
void MergeSort(int ARR[],int BEG,int END)
{
    int MID;
    if(BEG<END)
    {
        MID=(BEG+END)/2;
        MergeSort(ARR,BEG,MID);
        MergeSort(ARR,MID+1,END);
        Merge(ARR,BEG,MID,END);
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
    MergeSort(ARR,0,n-1);
    printf("\nThe sorted array is:\n");
    for(i=0;i<n;i++)
    {
        printf("\t%d",ARR[i]);
    }
}