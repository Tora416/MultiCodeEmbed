#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



#define MAX_DIR_LENGTH 256

typedef struct dir* Position;
typedef struct stack* StackPosition;
typedef struct dir {
    char name[MAX_DIR_LENGTH];
    Position sibling;
    Position child;
}Dir;

typedef struct stack {
    Position data;
    StackPosition next;
} Stack;
Position AllocateMemoryForDirectory();
StackPosition AllocateMemoryForStack();
int PushStack(Position, StackPosition);
Position PopStack(StackPosition);
Position MakeDirectory(Position, char*);
Position ChangeDirectory(Position, StackPosition, char*);
Position ChangeToPreviousDirectory(StackPosition);
int PrintDirectory(Position);
int Path(Position, StackPosition);
int CommandPrompt(Position current, StackPosition stackHead);
void Remove(Position);
int main()
{
    Dir C;
    C.sibling = NULL;
    C.child = NULL;
    strcpy(C.name, "C:");

    Stack stackHead;
    stackHead.data = NULL;
    stackHead.next = NULL;

    PushStack(&C, &stackHead);
    CommandPrompt(&C, &stackHead);

    return 0;
}
Position PopStack(StackPosition stackHead)
{
    StackPosition tempStackElement = stackHead->next, prev = stackHead->next;
    if (!tempStackElement->next)
        return NULL;
    while (tempStackElement->next)
    {
        prev = tempStackElement;
        tempStackElement = tempStackElement->next;
    }
        Position directory = tempStackElement->data;
        prev->next = tempStackElement->next;
        free(tempStackElement);
        return directory;
}
int PushStack(Position current, StackPosition stackHead)
{
    StackPosition newStackElement;
    StackPosition tempStackElement = stackHead;
    if (newStackElement = AllocateMemoryForStack()) 
    {
        while (tempStackElement->next)
            tempStackElement = tempStackElement->next;
        newStackElement->next = tempStackElement->next;
        tempStackElement->next = newStackElement;
        newStackElement->data = current;
        return 0;
    }
    else
        return 1;
}
int PrintDirectory(Position current)
{
    if (!current->child)
        printf("Directory is empty!\n");
    else
    {
        current = current->child;
        while (current)
        {
            printf(" %s\n", current->name);
            current = current->sibling;
        }
    }
    return 0;
}
Position ChangeToPreviousDirectory(StackPosition stackHead)
{
    return PopStack(stackHead);
}
Position ChangeDirectory(Position current, StackPosition stackHead, char* name)
{
    if (!current->child)
    {
        
        return current;
    }
    else
    {
        Position parent = current;
        Position finderOfWantedDirectory = current->child;
        while (finderOfWantedDirectory)
        {
            if (!strcmp(finderOfWantedDirectory->name, name))
            {
                PushStack(finderOfWantedDirectory, stackHead);
                return finderOfWantedDirectory;
            }
            finderOfWantedDirectory = finderOfWantedDirectory->sibling;
        }
        
        return parent;
    }
}
Position MakeDirectory(Position current, char* name)
{
    Position newDirectory;
    newDirectory = AllocateMemoryForDirectory();

    strcpy(newDirectory->name, name);
        if (!current->child)
        {
            current->child = newDirectory;
        }
        else
        {
            Position currentChild = current->child;
            while (currentChild->sibling)
                currentChild = currentChild->sibling;
            currentChild->sibling = newDirectory;
        }
        return current;
}
StackPosition AllocateMemoryForStack()
{
    StackPosition newStackElement = (StackPosition)malloc(sizeof(Dir));
    if (!newStackElement)
    {
        printf("Can not allocate memory!\n");
    }
    return newStackElement;
}
Position AllocateMemoryForDirectory()
{
    Position newDirectory = (Position)malloc(sizeof(Dir));
    if (!newDirectory)
    {
        printf("Can not allocate memory!\n");
    }
    newDirectory->child = NULL;
    newDirectory->sibling = NULL;
    return newDirectory;    
}
void Remove(Position current)
{
    if (!current)
        return;
    remove(current->sibling);
    remove(current->child);
    
}
int Path(Position current, StackPosition stackHead)
{
    char stringToPrint[MAX_DIR_LENGTH] = "";
    
    while (stackHead)
    {
            strcat(stringToPrint, stackHead->data->name);
            strcat(stringToPrint, "\\");
            stackHead = stackHead->next;
    }
    strcat(stringToPrint, ">");
    printf("%s ", stringToPrint);
    return 0;
}
int CommandPrompt(Position current, StackPosition stackHead)
{
    Position C = current;
    char userInput[MAX_DIR_LENGTH];
    char command[5];
    char directoryName[MAX_DIR_LENGTH];
    Path(current, stackHead->next);
    do {
        fgets(userInput, MAX_DIR_LENGTH, stdin);
        sscanf(userInput, "%s %s", command, directoryName);
        if (!strcmp(command, "md"))
        {
            current = MakeDirectory(current, directoryName);
            Path(current, stackHead->next);
        }
        else if (!strcmp(command, "cd"))
        {
            current = ChangeDirectory(current, stackHead, directoryName);
            Path(current, stackHead->next);
        }
        else if (!strcmp(command, "cd.."))
        {
            if (current = ChangeToPreviousDirectory(stackHead) == NULL)
                current = C;
            Path(current, stackHead->next);
        }
        else if (!strcmp(command, "dir"))
        {
            PrintDirectory(current);
            Path(current, stackHead->next);
        }
        else if (!strcmp(command, "exit"))
            Remove(current);
        else
            printf("That's not an option!");
    } while (strcmp(command, "exit"));
    return 0;
}