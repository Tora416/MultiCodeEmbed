#include <stdlib.h>
#include "parser-util.h"
#include "util.h"

const char* tokentypesarr[] = { "keyword", "identifier", "symbol",
                    "integerConstant", "stringConstant" };
mkstrlist(tokentypes, tokentypesarr);

void unexpected(PARSER* p) {
    eprintf("Unexpected token '%s' (of type %s); line %i, file '%s'\n",
                p->current->token, tokentypes.items[p->current->type],
                p->current->definedat, p->file);
    exit(1);
}

void checktype(PARSER* p, TOKENTYPE type) {
    if(p->current->type != type) {
        eprintf("Unexpected %s; file '%s', line %i\n", 
                tokentypes.items[p->current->type], p->file,
                    p->current->definedat);
        exit(1);
    }
}

void checkcontent(PARSER* p, const char* content) {
    if(differs(p, content))
        unexpected(p);
    next(p);
}

char* parseidentifier(PARSER* p) {
    checktype(p, identifier);
    char* result = p->current->token;
    next(p);
    return result;
}

DEBUGINFO* getdebug(PARSER* p) {
    DEBUGINFO* d = (DEBUGINFO*)malloc(sizeof(DEBUGINFO));
    d->file = p->file;
    d->definedat = p->current->definedat;
    return d;
}
