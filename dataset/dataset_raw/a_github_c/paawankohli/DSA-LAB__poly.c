#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node
{
    int coeff, exp;
    nptr next;
}node;

nptr createNode(int c, int e)
{
    nptr temp = (nptr)malloc(sizeof(node));
    temp -> coeff = c;
    temp -> exp = e;
    temp -> next = NULL;

    return temp;
}

nptr insert(nptr head, int c, int e)
{
    if(head == NULL)
        return head = createNode(c, e);

    nptr temp = head;
    while(temp -> next != NULL)
        temp = temp -> next;

    temp -> next = createNode(c, e);
    return head;
}

void display(nptr head)
{
    while(head)
    {
        printf("%dx^%d", head -> coeff, head -> exp);
        if(head -> next)
            printf(" + ");

        head = head -> next;
    }

    printf("\n");
}

int getCoeff(nptr poly, int exp)
{
    while(poly)
    {
        if (poly -> exp == exp)
            return poly -> coeff;
    }

    return 0;
}

nptr add(nptr poly1, nptr poly2)
{
    nptr poly3, temp1 = poly1, temp2 = poly2;

    while(temp1)
    {
        if ( getCoeff(poly2, temp1 -> exp) )
            poly3 = insert(poly3,               temp1 -> coeff + getCoeff(poly2, poly1 -> exp),            poly1 -> exp);

        poly1 = poly1 -> next;
    }

    temp1 = poly1, temp2 = poly2;

    while(temp1)
    {
        if (getCoeff(poly3, temp1 -> exp) == 0)
            poly3 = insert(poly3, temp1 -> coeff, temp1 -> exp);

        temp1 = temp1 -> next;
    }

    while(temp2)
    {
        if (getCoeff(poly3, temp2 -> exp) == 0)
            poly3 = insert(poly3, temp2 -> coeff, temp2 -> exp);

        temp2 = temp2 -> next;
    }

    return poly3;

}

int main()
{
    nptr poly1  = NULL, poly2 = NULL, poly3 = NULL;
    
    int n, m;
    int coeff, exp;

    printf("Enter terms in poly1: "); 
    scanf("%d", &n);
    
    for(int i = 0 ; i < n ; i++)
    {
        printf("Enter coeff and exp: "); 
        scanf("%d %d", &coeff, &exp);
        poly1 = insert(poly1, coeff, exp);
    }

    printf("Enter terms in poly2: "); 
    scanf("%d", &m);
    
    for(int i = 0 ; i < m ; i++)
    {
        printf("Enter coeff and exp: "); 
        scanf("%d %d", &coeff, &exp);
        poly2 = insert(poly2, coeff, exp);
    }

    printf("\n");
    display(poly1);
    display(poly2);
    
    printf("\n");
    display(poly3 = add(poly1, poly2));
}