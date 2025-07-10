#include <stdlib.h>
#include "vm-lines.h"

LINE* mkline(int size) {
    LINE* ln = (LINE*)malloc(sizeof(LINE));
    ln->tokens = (char**)malloc(sizeof(char*)*size);
    ln->count = 0;
    return ln;
}

void addtoken(LINE* ln, char* token) {
    ln->tokens[ln->count] = token;
    ln->count++;
}

void println(LINE* ln, FILE* stream) {
    for(int i = 0; i < ln->count; i++) {
        fprintf(stream, "%s", ln->tokens[i]);
        if(i + 1 < ln->count)
            fprintf(stream, " ");
    }
    fprintf(stream, "\n");
}

void printlns(LINE* lns, FILE* stream) {
    while(lns != NULL) {
        println(lns, stream);
        lns = lns->next;
    }
}

void freeln(LINE* ln) {
    for(int i = 0; i < ln->count; i++)
        free(ln->tokens[i]);
    free(ln->tokens);
    free(ln);
}

void freelns(LINE* lns) {
    LINE* next = lns->next;
    freeln(lns);
    if(next != NULL)
        freelns(next);
}

void freelnblk(LINEBLOCK* blk) {
    freelns(blk->head);
    free(blk);
}

LINEBLOCK* mklnblk(LINE* start) {
    LINEBLOCK* blk = (LINEBLOCK*)malloc(sizeof(LINEBLOCK));
    blk->head = start;
    blk->tail = start;
    return blk;
}

LINEBLOCK* mergelnblks(LINEBLOCK* head, LINEBLOCK* tail) {
    if(head == NULL)
        return tail;
    head->tail->next = tail->head;
    head->tail = tail->tail;
    free(tail);
    return head;
}

void appendln(LINEBLOCK* lnblk, LINE* ln) {
    lnblk->tail->next = ln;
    lnblk->tail = ln;
}

void appendlnbefore(LINEBLOCK* lnblk, LINE* ln) {
    ln->next = lnblk->head;
    lnblk->head = ln;
}
