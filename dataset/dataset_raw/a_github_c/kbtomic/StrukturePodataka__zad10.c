#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_NAME_OF_FILE 30

typedef struct treeNode* treePointer;
typedef struct stack* stackPointer;
struct treeNode
{
    char data;
    treePointer left;
    treePointer right;
};
struct stack
{
    stackPointer next;
    treePointer nextTree;
};
treePointer ReadFromFile(char*, treePointer, stackPointer);
int Push(stackPointer, char);
stackPointer AllocateMemoryForStackElement(stackPointer, char);
treePointer AllocateMemoryForTree(char);
treePointer Pop(stackPointer);
treePointer EditTree(treePointer, treePointer, treePointer);
int CreateTree(treePointer, stackPointer);
int WriteInFile(char *, treePointer);
int InOrderPrintInFile(FILE*, treePointer);
int main()
{
    stackPointer head = (stackPointer)malloc(sizeof(struct stack));
    head->next = NULL;
    treePointer root = NULL;
    char readFile[MAX_NAME_OF_FILE] = "postfix.txt";
    char writeFile[MAX_NAME_OF_FILE] = "infix.txt";
    root = ReadFromFile(readFile, root, head);
    WriteInFile(writeFile, root);
    return 0;
}
treePointer ReadFromFile(char* nameOfFile, treePointer root, stackPointer head)
{
    char sign;
    treePointer rightChild = NULL;
    treePointer leftChild = NULL;
    FILE* fp = NULL;
    fp = fopen(nameOfFile, "r");
    if (!fp)
    {
        printf("Greska kod otvaranja datoteke!\n");
        return fp;
    }
    while (!feof(fp))
    {
        fscanf(fp, "%c ", &sign);
        if (sign == '+' || sign == '-' || sign == '*' || sign == '/')
        {
            root = AllocateMemoryForTree(sign);
            rightChild = Pop(head);
            leftChild = Pop(head);
            root = EditTree(root, rightChild, leftChild);
            CreateTree(root, head);
        }
        else
            Push(head, sign);
    }
    root = head->next->nextTree;
    fclose(fp);
    return root;
}
int Push(stackPointer head, char sign)
{
    stackPointer newStackElement = AllocateMemoryForStackElement(head, sign);
    newStackElement->next = head->next;
    head->next = newStackElement;
    return 0;
}
stackPointer AllocateMemoryForStackElement(stackPointer head, char sign)
{
    stackPointer newStackElement = (stackPointer)malloc(sizeof(struct stack));
    if (!newStackElement)
    {
        printf("Neuspjesna alokacija memorije!\n");
        return newStackElement;
    }
    newStackElement->next = NULL;
    newStackElement->nextTree = AllocateMemoryForTree(sign);
    return newStackElement;
}
treePointer AllocateMemoryForTree(char sign)
{
    treePointer newTreeNode = (treePointer)malloc(sizeof(struct treeNode));
    if (!newTreeNode)
    {
        printf("Neuspjesna alokacija memorije!\n");
        return newTreeNode;
    }
    newTreeNode->left = NULL;
    newTreeNode->right = NULL;
    newTreeNode->data = sign;
    return newTreeNode;
}
treePointer Pop(stackPointer head)
{
    stackPointer deletedStackElement = head->next;
    treePointer returnedTree = NULL;
    head->next = deletedStackElement->next;
    returnedTree = deletedStackElement->nextTree;
    free(deletedStackElement);
    return returnedTree;
}
treePointer EditTree(treePointer root, treePointer rightChild, treePointer leftChild)
{
    root->right = rightChild;
    root->left = leftChild;
    return root;
}
int CreateTree(treePointer root, stackPointer head)
{
    stackPointer nodeToAdd = (stackPointer)malloc(sizeof(struct stack));
    if (!nodeToAdd)
    {
        printf("Neuspjesna alokacija memorije!\n");
        return 1;
    }
    nodeToAdd->next = head->next;
    head->next = nodeToAdd;
    nodeToAdd->nextTree = root;
    return 0;
}
int WriteInFile(char* nameOfFile, treePointer root)
{
    FILE* fp = NULL;
    fp = fopen(nameOfFile, "w");
    if (!fp)
    {
        printf("Greska kod otvaranja datoteke!\n");
        return 1;
    }
    InOrderPrintInFile(fp, root);
    fclose(fp);
    return 0;
}
int InOrderPrintInFile(FILE* fp, treePointer root)
{
    if (root)
    {
        InOrderPrintInFile(fp, root->left);
        fprintf(fp, "%c ", root->data);
        InOrderPrintInFile(fp, root->right);
    }
    return 0;
}