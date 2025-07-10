#include <stdlib.h>
#include "compiler-statements.h"
#include "compiler-structure.h"
#include "compiler-util.h"




int countlocalvars(VARDEC* decs);
int countstrs(STRINGLIST* ls);
int getobjsize(CLASS* c);
LINE* mksubdeclabel(CLASS* c, SUBROUTDEC* sd);


LINEBLOCK* compilefunbody(SCOPE* s, CLASS* cl, SUBROUTDEC* d);
LINEBLOCK* compilefundec(SCOPE* s, CLASS* cl, SUBROUTDEC* f);
LINEBLOCK* compileconstructor(SCOPE* s, CLASS* cl, SUBROUTDEC* con);
LINEBLOCK* compilemethod(SCOPE* s, CLASS* cl, SUBROUTDEC* m);





int countlocalvars(VARDEC* decs) {
    int i = 0;
    while(decs != NULL) {
        STRINGLIST* curr = decs->names;
        while(curr != NULL) {
            i++;
            curr = curr->next;
        }
        decs = decs->next;
    }
    return i;
}

int countstrs(STRINGLIST* ls) {
    int count = 0;
    while(ls != NULL) {
        count++;
        ls = ls->next;
    }
    return count;
}

int getobjsize(CLASS* c) {
    CLASSVARDEC* curr = c->vardecs;
    int count = 0;
    while(curr != NULL) {
        if(curr->type == field)
            count += countstrs(curr->base->names);
        curr = curr->next;
    }
    return count;
}

LINE* mksubdeclabel(CLASS* c, SUBROUTDEC* sd) {
    char* labelstrs[] = { "function", dotlabel(c->name, sd->name), itoa(countlocalvars(sd->body->vardecs)) };
    LINE* label = mkln(labelstrs);
    free(labelstrs[1]);
    free(labelstrs[2]);
    label->next = NULL;
    return label;
}


LINEBLOCK* compilefunbody(SCOPE* s, CLASS* cl, SUBROUTDEC* d) {
    SUBROUTBODY* b = d->body;
    SCOPE* myscope = mkscope(s);
    myscope->currclass = cl;
    if(b->vardecs != NULL)
        addlocalvars(myscope, b->vardecs);

    if(b->statements == NULL) {
        eprintf("Subroutine body has no statements; file '%s', line %i\n",
                d->debug->file, d->debug->definedat);
        exit(1);
    }

    STATEMENT* last;
    LINEBLOCK* head = compilestatementsretlast(myscope, b->statements, &last);
    if(last->type != returnstatement) {
        eprintf("Subroutine must end with a return statement; file '%s', line %i\n",
                last->debug->file, last->debug->definedat);
        exit(1);
    }

    freescope(myscope);
    return head;
}

LINEBLOCK* compilefundec(SCOPE* s, CLASS* cl, SUBROUTDEC* f) {
    LINE* label = mksubdeclabel(cl, f);

    LINEBLOCK* body = compilefunbody(s, cl, f);
    appendlnbefore(body, label);
    return body;
}

LINEBLOCK* compileconstructor(SCOPE* s, CLASS* cl, SUBROUTDEC* con) {
    LINE* label = mksubdeclabel(cl, con);
    LINEBLOCK* blk = mklnblk(label);

    char* size[] = { "push", "constant", itoa(getobjsize(cl)) };
    char* memalloc[] = { "call", "Memory.alloc", "1" };
    char* poppointer[] = { "pop", "pointer", "0" };
    appendln(blk, mkln(size));
    appendln(blk, mkln(memalloc));
    appendln(blk, mkln(poppointer));
    free(size[2]);

    if(con->body != NULL)
        return mergelnblks(blk, compilefunbody(s, cl, con));
    else
        return blk;
}

LINEBLOCK* compilemethod(SCOPE* s, CLASS* cl, SUBROUTDEC* m) {
    LINE* label = mksubdeclabel(cl, m);
    LINEBLOCK* blk = mklnblk(label);

    char* pusharg0[] = { "push", "argument", "0" };
    char* poppointer[] = { "pop", "pointer", "0" };
    appendln(blk, mkln(pusharg0));
    appendln(blk, mkln(poppointer));

    if(m->body != NULL) 
        return mergelnblks(blk, compilefunbody(s, cl, m));
    else
        return blk;
}

LINEBLOCK* compilesubroutdec(SCOPE* s, CLASS* cl, SUBROUTDEC* sd) {
    SCOPE* myscope = mkscope(s);
    LINEBLOCK* blk;
    if(sd->parameters != NULL)
        addparameters(myscope, sd->subroutclass == method, sd->parameters);
    if(sd->subroutclass == function)
        blk = compilefundec(myscope, cl, sd);
    else if(sd->subroutclass == constructor)
        blk = compileconstructor(myscope, cl, sd);
    else
        blk = compilemethod(myscope, cl, sd);
    freescope(myscope);
    return blk;
}
