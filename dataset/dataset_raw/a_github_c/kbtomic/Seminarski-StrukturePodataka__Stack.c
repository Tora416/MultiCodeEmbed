#include "Stack.h"
#include "AllocateMemory.h"
islandPointer PopStack(stackPointer stackHead)
{
    stackPointer tempStackElement = stackHead->next, prev = stackHead->next;
    if (!tempStackElement->next)
        return NULL;
    while (tempStackElement->next)
    {
        prev = tempStackElement;
        tempStackElement = tempStackElement->next;
    }
    islandPointer island = tempStackElement->data;
    prev->next = tempStackElement->next;
    free(tempStackElement);
    return island;
}
int PushStack(islandPointer current, stackPointer stackHead)
{
    stackPointer newStackElement;
    stackPointer tempStackElement = stackHead;
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
int CleanStack(stackPointer stackHead)
{
    stackPointer prev = stackHead->next, top = stackHead->next;
    stackHead = stackHead->next;
    while (top->next)
    {
        while (stackHead->next)
        {
            prev = stackHead;
            stackHead = stackHead->next;
        }
        free(stackHead);
        prev->next = NULL;
        stackHead = top->next;
        prev = top;
    }
    return 0;
}
stackPointer CreateStackHead()
{
    stackPointer stackHead = AllocateMemoryForStack();
    stackHead->data = NULL;
    stackHead->next = NULL;
    return stackHead;
}