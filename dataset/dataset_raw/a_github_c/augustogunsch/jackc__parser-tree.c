#include <stdlib.h>
#include "parser-tree.h"

void freeexpression(TERM* e);
void freeexpressionlist(EXPRESSIONLIST* el);
void freestatements(STATEMENT* s);

void freevardec(VARDEC* v) {
    freestrlist(v->names);
    free(v->debug);
    free(v);
}

void freevardecs(VARDEC* v) {
    VARDEC* next = v->next;
    freevardec(v);
    if(next != NULL)
        freevardecs(next);
}

void freeparameters(PARAMETER* p) {
    free(p->debug);
    PARAMETER* next = p->next;
    free(p);
    if(next != NULL)
        freeparameters(next);
}

void freearray(ARRAY* a) {
    freeexpression(a->exp);
    free(a);
}

void freesubroutcall(SUBROUTCALL* call) {
    if(call->parameters != NULL)
        freeexpressionlist(call->parameters);
    free(call->debug);
    free(call);
}

void freeexpression(TERM* e) {
    if(e->type == arrayitem)
        freearray(e->array);
    else if(e->type == innerexpression || e->type == unaryopterm)
        freeexpression(e->expression);
    else if(e->type == subroutcall)
        freesubroutcall(e->call);
    TERM* next = e->next;
    free(e);
    if(next != NULL)
        freeexpression(next);
}

void freeexpressionlist(EXPRESSIONLIST* el) {
    freeexpression(el->expression);
    EXPRESSIONLIST* next = el->next;
    free(el);
    if(next != NULL)
        freeexpressionlist(next);
}

void freelet(LETSTATEMENT* l) {
    if(l->arrayind != NULL)
        freeexpression(l->arrayind);
    freeexpression(l->expression);
    free(l);
}

void freecond(CONDSTATEMENT* cond) {
    freeexpression(cond->expression);
    if(cond->statements != NULL)
        freestatements(cond->statements);
    free(cond);
}

void freeif(IFSTATEMENT* st) {
    freecond(st->base);
    if(st->elsestatements != NULL)
        freestatements(st->elsestatements);
    free(st);
}

void freestatements(STATEMENT* s) {
    if(s->type == letstatement)
        freelet(s->letstatement);
    else if(s->type == ifstatement)
        freeif(s->ifstatement);
    else if(s->type == whilestatement)
        freecond(s->whilestatement);
    else if(s->type == dostatement)
        freesubroutcall(s->dostatement);
    else if(s->retstatement != NULL)
        freeexpression(s->retstatement);

    free(s->debug);
    STATEMENT* next = s->next;
    free(s);
    if(next != NULL)
        freestatements(next);
}

void freesubroutbody(SUBROUTBODY* b) {
    if(b->vardecs != NULL)
        freevardecs(b->vardecs);
    if(b->statements != NULL)
        freestatements(b->statements);
    free(b);
}

void freesubroutdecs(SUBROUTDEC* sr) {
    free(sr->debug);
    if(sr->parameters != NULL)
        freeparameters(sr->parameters);
    freesubroutbody(sr->body);
    SUBROUTDEC* next = sr->next;
    free(sr);
    if(next != NULL)
        freesubroutdecs(next);
}

void freeclassvardecs(CLASSVARDEC* cvd) {
    freevardec(cvd->base);
    CLASSVARDEC* next = cvd->next;
    free(cvd);
    if(next != NULL)
        freeclassvardecs(next);
}

void freetree(CLASS* c) {
    free(c->debug);

    if(c->vardecs != NULL)
        freeclassvardecs(c->vardecs);
    if(c->subroutdecs != NULL)
        freesubroutdecs(c->subroutdecs);

    CLASS* next = c->next;
    free(c);
    if(next != NULL)
        freetree(next);
}
