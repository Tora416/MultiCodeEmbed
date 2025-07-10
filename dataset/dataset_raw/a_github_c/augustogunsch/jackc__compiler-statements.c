#include <stdlib.h>
#include <string.h>
#include "compiler-expressions.h"
#include "compiler-statements.h"
#include "compiler-util.h"




LINE* popthat();
LINE* pushtemp();
char* mkcondlabel(char* name, int count);


LINEBLOCK* compileret(SCOPE* s, STATEMENT* st);
LINEBLOCK* compileif(SCOPE* s, STATEMENT* st);
LINEBLOCK* compilewhile(SCOPE* s, STATEMENT* st);
LINEBLOCK* compilelet(SCOPE* s, STATEMENT* st);
LINEBLOCK* compilestatement(SCOPE* s, STATEMENT* st);






LINE* popthat() {
    char* popthat[] = { "pop", "that", "0" };
    return mkln(popthat);
}

LINE* pushtemp() {
    char* pushtemp[] = { "push", "temp", "0" };
    return mkln(pushtemp);
}

char* mkcondlabel(char* name, int count) {
    int sz = (strlen(name) + countplaces(count) + 1) * sizeof(char);
    char* result = (char*)malloc(sz);
    sprintf(result, "%s%i", name, count);
    return result;
}


LINEBLOCK* compileret(SCOPE* s, STATEMENT* st) {
    TERM* e = st->retstatement;
    LINE* ret = onetoken("return");
    LINEBLOCK* blk = mklnblk(ret);

    
    if(e == NULL) {
        char* tokens[] = { "push", "constant", "0" };
        appendlnbefore(blk, mkln(tokens));
    } else
        blk = mergelnblks(compileexpression(s, st->debug, e), blk);

    return blk;
}

LINEBLOCK* compileif(SCOPE* s, STATEMENT* st) {
    IFSTATEMENT* ifst = st->ifstatement;
    LINEBLOCK* blk = compileexpression(s, st->debug, ifst->base->expression);

    pthread_mutex_lock(&(s->compiler->ifmutex));
    static int ifcount = 0;
    int mycount = ifcount;
    ifcount++;
    pthread_mutex_unlock(&(s->compiler->ifmutex));
    
    char* truelabel = mkcondlabel("IF_TRUE", mycount);
    char* ifgoto[] = { "if-goto", truelabel };
    appendln(blk, mkln(ifgoto));
    
    char* falselabel = mkcondlabel("IF_FALSE", mycount);
    char* gotofalse[] = { "goto", falselabel };
    appendln(blk, mkln(gotofalse));

    char* truelabelln[] = { "label", truelabel };
    appendln(blk, mkln(truelabelln));

    blk = mergelnblks(blk, compilestatements(s, ifst->base->statements));

    char* endlabel;
    bool haselse = ifst->elsestatements != NULL;
    if(haselse) {
        endlabel = mkcondlabel("IF_END", mycount);
        char* endgoto[] = { "goto", endlabel };
        appendln(blk, mkln(endgoto));
    }

    char* falselabelln[] = { "label", falselabel};
    appendln(blk, mkln(falselabelln));

    if(haselse) {
        blk = mergelnblks(blk, compilestatements(s, ifst->elsestatements));
        char* endlabelln[] = { "label", endlabel };
        appendln(blk, mkln(endlabelln));
        free(endlabel);
    }

    free(falselabel);
    free(truelabel);

    return blk;
}

LINEBLOCK* compilewhile(SCOPE* s, STATEMENT* st) {
    CONDSTATEMENT* w = st->whilestatement;
    LINEBLOCK* blk = compileexpression(s, st->debug, w->expression);

    pthread_mutex_lock(&(s->compiler->whilemutex));
    static int whilecount = 0;
    int mycount = whilecount;
    whilecount++;
    pthread_mutex_unlock(&(s->compiler->whilemutex));

    char* explabel = mkcondlabel("WHILE_EXP", mycount);
    char* explabelln[] = { "label", explabel };
    appendlnbefore(blk, mkln(explabelln));

    appendln(blk, onetoken("not"));

    char* endlabel = mkcondlabel("WHILE_END", mycount);
    char* ifgoto[] = { "if-goto", endlabel };
    appendln(blk, mkln(ifgoto));

    blk = mergelnblks(blk, compilestatements(s, w->statements));

    char* gotoln[] = { "goto", explabel };
    appendln(blk, mkln(gotoln));

    char* endlabelln[] = { "label", endlabel };
    appendln(blk, mkln(endlabelln));

    free(explabel);
    free(endlabel);

    return blk;
}

LINEBLOCK* compilelet(SCOPE* s, STATEMENT* st) {
    LETSTATEMENT* l = st->letstatement;
    LINEBLOCK* blk = compileexpression(s, st->debug, l->expression);

    if(l->arrayind != NULL) {
        appendlnbefore(blk, onetoken("add"));
        appendlnbefore(blk, pushvar(s, st->debug, l->varname));
        blk = mergelnblks(compileexpression(s, st->debug, l->arrayind), blk);

        appendln(blk, poptemp());
        appendln(blk, popthatadd());
        appendln(blk, pushtemp());
        appendln(blk, popthat());
    }
    else
        appendln(blk, popvar(s, st->debug, l->varname));
    return blk;
}

LINEBLOCK* compilestatement(SCOPE* s, STATEMENT* st) {
    if(st->type == dostatement) return compilesubroutcall(s, st->dostatement);
    if(st->type == returnstatement) return compileret(s, st);
    if(st->type == ifstatement) return compileif(s, st);
    if(st->type == whilestatement) return compilewhile(s, st);
    return compilelet(s, st);
}

LINEBLOCK* compilestatements(SCOPE* s, STATEMENT* sts) {
    LINEBLOCK* head = NULL;
    while(sts != NULL) {
        head = mergelnblks(head, compilestatement(s, sts));
        sts = sts->next;
    }
    return head;
}

LINEBLOCK* compilestatementsretlast(SCOPE* s, STATEMENT* sts, STATEMENT** retlast) {
    LINEBLOCK* head = NULL;
    STATEMENT* last = NULL;
    while(sts != NULL) {
        head = mergelnblks(head, compilestatement(s, sts));
        last = sts;
        sts = sts->next;
    }
    *retlast = last;
    return head;
}
