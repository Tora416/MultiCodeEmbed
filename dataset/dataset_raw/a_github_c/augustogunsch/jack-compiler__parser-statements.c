#include <stdlib.h>
#include "parser-expressions.h"
#include "parser-util.h"
#include "parser-statements.h"




STATEMENT* mkstatement(PARSER* p, STATEMENTTYPE t);

STATEMENT* parsestatementnullified(PARSER* p);
STATEMENT* parselet(PARSER* p);
CONDSTATEMENT* parsecond(PARSER* p);
STATEMENT* parseif(PARSER* p);
STATEMENT* parsewhile(PARSER* p);
STATEMENT* parsedo(PARSER* p);
STATEMENT* parsereturn(PARSER* p);




STATEMENT* mkstatement(PARSER* p, STATEMENTTYPE t) {
    STATEMENT* s = (STATEMENT*)malloc(sizeof(STATEMENT));
    s->type = t;
    s->debug = getdebug(p);
    return s;
}




STATEMENT* parsestatementnullified(PARSER* p) {
    if(equals(p, "let")) return parselet(p);
    if(equals(p, "if")) return parseif(p);
    if(equals(p, "while")) return parsewhile(p);
    if(equals(p, "do")) return parsedo(p);
    if(equals(p, "return")) return parsereturn(p);
    return NULL;
}

STATEMENT* parsestatements(PARSER* p) {
    STATEMENT* head = parsestatementnullified(p);
    STATEMENT* curr = head;
    STATEMENT* next;
    while(next = parsestatementnullified(p), next != NULL) {
        curr->next = next;
        curr = next;
    }
    if(curr != NULL)
        curr->next = NULL;
    return head;
}

STATEMENT* parselet(PARSER* p) {
    next(p);
    STATEMENT* s = mkstatement(p, letstatement);
    LETSTATEMENT* letst = (LETSTATEMENT*)malloc(sizeof(LETSTATEMENT));

    letst->varname = parseidentifier(p);
    
    if(equals(p, "[")) {
        next(p);
        letst->arrayind = parseexpression(p);
        checkcontent(p, "]");
    }
    else
        letst->arrayind = NULL;

    checkcontent(p, "=");

    letst->expression = parseexpression(p);

    checkcontent(p, ";");

    s->type = letstatement;
    s->letstatement = letst;
    return s;
}

CONDSTATEMENT* parsecond(PARSER* p) {
    checkcontent(p, "(");

    CONDSTATEMENT* st = (CONDSTATEMENT*)malloc(sizeof(CONDSTATEMENT));

    st->expression = parseexpression(p);

    checkcontent(p, ")");
    checkcontent(p, "{");

    st->statements = parsestatements(p);

    checkcontent(p, "}");
    return st;
}

STATEMENT* parseif(PARSER* p) {
    next(p);
    STATEMENT* s = mkstatement(p, ifstatement);
    IFSTATEMENT* ifst = (IFSTATEMENT*)malloc(sizeof(IFSTATEMENT));

    ifst->base = parsecond(p);

    if(equals(p, "else")) {
        next(p);
        checkcontent(p, "{");
        ifst->elsestatements = parsestatements(p);
        checkcontent(p, "}");
    }
    else
        ifst->elsestatements = NULL;

    s->type = ifstatement;
    s->ifstatement = ifst;
    return s;
}

STATEMENT* parsewhile(PARSER* p) {
    next(p);
    STATEMENT* s = mkstatement(p, whilestatement);

    s->whilestatement = parsecond(p);
    return s;
}

STATEMENT* parsedo(PARSER* p) {
    next(p);
    STATEMENT* s = mkstatement(p, dostatement);

    s->dostatement = parsesubroutcall(p);

    checkcontent(p, ";");
    return s;
}

STATEMENT* parsereturn(PARSER* p) {
    next(p);
    STATEMENT* s = mkstatement(p, returnstatement);

    s->retstatement = parseexpressionnullified(p);

    checkcontent(p, ";");
    return s;
}
