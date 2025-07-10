#include <stdlib.h>
#include <string.h>
#include "os.h"
#include "util.h"

CLASS* mkosclass(CLASS* os, const char* name) {
    CLASS* c = (CLASS*)malloc(sizeof(CLASS));
    c->name = ezheapstr(name);
    c->subroutdecs = NULL;
    c->next = os;
    return c;
}

void adddec(CLASS* c, SUBROUTCLASS subroutclass, char* type, const char* name) {
    SUBROUTDEC* dec = (SUBROUTDEC*)malloc(sizeof(SUBROUTDEC));
    dec->class = c;
    dec->subroutclass = subroutclass;
    dec->name = ezheapstr(name);
    dec->type = ezheapstr(type);
    dec->next = c->subroutdecs;
    c->subroutdecs = dec;
}

CLASS* mkmath(CLASS* os) {
    CLASS* mathclass = mkosclass(os, "Math");
    adddec(mathclass, function, "int", "multiply");
    adddec(mathclass, function, "int", "divide");
    adddec(mathclass, function, "int", "abs");
    adddec(mathclass, function, "int", "min");
    adddec(mathclass, function, "int", "max");
    adddec(mathclass, function, "int", "sqrt");
    return mathclass;
}

CLASS* mkstringclass(CLASS* os) {
    CLASS* strclass = mkosclass(os, "String");
    adddec(strclass, constructor, "String", "new");
    adddec(strclass, method, "int", "dispose");
    adddec(strclass, method, "int", "length");
    adddec(strclass, method, "char", "charAt");
    adddec(strclass, method, "void", "setCharAt");
    adddec(strclass, method, "String", "appendChar");
    adddec(strclass, method, "void", "eraseLastChar");
    adddec(strclass, method, "int", "intValue");
    adddec(strclass, method, "void", "setInt");
    adddec(strclass, function, "char", "backSpace");
    adddec(strclass, function, "char", "doubleQuote");
    adddec(strclass, function, "char", "newLine");
    return strclass;
}

CLASS* mkarray(CLASS* os) {
    CLASS* arrclass = mkosclass(os, "Array");
    adddec(arrclass, function, "Array", "new");
    adddec(arrclass, method, "void", "dispose");
    return arrclass;
}

CLASS* mkoutput(CLASS* os) {
    CLASS* outclass = mkosclass(os, "Output");
    adddec(outclass, function, "void", "moveCursor");
    adddec(outclass, function, "void", "printChar");
    adddec(outclass, function, "void", "printString");
    adddec(outclass, function, "void", "printInt");
    adddec(outclass, function, "void", "println");
    adddec(outclass, function, "void", "backSpace");
    return outclass;
}

CLASS* mkscreen(CLASS* os) {
    CLASS* scrclass = mkosclass(os, "Screen");
    adddec(scrclass, function, "void", "clearScreen");
    adddec(scrclass, function, "void", "setColor");
    adddec(scrclass, function, "void", "drawPixel");
    adddec(scrclass, function, "void", "drawLine");
    adddec(scrclass, function, "void", "drawRectangle");
    adddec(scrclass, function, "void", "drawCircle");
    return scrclass;
}

CLASS* mkkeyboard(CLASS* os) {
    CLASS* kbdclass = mkosclass(os, "Keyboard");
    adddec(kbdclass, function, "char", "keyPressed");
    adddec(kbdclass, function, "char", "readChar");
    adddec(kbdclass, function, "String", "readLine");
    adddec(kbdclass, function, "int", "readInt");
    return kbdclass;
}

CLASS* mkmemory(CLASS* os) {
    CLASS* memclass = mkosclass(os, "Memory");
    adddec(memclass, function, "int", "peek");
    adddec(memclass, function, "void", "poke");
    adddec(memclass, function, "Array", "alloc");
    adddec(memclass, function, "void", "deAlloc");
    return memclass;
}

CLASS* mksys(CLASS* os) {
    CLASS* sysclass = mkosclass(os, "Sys");
    adddec(sysclass, function, "void", "halt");
    adddec(sysclass, function, "void", "error");
    adddec(sysclass, function, "void", "wait");
    return sysclass;
}

CLASS* mkos() {
    CLASS* os = mkmath(NULL);
    os = mkstringclass(os);
    os = mkarray(os);
    os = mkoutput(os);
    os = mkscreen(os);
    os = mkkeyboard(os);
    os = mkmemory(os);
    os = mksys(os);
    return os;
}

void freeossubroutdecs(SUBROUTDEC* d) {
    free(d->name);
    free(d->type);
    SUBROUTDEC* next = d->next;
    free(d);
    if(next != NULL)
        freeossubroutdecs(next);
}

void freeosclasses(CLASS* c) {
    freeossubroutdecs(c->subroutdecs);
    free(c->name);
    CLASS* next = c->next;
    free(c);
    if(next != NULL)
        freeosclasses(next);
}

void freeos(CLASS* os) {
    freeosclasses(os);
}

SUBROUTDEC* getsubroutdecinclass(CLASS* c, const char* name) {
    SUBROUTDEC* curr = c->subroutdecs;
    while(curr != NULL) {
        if(!strcmp(curr->name, name))
            return curr;
        curr = curr->next;
    }
    return NULL;
}

CLASS* getosclass(CLASS* os, const char* name) {
    CLASS* curr = os;
    while(curr != NULL) {
        if(!strcmp(curr->name, name))
            return curr;
        curr = curr->next;
    }
    return NULL;
}

SUBROUTDEC* getossubroutdec(CLASS* os, SUBROUTCALL* call) {
    CLASS* c = getosclass(os, call->parentname);
    if(c == NULL)
        return NULL;
    return getsubroutdecinclass(c, call->name);
}
