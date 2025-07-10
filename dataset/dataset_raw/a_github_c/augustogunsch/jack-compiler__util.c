#include <string.h>
#include <stdlib.h>
#include "util.h"

char* heapstr(const char* str, int len) {
    int size = sizeof(char) * (len + 1);
    char* outstr = (char*)malloc(size);
    strcpy(outstr, str);
    return outstr;
}

char* ezheapstr(const char* str) {
    return heapstr(str, strlen(str));
}

void* copy(void* v, int size) {
    void* copy = malloc(size);
    memcpy(copy, v, size);
    return copy;
}

int countplaces(int n) {
    int places = 1;
    int divisor = 1;
    if(n < 0) {
        n = -n;
        places++;
    }
    while(n / divisor >= 10) {
        places++;
        divisor *= 10;
    }
    return places;
}

char* itoa(int i) {
    int size = sizeof(char)*(countplaces(i)+1);
    char* a = (char*)malloc(size);
    snprintf(a, size, "%i", i);
    return a;
}

char* dotlabel(char* n1, char* n2) {
    int sz = (strlen(n1) + strlen(n2) + 2) * sizeof(char);
    char* result = (char*)malloc(sz);
    sprintf(result, "%s.%s", n1, n2);
    return result;
}

STRINGLIST* onestr(const char* str) {
    STRINGLIST* strlist = (STRINGLIST*)malloc(sizeof(STRINGLIST));
    strlist->content = ezheapstr(str);
    strlist->next = NULL;
    return strlist;
}

STRINGLIST* initstrlist(const char** strs, int count) {
    STRINGLIST* strlist = (STRINGLIST*)malloc(sizeof(STRINGLIST));
    STRINGLIST* curr = strlist;
    for(int i = 0; i < count-1; i++) {
        curr->content = ezheapstr(strs[i]);
        curr->next = (STRINGLIST*)malloc(sizeof(STRINGLIST));
        curr = curr->next;
    }
    curr->content = ezheapstr(strs[count-1]);
    curr->next = NULL;
    return strlist;
}

void printstrlist(STRINGLIST* strlist, FILE* stream) {
    while(strlist != NULL) {
        fprintf(stream, "%s\n", strlist->content);
        strlist = strlist->next;
    }
}

void freestrlist(STRINGLIST* strlist) {
    STRINGLIST* next = strlist->next;
    free(strlist);
    if(next != NULL)
        freestrlist(next);
}

bool existsinarray(STRINGARRAY* arr, const char* item) {
    for(int i = 0; i < arr->size; i++)
        if(!strcmp(arr->items[i], item))
            return true;
    return false;
}
