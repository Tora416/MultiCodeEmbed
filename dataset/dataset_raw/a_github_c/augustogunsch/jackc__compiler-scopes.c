#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include "compiler.h"
#include "compiler-scopes.h"

typedef enum { local, staticseg, arg, fieldseg } MEMSEGMENT;
char* memsegnames[] = { "local", "static", "argument", "this" };


void doubledeclaration(const char* name, DEBUGINFO* d1, DEBUGINFO* d2);
void ensurenoduplicate(SCOPE* s, DEBUGINFO* d, char* name);


VAR* getvarinvars(VAR* vars, const char* name);
CLASS* getclass(SCOPE* s, const char* name);
SUBROUTDEC* getsubroutdecfromlist(SUBROUTDEC* start, char* name);
SUBROUTDEC* getmethod(SCOPE* s, VAR* parent, SUBROUTCALL* call);
SUBROUTDEC* getfunction(SCOPE* s, SUBROUTCALL* call);
SUBROUTDEC* getsubroutdecwithparent(SCOPE* s, SUBROUTCALL* call, VAR** varret);
SUBROUTDEC* getsubroutdecwithoutparent(SCOPE* s, SUBROUTCALL* call);
SUBROUTDEC* getsubroutdec(SCOPE* s, const char* name);


VAR* mkvar(char* type, char* name, bool primitive, DEBUGINFO* debug, MEMSEGMENT seg, int i);
void addvar(SCOPE* s, VAR** dest, VAR* v);
void addlocalvar(SCOPE* s, VARDEC* v, int* i);
void addstaticvar(SCOPE* s, CLASSVARDEC* v);
void addfield(SCOPE* s, CLASSVARDEC* v, int* i);
void addclassvardec(SCOPE* s, CLASSVARDEC* v, int* i);
void addparameter(SCOPE* s, PARAMETER* p, int* i);


void doubledeclaration(const char* name, DEBUGINFO* d1, DEBUGINFO* d2) {
    eprintf("Double declaration of '%s' at '%s', line %i; previously defined at '%s', line %i\n",
                name, d1->file, d1->definedat, d2->file, d2->definedat);
    exit(1);
}

void notdeclared(const char* name, DEBUGINFO* debug) {
    eprintf("'%s' not declared; file '%s', line %i\n", name, debug->file, debug->definedat);
    exit(1);
}

void invalidparent(SUBROUTCALL* call) {
    eprintf("Invalid subroutine parent '%s'; file '%s', line %i\n", call->parentname, call->debug->file, call->debug->definedat);
    exit(1);
}

void ensurenoduplicate(SCOPE* s, DEBUGINFO* d, char* name) {
    VAR* v = getvar(s, name);
    if(v != NULL)
        doubledeclaration(name, d, v->debug);

    CLASS* c = getclass(s, name);
    if(c != NULL)
        doubledeclaration(name, d, c->debug);

    SUBROUTDEC* sr = getsubroutdec(s, name);
    if(sr != NULL)
        doubledeclaration(name, d, sr->debug);
}


SCOPE* mkscope(SCOPE* prev) {
    SCOPE* s = (SCOPE*)malloc(sizeof(SCOPE));
    s->previous = prev;
    if(prev != NULL)
        s->compiler = prev->compiler;
    s->localvars = NULL;
    s->fields = NULL;
    s->staticvars = NULL;
    s->parameters = NULL;
    s->classes = NULL;
    s->subroutines = NULL;
    return s;
}


VAR* getvarinvars(VAR* vars, const char* name) {
    while(vars != NULL) {
        if(!strcmp(vars->name, name))
            return vars;
        vars = vars->next;
    }
    return NULL;
}

VAR* getvar(SCOPE* s, const char* name) {
    VAR* var = getvarinvars(s->localvars, name);
    if(var != NULL)
        return var;
    var = getvarinvars(s->parameters, name);
    if(var != NULL)
        return var;
    var = getvarinvars(s->fields, name);
    if(var != NULL)
        return var;
    var = getvarinvars(s->staticvars, name);
    if(var != NULL)
        return var;
    if(s->previous != NULL)
        return getvar(s->previous, name);
    return NULL;
}

VAR* getvarmustexist(SCOPE* s, DEBUGINFO* d, const char* name) {
    VAR* v = getvar(s, name);
    if(v == NULL)
        notdeclared(name, d);
    return v;
}

CLASS* getclass(SCOPE* s, const char* name) {
    CLASS* curr = s->classes;
    while(curr != NULL) {
        if(!strcmp(curr->name, name))
            return curr;
        curr = curr->next;
    }
    if(s->previous != NULL)
        return getclass(s->previous, name);
    return NULL;
}

SUBROUTDEC* getsubroutdecfromlist(SUBROUTDEC* start, char* name) {
    while(start != NULL) {
        if(!strcmp(start->name, name))
            return start;
        start = start->next;
    }
    return NULL;
}

SUBROUTDEC* getmethod(SCOPE* s, VAR* parent, SUBROUTCALL* call) {
    CLASS* c = getclass(s, parent->type);
    SUBROUTDEC* d = getsubroutdecfromlist(c->subroutdecs, call->name);
    if(d == NULL)
        return NULL;
    if(d->subroutclass != method) {
        eprintf("Calling a function/constructor as if it were a method; file '%s', line %i\n", call->debug->file, call->debug->definedat);
        exit(1);
    }
    return d;
}

SUBROUTDEC* getfunction(SCOPE* s, SUBROUTCALL* call) {
    CLASS* c = getclass(s, call->parentname);
    if(c == NULL)
        notdeclared(call->parentname, call->debug);
    SUBROUTDEC* d = getsubroutdecfromlist(c->subroutdecs, call->name);
    if(d == NULL)
        return NULL;
    if(d->subroutclass == method) {
        eprintf("Calling a method as if it were a function; file '%s', line %i\n", call->debug->file, call->debug->definedat);
        exit(1);
    }
    return d;
}

SUBROUTDEC* getsubroutdecwithparent(SCOPE* s, SUBROUTCALL* call, VAR** varret) {
    VAR* parent = getvar(s, call->parentname);
    if(parent != NULL) {
        if(parent->primitive) {
            eprintf("Primitive type does not have subroutines; file '%s', line %i\n", call->debug->file, call->debug->definedat);
            exit(1);
        }
        *varret = parent;
        return getmethod(s, parent, call);
    }
    else
        return getfunction(s, call);
}

SUBROUTDEC* getsubroutdecwithoutparent(SCOPE* s, SUBROUTCALL* call) {
    SUBROUTDEC* d = getsubroutdecfromlist(s->currclass->subroutdecs, call->name);
    return d;
}

SUBROUTDEC* getsubroutdecfromcall(SCOPE* s, SUBROUTCALL* call, VAR** varret) {
    SUBROUTDEC* d;
    *varret = NULL;
    if(call->parentname != NULL)
        d = getsubroutdecwithparent(s, call, varret);
    else
        d = getsubroutdecwithoutparent(s, call);
    if(d == NULL)
        notdeclared(call->name, call->debug);
    return d;
}

SUBROUTDEC* getsubroutdec(SCOPE* s, const char* name) {
    SUBROUTDEC* curr = s->subroutines;
    while(curr != NULL) {
        if(!strcmp(curr->name, name))
            return curr;
        curr = curr->next;
    }
    if(s->previous != NULL)
        return getsubroutdec(s->previous, name);
    return NULL;
}


VAR* mkvar(char* type, char* name, bool primitive, DEBUGINFO* debug, MEMSEGMENT seg, int i) {
    VAR* v = (VAR*)malloc(sizeof(VAR));
    v->name = name;
    v->type = type;
    v->debug = debug;
    v->memsegment = memsegnames[seg];
    v->primitive = primitive;
    v->index = i;
    return v;
}

void addvar(SCOPE* s, VAR** dest, VAR* v) {
    ensurenoduplicate(s, v->debug, v->name);

    if(!v->primitive) {
        CLASS* type = getclass(s, v->type);
        if(type == NULL)
            notdeclared(v->type, v->debug);
    }

    v->next = *dest;
    *dest = v;
}

void addlocalvar(SCOPE* s, VARDEC* v, int* i) {
    STRINGLIST* currname = v->names;
    while(currname != NULL) {
        addvar(s, &(s->localvars), mkvar(v->type, currname->content, v->primitive, v->debug, local, *i));
        currname = currname->next;
        (*i)++;
    }
}

void addstaticvar(SCOPE* s, CLASSVARDEC* v) {
    STRINGLIST* currname = v->base->names;
    pthread_mutex_lock(&(s->compiler->staticmutex));
    static int i = 0;
    while(currname != NULL) {
        addvar(s, &(s->staticvars), mkvar(v->base->type, currname->content, v->base->primitive, v->base->debug, staticseg, i));
        currname = currname->next;
        i++;
    }
    pthread_mutex_unlock(&(s->compiler->staticmutex));
}

void addfield(SCOPE* s, CLASSVARDEC* v, int* i) {
    STRINGLIST* currname = v->base->names;
    while(currname != NULL) {
        addvar(s, &(s->fields), mkvar(v->base->type, currname->content, v->base->primitive, v->base->debug, fieldseg, *i));
        currname = currname->next;
        (*i)++;
    }
}

void addclassvardec(SCOPE* s, CLASSVARDEC* v, int* i) {
    if(v->type == stat)
        addstaticvar(s, v);
    else {
        addfield(s, v, i);
    }
}

void addparameter(SCOPE* s, PARAMETER* p, int* i) {
    addvar(s, &(s->parameters), mkvar(p->type, p->name, p->primitive, p->debug, arg, *i));
    (*i)++;
}


void addclassvardecs(SCOPE* s, CLASSVARDEC* classvardecs) {
    int i = 0;
    while(classvardecs != NULL) {
        addclassvardec(s, classvardecs, &i);
        classvardecs = classvardecs->next;
    }
}

void addlocalvars(SCOPE* s, VARDEC* localvars) {
    int i = 0;
    while(localvars != NULL) {
        addlocalvar(s, localvars, &i);
        localvars = localvars->next;
    }
}

void addparameters(SCOPE* s, bool isformethod, PARAMETER* params) {
    int i = isformethod ? 1 : 0;
    while(params != NULL) {
        addparameter(s, params, &i);
        params = params->next;
    }
}

void freevars(VAR* v) {
    if(v != NULL) {
        VAR* next = v->next;
        free(v);
        freevars(next);
    }
}

void freescope(SCOPE* s) {
    freevars(s->fields);
    freevars(s->staticvars);
    freevars(s->localvars);
    freevars(s->parameters);
    free(s);
};
