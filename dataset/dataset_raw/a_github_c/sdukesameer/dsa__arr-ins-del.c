
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n, arr[10], c=0, ch;
    while(1)
    {
        printf("1. To enter elements in the array\n");
        printf("2. To delete elements from the array\n");
        printf("3. Print the array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if (ch==1)
        {
            if (c+1>10)
                    printf("Array full. Try deleting elements.\n\n");
            else
                scanf("%d",&arr[c++]);
        }
        else if(ch==2)
        {
            if(c-1<0)
                printf("Array empty, try adding elements.\n\n");
            else
                arr[c--]=0;
        }
        else if(ch==3)
        {
            for(int j=0;j<c;j++)
            {
                printf("%d ",arr[j]);
            }
            printf("\n\n");
        }
        else if (ch==4)
        {
            printf("Exitting program, Thank you.\n");
            break;
        }
        else
        {
            printf("Invalid, choice try again\n\n");
        }
    }
    return 0;
}