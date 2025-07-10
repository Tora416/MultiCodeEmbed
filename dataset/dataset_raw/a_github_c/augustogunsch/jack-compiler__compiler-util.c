#include <stdlib.h>
#include "compiler-util.h"

LINE* opvarraw(SCOPE* s, char* op, VAR* v) {
    char* tokens[] = { op, v->memsegment, itoa(v->index) };
    LINE* ln = mksimpleln(tokens, strcount(tokens));
    free(tokens[2]);
    return ln;
}

LINE* pushvarraw(SCOPE* s, VAR* v) {
    return opvarraw(s, "push", v);
}

LINE* pushvar(SCOPE* s, DEBUGINFO* d, const char* name) {
    return opvarraw(s, "push", getvarmustexist(s, d, name));
}

LINE* popvar(SCOPE* s, DEBUGINFO* d, const char* name) {
    return opvarraw(s, "pop", getvarmustexist(s, d, name));
}

LINE* poptemp() {
    char* poptemp[] = { "pop", "temp", "0" };
    return mksimpleln(poptemp, strcount(poptemp));
}

LINE* popthatadd() {
    char* popthatadd[] = { "pop", "pointer", "1" };
    return mksimpleln(popthatadd, strcount(popthatadd));
}

LINE* onetoken(char* str) {
    LINE* ln = mkline(1);
    addtoken(ln, ezheapstr(str));
    ln->next = NULL;
    return ln;
}

LINE* mksimpleln(char** tokens, int count) {
    LINE* ln = mkline(count);
    for(int i = 0; i < count; i++)
        addtoken(ln, ezheapstr(tokens[i]));
    ln->next = NULL;
    return ln;
}
