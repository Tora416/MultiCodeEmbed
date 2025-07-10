#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* nptr;
typedef struct Node
{
    nptr llink;
    nptr rlink;
    int ele;
}node;

nptr createNode()
{
    nptr temp = (nptr)malloc(sizeof(node));
    temp->llink = temp;
    temp->rlink = temp;
    return temp;
}

void insert(nptr list,int x)
{
    nptr temp = createNode();
    temp->ele = x;

    temp-> llink = list;
    temp-> rlink = list -> rlink;
    list -> rlink = temp;
    (temp -> rlink) -> llink = temp;
}

nptr getnum(char num[50])
{
    nptr head = createNode();

    for(int i = strlen(num) - 1 ; i >= 0 ; i--)
        insert(head, num[i] - '0');

    return head;
}

nptr add(nptr num1, nptr num2)
{
    nptr sum = createNode();
    nptr n1 = num1 -> llink;
    nptr n2 = num2 -> llink;

    int cin = 0;
    int s = 0;

    while(n1 != num1 && n2 != num2)
    {
        s = (n1 -> ele) + (n2 -> ele) + cin;

        if(s >= 10)
        { 
            cin = 1;
            insert(sum, s - 10);
        }
        else
        {
            cin = 0;
            insert(sum, s);
        }

        n1 = n1 -> llink;
        n2 = n2 -> llink;
    }
    
    while(n1 != num1)
    {
        s = (n1 -> ele) + cin;
        
        if(s > 9)
        { 
            cin = 1; 
            insert(sum, s - 10);
        }
        else 
        {
            cin = 0; 
            insert(sum, s);
        }
        
        n1 = n1 -> llink;
    }
    
    while(n2 != num2)
    {
        s = (n2 -> ele) + cin;
        
        if(s > 9)
        { 
            cin = 1; 
            insert(sum, s - 10);
        }
        else 
        {
            cin = 0; 
            insert(sum, s);
        }
        
        n2 = n2 -> llink;
    }

    return sum;
}

void disp(nptr list)
{
    nptr i = list -> rlink;
    
    while(i != list)
    {
        printf("%d", i -> ele);
        i = i -> rlink;
    }
    
    printf("\n");
}

int main()
{
    char num1[50],num2[50];
    
    printf("Enter the first number: ");
    scanf("%s",num1);
    printf("Enter the second number: ");
    scanf("%s",num2);

    nptr n1 = getnum(num1);
    nptr n2 = getnum(num2);
    
    
    
    
    nptr sum = add(n1,n2);
    
    printf("The sum of the given numbers is ");
    disp(sum);
}