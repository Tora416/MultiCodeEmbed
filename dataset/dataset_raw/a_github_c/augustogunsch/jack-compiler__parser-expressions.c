#include <stdlib.h>
#include "util.h"
#include "parser-util.h"
#include "parser-expressions.h"

    const char* keywordsarr[] = { "true", "false", "null", "this" };
    const char* opsarr[] = { "+", "-", "*", "/", "&", "|", "<", ">", "=" };
    mkstrlist(keywordconstants, keywordsarr);
mkstrlist(operators, opsarr);




bool isop(TOKEN* t);


TERM* parsetermnullified(PARSER* p);
TERM* parseterm(PARSER* p);
TERM* mkterm(TERMTYPE type);
TERM* parseint(PARSER* p);
TERM* parsestr(PARSER* p);
TERM* parsekeyword(PARSER* p);
TERM* parseunaryopterm(PARSER* p);
TERM* parseinnerexpression(PARSER* p);
TERM* parsecalltermnullified(PARSER* p);
TERM* parsearrayterm(PARSER* p);
TERM* parsevarterm(PARSER* p);
TERM* parseidentifierterm(PARSER* p);
SUBROUTCALL* nullsubroutcall(PARSER* p, SUBROUTCALL* c);
SUBROUTCALL* parsesubroutcallnullified(PARSER* p);




bool isop(TOKEN* t) {
    for(int i = 0; i < operators.size; i++)
        if(!strcmp(t->token, operators.items[i]))
            return true;
    return false;
}


TERM* parsetermnullified(PARSER* p) {
    TOKENTYPE type = p->current->type;
    if(type == integer) return parseint(p);
    if(type == string) return parsestr(p);
    if(type == keyword) return parsekeyword(p);
    if(type == identifier) return parseidentifierterm(p);
    if(equals(p, "-") || equals(p, "~")) return parseunaryopterm(p);
    if(equals(p, "(")) return parseinnerexpression(p);
    return NULL;
}

TERM* parseterm(PARSER* p) {
    TERM* t = parsetermnullified(p);
    if(t == NULL)
        unexpected(p);
    return t;
}

TERM* mkterm(TERMTYPE type) {
    TERM* t = (TERM*)malloc(sizeof(TERM));
    t->type = type;
    return t;
}

TERM* parseint(PARSER* p) {
    TERM* t = mkterm(intconstant);
    t->integer = atoi(p->current->token);
    next(p);
    return t;
}

TERM* parsestr(PARSER* p) {
    TERM* t = mkterm(stringconstant);
    t->string = p->current->token;
    next(p);
    return t;
}

TERM* parsekeyword(PARSER* p) {
    TERM* t = mkterm(keywordconstant);
    if(!existsinarray(&keywordconstants, p->current->token))
        unexpected(p);
    t->string = p->current->token;
    next(p);
    return t;
}

TERM* parseunaryopterm(PARSER* p) {
    TERM* t = mkterm(unaryopterm);
    t->unaryop = p->current->token[0];
    next(p);
    t->expression = parseterm(p);
    t->expression->next = NULL;
    return t;
}

TERM* parseinnerexpression(PARSER* p) {
    TERM* t = mkterm(innerexpression);
    next(p);
    t->expression = parseexpression(p);
    checkcontent(p, ")");
    return t;
}

TERM* parsecalltermnullified(PARSER* p) {
    SUBROUTCALL* call = parsesubroutcallnullified(p);
    if(call == NULL)
        return NULL;
    TERM* t = mkterm(subroutcall);
    t->call = call;
    return t;
}

TERM* parsearrayterm(PARSER* p) {
    TERM* t = mkterm(arrayitem);
    t->array = (ARRAY*)malloc(sizeof(ARRAY));
    t->array->name = p->current->token;
    next(p);
    checkcontent(p, "[");
    t->array->exp = parseexpression(p);
    checkcontent(p, "]");
    return t;
}

TERM* parsevarterm(PARSER* p) {
    TERM* t = mkterm(varname);
    t->string = p->current->token;
    next(p);
    return t;
}

TERM* parseidentifierterm(PARSER* p) {
    TERM* t = parsecalltermnullified(p);
    if(t == NULL)
        if(nextequals(p, "["))
            return parsearrayterm(p);
        else
            return parsevarterm(p);
    else
        return t;
}

TERM* parseexpressionnullified(PARSER* p) {
    TERM* head = parsetermnullified(p);
    TERM* current = head;
    TERM* nextt;
    while(isop(p->current)) {
        current->op = p->current->token[0]; 
        next(p);
        nextt = parseterm(p);
        current->next = nextt;
        current = nextt;
    }
    if(current != NULL)
        current->next = NULL;
    return head;
}

TERM* parseexpression(PARSER* p) {
    TERM* t = parseexpressionnullified(p);
    if(t == NULL)
        unexpected(p);
    return t;
}

SUBROUTCALL* nullsubroutcall(PARSER* p, SUBROUTCALL* c) {
    free(c->debug);
    free(c);
    rewindparser(p);
    return NULL;
}

SUBROUTCALL* parsesubroutcallnullified(PARSER* p) {
    if(p->current->type != identifier)
        return NULL;

    anchorparser(p);
    SUBROUTCALL* c = (SUBROUTCALL*)malloc(sizeof(SUBROUTCALL));

    c->debug = getdebug(p);

    if(nextequals(p, ".")) {
        c->parentname = p->current->token;
        next(p);
        next(p);
    }
    else
        c->parentname = NULL;

    if(p->current->type != identifier)
        return nullsubroutcall(p, c);
    c->name = p->current->token;
    next(p);

    if(differs(p, "("))
        return nullsubroutcall(p, c);
    next(p);

    c->parameters = parseexpressionlist(p);

    if(differs(p, ")"))
        return nullsubroutcall(p, c);
    next(p);
    return c;
}

SUBROUTCALL* parsesubroutcall(PARSER* p) {
    SUBROUTCALL* c = (SUBROUTCALL*)malloc(sizeof(SUBROUTCALL));
    c->debug = getdebug(p);

    if(nextequals(p, ".")) {
        c->parentname = parseidentifier(p);
        next(p);
    }
    else
        c->parentname = NULL;

    c->name = parseidentifier(p);

    checkcontent(p, "(");

    c->parameters = parseexpressionlist(p);

    checkcontent(p, ")");
    return c;
}

EXPRESSIONLIST* parseexpressionlist(PARSER* p) {
    if(!strcmp(p->current->token, ")"))
        return NULL;
    EXPRESSIONLIST* head = (EXPRESSIONLIST*)malloc(sizeof(EXPRESSIONLIST));
    head->expression = parseexpressionnullified(p);
    EXPRESSIONLIST* current = head;
    EXPRESSIONLIST* nextls;
    while(!strcmp(p->current->token, ",")) {
        next(p);
        nextls = (EXPRESSIONLIST*)malloc(sizeof(EXPRESSIONLIST));
        nextls->expression = parseexpression(p);
        current->next = nextls;
        current = nextls;
    }
    if(current != NULL)
        current->next = NULL;
    return head;
}
