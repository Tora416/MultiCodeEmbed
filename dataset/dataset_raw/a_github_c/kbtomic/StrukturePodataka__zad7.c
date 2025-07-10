#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct stog* pozicija;
struct stog {
    int el;
    pozicija next;
};
int push(pozicija head, int element);
int pop(pozicija head);
int dat(pozicija head);
int zbroj(pozicija head);
int razlika(pozicija head);
int umnozak(pozicija head);
int kvocijent(pozicija head);
int main()
{
    struct stog Head;
    Head.next = NULL;
    dat(&Head);
    printf("Rezultat je %d\n", Head.next->el);
    return 0;
}
int dat(pozicija head)
{
    FILE* fp = NULL;
    fp = fopen("postfix.txt", "r");
    char operacija[15];
    if (fp == NULL)
    {
        printf("Neuspjesno otvaranje datoteke!\n");
        return 1;
    }
    while (!feof(fp))
    {
        int br = 0;
        int procitani = sscanf(fp, "%d", &br);
        if (!procitani) {
            if (!strcmp(procitani, "+"))
                zbroj(head);
            else if (!strcmp(procitani, "-"))
                razlika(head);
            else if (!strcmp(procitani, "*"))
                umnozak(head);
            else if (!strcmp(procitani, "/"))
                kvocijent(head);
        }
        else
            push(head, procitani);
    }
    fclose(fp);
    return 0;

}
int push(pozicija head, int element)
{
    pozicija novi;
    novi = (pozicija)malloc(sizeof(struct stog));
    if (novi == NULL)
    {
        printf("Neuspjesna alokacija memorije!\n");
        return 1;
    }
    novi->el = element;
    novi->next = head->next;
    head->next = novi;

    return 0;
}
int pop(pozicija head)
{
    pozicija temp = NULL;
    int element;
    if (head == NULL)
        printf("Stog je prazan!\n");
    else {
        temp = head->next;
        element = temp->el;
        head->next = temp->next;
        free(temp);
    }
    return element;
}
int zbroj(pozicija head)
{
    int prviBroj = pop(head);
    int drugiBroj = pop(head);
    push(head, drugiBroj + prviBroj);
    return 0;
}
int razlika(pozicija head)
{
    int prviBroj = pop(head);
    int drugiBroj = pop(head);
    push(head, drugiBroj - prviBroj);
    return 0;
}
int umnozak(pozicija head)
{
    int prviBroj = pop(head);
    int drugiBroj = pop(head);
    push(head, drugiBroj * prviBroj);
    return 0;
}
int kvocijent(pozicija head)
{
    int prviBroj = pop(head);
    int drugiBroj = pop(head);
    push(head, drugiBroj / prviBroj);
    return 0;
}
