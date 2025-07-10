#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode* treePointer;
struct treeNode
{
    int data;
    treePointer left;
    treePointer right;
};
treePointer AllocateMemory(int);
treePointer InsertElement(int, treePointer);
int InOrderPrint(treePointer);
int PostOrderPrint(treePointer);
int PreOrderPrint(treePointer);
treePointer DeleteElement(int, treePointer);
treePointer FindMin(treePointer);
treePointer FindElement(int, treePointer);
int main()
{
    treePointer root = NULL;
    root = InsertElement(2, root);
    root = InsertElement(4, root);
    root = InsertElement(9, root);
    root = InsertElement(1, root);
    root = InsertElement(11, root);
    root = InsertElement(7, root);
    root = DeleteElement(2, root);
    int choice = 0, element;
    treePointer temp = NULL;

    do
    {
        printf("Odaberi:\n");
        printf("1 - unos novog elementa u stablo\n");
        printf("2 - ispis inorder stabla\n");
        printf("3 - ispis postorder stabla\n");
        printf("4 - ispis preorder stabla\n");
        printf("5 - trazenje elementa stabla\n");
        printf("6 - brisanje elementa iz stabla\n");
        printf("7 - izlaz\n");

        scanf("%d", &choice);
        system("cls");
        switch (choice)
        {
        case 1:
            printf("Unesi element koji zelis unijeti u stablo:\n");
            scanf("%d", &element);
            root = InsertElement(element, root);
            break;
        case 2:
            InOrderPrint(root);
            break;
        case 3:
            PostOrderPrint(root);
            break;
        case 4:
            PreOrderPrint(root);
            break;
        case 5:
            printf("Unesi element koji trazis u stablu:\n");
            scanf("%d", &element);
            temp = FindElement(element, root);
            if (temp)
                printf("Element %d se nalazi na adresi %d\n", temp->data, temp);
            break;
        case 6:
            printf("Unesi element koji brises iz stabla:\n");
            scanf("%d", &element);
            root = DeleteElement(element, root);
        case 7:
            break;
        default:
            printf("Pogresan unos!\n");
        }
    } while (choice != '7');
    return 0;
}
treePointer AllocateMemory(int element)
{
    treePointer newNode = (treePointer)malloc(sizeof(struct treeNode));
    if (!newNode)
    {
        printf("Problem s alokacijom memorije!\n");
        return newNode;
    }
    newNode->data = element;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;

}
treePointer InsertElement(int element, treePointer root)
{
    if (!root)
        return AllocateMemory(element);
    else if (element < root->data)
        root->left = InsertElement(element, root->left);
    else if (element > root->data)
        root->right = InsertElement(element, root->right);
    return root;
}
int InOrderPrint(treePointer root)
{
    if (root)
    {
        InOrderPrint(root->left);
        printf("%d\n", root->data);
        InOrderPrint(root->right);
    }
    return 0;
}
int PostOrderPrint(treePointer root)
{
    if (root)
    {
        PostOrderPrint(root->left);
        PostOrderPrint(root->right);
        printf("%d\n", root->data);
    }
    return 0;
}
int PreOrderPrint(treePointer root)
{
    if (root)
    {
        printf("%d\n", root->data);
        PreOrderPrint(root->left);
        PreOrderPrint(root->right);
    }
    return 0;
}
treePointer DeleteElement(int element, treePointer root)
{
    treePointer temp;
    if (!root)
        return root;
    else if (element < root->data)
        root->left = DeleteElement(element, root->left);
    else if (element > root->data)
        root->right = DeleteElement(element, root->right);
    else
    {
        if (root->left && root->right)
        {
            temp = FindMin(root->right);
            root->data = temp->data;
            root->right = DeleteElement(temp->data, root->right);
        }
        else
        {
            temp = root;
            if (!root->left)
                root = root->right;
            else if (!root->right)
                root = root->left;
            free(temp);
        }
    }
    return root;
}
treePointer FindMin(treePointer root)
{
    while (root->left)
        root = root->left;
    return root;
}
treePointer FindElement(int element, treePointer root)
{
    if (!root)
        return root;
    else if (element < root->data)
        return FindElement(element, root->left);
    else if (element > root->data)
        return FindElement(element, root->right);
    else
        return root;
}