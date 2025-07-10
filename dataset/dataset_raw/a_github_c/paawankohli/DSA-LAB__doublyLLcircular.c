#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node
{
    int data;
    nptr left, right;
}node;

nptr createNode(int x)
{
    nptr temp = (nptr)malloc(sizeof(node));
    temp -> data = x;
    temp -> left = temp -> right = NULL;

    return temp;
}

nptr insertLeft(nptr head, int x)
{
    if (head == NULL)
    {
        nptr temp = createNode(x);
        temp -> left = temp -> right = temp;
        return temp;
    }

    else
    {
        nptr temp = createNode(x);
        temp -> left = head -> left;
        temp -> right = head;

        head -> left = temp;
        (temp -> left) -> right = temp;

        return temp;
    }
}

nptr insertRight(nptr head, int x)
{
    if (head == NULL)
    {
        nptr temp = createNode(x);
        temp -> left = temp -> right = temp;
        return temp;
    }

    else
    {
        nptr curr = head;

        while(curr -> right != head)
            curr = curr -> right;
        
        nptr temp = createNode(x);

        temp -> left = head -> left;
        temp -> right = head;

        head -> left = temp;
        (temp -> left) -> right = temp;

        return head;
    }
}

nptr deleteLeft(nptr head)
{
    if(head == NULL)
        return head;

    if(head -> left == head && head -> right == head)
    {
        printf("%d deleted\n", head -> data);
        free(head);
        return NULL;
    }

    nptr temp = head;
    head = head -> right;
    head -> left = temp -> left;
    
    printf("%d deleted\n", temp -> data);
    free(temp);

    return head;
}

nptr deleteRight(nptr head)
{
    if(head == NULL)
        return head;

    if(head -> left == head && head -> right == head)
    {
        printf("%d deleted\n", head -> data);
        free(head);
        return NULL;
    }

    nptr curr = head;

    while(curr -> right != head)
        curr = curr -> right;

    (curr -> left) -> right = head;
    head -> left = curr -> left;

    printf("%d deleted\n", curr -> data);
    free(curr);
    return head;
}

void display(nptr head)
{
    nptr curr = head;
    printf("                 ");
    
    if(curr == NULL)
        printf("EMPTY");

    while(curr -> right != head)
    {
        printf(" %d ", curr -> data);
        curr = curr -> right;
    }

    printf(" %d\n", curr -> data);
}

int main()
{
    nptr head = NULL;
    printf("1. insertLeft 2. insertRight 3. deleteLeft 4. deleteRight 5. display 6. exit\n");

    int ch,  ele;

    do
    {
        printf("Command: "); scanf("%d", &ch);
        switch(ch)
        {
            case 1: 
                    scanf("%d", &ele);
                    head = insertLeft(head, ele);
                    break;

            case 2: 
                    scanf("%d", &ele);
                    head = insertRight(head, ele);
                    break;

            case 3: head = deleteLeft(head);
                    break;
            
            case 4: head = deleteRight(head);
                    break;

            case 5: display(head);
                    break;

            case 6: exit(0);
        }

    }while(ch != 6);
}