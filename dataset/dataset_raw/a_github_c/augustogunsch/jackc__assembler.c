#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "assembler-tables.h"
#include "assembler.h"
#include "util.h"

void expandsymbols(SYMBOLARRAY* a, int toaddn);
void pushsymbol(SYMBOLARRAY* a, SYMBOL* s);
void freesymbol(SYMBOL* s);
SYMBOL* mksymbol(char* name, int namesize, int val);
int getsymbol(ASSEMBLER* a, char* name);
void skipln(ASSEMBLER* a);
void readrest(ASSEMBLER* a, int trueln);
int isvar(char* var);
void initsymbols(SYMBOLARRAY* s);
void populatevars(ASSEMBLER* a);
SYMBOL* readlabel(ASSEMBLER* a, STRINGLIST* ln, int count);
void replacevar(ASSEMBLER* a, STRINGLIST* ln, int val);
void preprocess(ASSEMBLER* a);
void transa(STRINGLIST* ln);
char* lookctable(TABLE* t, bool cond, char* token, const char* fieldname);
void transb(STRINGLIST* ln);
void assemble(ASSEMBLER* a);
void freeassembler(ASSEMBLER* a);
void strtogarbage(ASSEMBLER* a, char* str);

void strtogarbage(ASSEMBLER* a, char* str) {
    STRINGLIST* newstr = (STRINGLIST*)malloc(sizeof(STRINGLIST));
    newstr->content = str;
    newstr->next = a->garbage;
    a->garbage = newstr;
}

void expandsymbols(SYMBOLARRAY* a, int toaddn) {
    int sum = a->count + toaddn;
    if(sizeof(SYMBOL*) * sum > a->size) {
        a->size = sizeof(SYMBOL*) * sum * 3;
        a->items = (SYMBOL**)realloc(a->items, a->size);
    }
}

void pushsymbol(SYMBOLARRAY* a, SYMBOL* s) {
    expandsymbols(a, 1);
    a->items[a->count] = s;
    a->count++;
}

void freesymbol(SYMBOL* s) {
    free(s->name);
    free(s);
}

void freesymbols(SYMBOLARRAY* a) {
    for(int i = 0; i < a->count; i++)
        freesymbol(a->items[i]);
    free(a->items);
    free(a);
}

SYMBOL* mksymbol(char* name, int namesize, int val) {
    SYMBOL* s = (SYMBOL*)malloc(sizeof(SYMBOL));
    char* heapname = (char*)malloc(namesize);
    strcpy(heapname, name);
    s->name = heapname;
    s->value = val;
    return s;
}

int getsymbol(ASSEMBLER* a, char* name) {
    for(int i = 0; i < a->vars->count; i++)
        if(strcmp(a->vars->items[i]->name, name)  == 0)
            return a->vars->items[i]->value;

    for(int i = 0; i < a->labels->count; i++)
        if(strcmp(a->labels->items[i]->name, name)  == 0)
            return a->labels->items[i]->value;
    
    return -1;
}

int isvar(char* var) {
    int i = 0;
    while(1) {
        if(var[i] == '\0')
            break;
        if(!isdigit(var[i]))
            return 1;
        i++;
    }
    return 0;
}

void initsymbols(SYMBOLARRAY* s) {
    s->size = 150 * sizeof(SYMBOL*);
    s->items = (SYMBOL**)malloc(s->size);
    s->count = 0;
}

ASSEMBLER* mkassembler(STRINGLIST* input) {
    ASSEMBLER* a = (ASSEMBLER*)malloc(sizeof(ASSEMBLER));
    a->labels = (SYMBOLARRAY*)malloc(sizeof(SYMBOLARRAY));
    a->vars = (SYMBOLARRAY*)malloc(sizeof(SYMBOLARRAY));
    a->garbage = NULL;
    a->lns = input;

    initsymbols(a->labels);
    initsymbols(a->vars);

    populatevars(a);
    a->varsramind = BOTTOM_VAR;

    return a;
}

void populatevars(ASSEMBLER* a) {
    const int firstamnt = 5;
    const int ramvamnt = 16; 
    const int specialamt = 2;
    const int sum = firstamnt + ramvamnt + specialamt;

    
    expandsymbols(a->vars, sum);
    
    
    a->vars->count = sum;

    
    char* labels[] = { "SP", "LCL", "ARG", "THIS", "THAT" };
    for(int i = 0; i < firstamnt; i++) {
        a->vars->items[i] = mksymbol(labels[i], strlen(labels[i])+1, i);
    }

    
    const int asciioff = 48;
    char ramvname[4];
    ramvname[0] = 'R';
    ramvname[2] = '\0';
    int tmptarg = (ramvamnt/10)*10;
    for(int i = 0; i < tmptarg; i++) {
        ramvname[1] = (char)(i+asciioff);
        a->vars->items[firstamnt+i] = mksymbol(ramvname, 3, i);
    }
    ramvname[1] = '1';
    ramvname[3] = '\0';
    for(int i = 10; i < ramvamnt; i++) {
        ramvname[2] = (char)((i%10)+asciioff);
        a->vars->items[firstamnt+i] = mksymbol(ramvname, 4, i);
    }

    
    a->vars->items[firstamnt+ramvamnt] = mksymbol("SCREEN", 7, 16384);
    
    a->vars->items[firstamnt+ramvamnt+1] = mksymbol("KBD", 4, 24576);
}

SYMBOL* readlabel(ASSEMBLER* a, STRINGLIST* ln, int count) {
    int i = 1;
    char c;
    while(true) {
        c = ln->content[i];
        if(c == ')') 
            break;
        i++;
    }

    int size = i * sizeof(char);
    char* name = (char*)malloc(size);
    snprintf(name, size, "%s", ln->content+sizeof(char));
    SYMBOL* l = (SYMBOL*)malloc(sizeof(SYMBOL));
    l->name = name;
    l->value = count;
    return l;
}

void replacevar(ASSEMBLER* a, STRINGLIST* ln, int val) {
    int size = sizeof(char)*(countplaces(val) + 2);
    char* newln = (char *)malloc(size);
    snprintf(newln, size, "@%i", val);
    ln->content = newln;
    strtogarbage(a, newln);
}

void handlevarsymbol(ASSEMBLER* a, STRINGLIST* ln) {
    char* afterat = ln->content+sizeof(char);
    if(isvar(afterat)) {
        int val = getsymbol(a, afterat);
        if(val == -1) {
            if(a->varsramind == RAM_LIMIT) {
                eprintf("Variable amount reached RAM limit (%i)\n", RAM_LIMIT);
                exit(1);
            }
            SYMBOL* var = mksymbol(afterat, strlen(afterat)+1, a->varsramind);
            a->varsramind++;
            pushsymbol(a->vars, var);
            val = var->value;
        }
        replacevar(a, ln, val);
    }
}

void handlelabelsymbol(ASSEMBLER* a, STRINGLIST* ln, int count) {
    SYMBOL* l = readlabel(a, ln, count);

    pushsymbol(a->labels, l);
}

void stripvars(ASSEMBLER* a) {
    STRINGLIST* curln = a->lns;
    while(curln != NULL) {
        if(curln->content[0] == '@')
                handlevarsymbol(a, curln);
        curln = curln->next;
    }
}

void striplabels(ASSEMBLER* a) {
    STRINGLIST* curln = a->lns;
    STRINGLIST* lastln;
    int count = 0;
    while(curln != NULL) {
        if(curln->content[0] == '(') {
            handlelabelsymbol(a, curln, count);
            if(count > 0)
                lastln->next = curln->next;
            else
                a->lns = curln->next;
            STRINGLIST* tmp = curln;
            curln = curln->next;
            free(tmp);
        }
        else {
            lastln = curln;
            curln = curln->next;
            count++;
        }
    }
}

void preprocess(ASSEMBLER* a) {
    striplabels(a);
    stripvars(a);
}

void transa(STRINGLIST* ln) {
    int add = atoi(ln->content+sizeof(char));

    char* out = (char*)malloc(sizeof(char) * INST_SIZE);

    int lastbit = 1 << 15;
    for(int i = INST_SIZE-2; i > 0; i--) {
        if(add & (lastbit >> i))
            out[i] = '1';
        else
            out[i] = '0';
    }

    out[INST_SIZE-1] = '\0';
    out[0] = '0';

    ln->content = out;
}

char* lookctable(TABLE* t, bool cond, char* token, const char* fieldname) {
    char* out = (char*)malloc(t->instsize);

    if(!cond) {
        int targsize = t->instsize - 1;
        for(int i = 0; i < targsize; i++)
            out[i] = '0';
        out[t->instsize-1] = '\0';
        return out;
    }
    for(int i = 0; i < t->size; i++)
        if(strcmp(t->table[2*i], token) == 0) {
            strcpy(out, t->table[(2*i)+1]);
            return out;
        }
    return NULL;
}

void transb(STRINGLIST* ln) {
    bool hasjmp = false;
    bool hasdest = false;
    bool hascmp = false;
    int i = 0;
    int tmpi = 0;
    char tmp[C_TOKEN_SIZE], dest[C_TOKEN_SIZE], cmp[C_TOKEN_SIZE], jmp[C_TOKEN_SIZE];

    while(true) {
        if(ln->content[i] == '\0') {
            tmp[tmpi] = '\0';
            if(hasjmp)
                strcpy(jmp, tmp);
            else
                strcpy(cmp, tmp);
            break;
        }

        if(ln->content[i] == '=' && !hasdest && hascmp) {
            hascmp = false;
            hasdest = true;
            tmp[tmpi] = '\0';
            strcpy(dest, tmp);
            tmpi = 0;
            i++;
            continue;
        }
        if(ln->content[i] == ';' && !hasjmp && hascmp) {
            hascmp = false;
            hasjmp = true;
            tmp[tmpi] = '\0';
            strcpy(cmp, tmp);
            tmpi = 0;
            i++;
            continue;
        }
        
        hascmp = 1;
        tmp[tmpi] = ln->content[i];
        tmpi++;
        i++;
    }
    
    char* rawdest = lookctable(&desttable, hasdest, dest, "dest");
    char* rawjmp = lookctable(&jmptable, hasjmp, jmp, "jump");
    char* rawcmp = lookctable(&cmptable, 1, cmp, "comp");

    int sz = sizeof(char) * INST_SIZE;
    char* out = (char*)malloc(sz);
    snprintf(out, sz, "111%s%s%s", rawcmp, rawdest, rawjmp);

    ln->content = out;
    free(rawdest);
    free(rawjmp);
    free(rawcmp);
}

void assemble(ASSEMBLER* a) {
    STRINGLIST* currln = a->lns;
    while(currln != NULL) {
        if(currln->content[0] == '@')
            transa(currln);
        else
            transb(currln);
        currln = currln->next;
    }
}

void freeasmlns(STRINGLIST* lns) {
    if(lns != NULL) {
        free(lns->content);
        STRINGLIST* next = lns->next;
        free(lns);
        freeasmlns(next);
    }
}

void freeassembler(ASSEMBLER* a) {
    freesymbols(a->vars);
    freesymbols(a->labels);
    freeasmlns(a->lns);
    freeasmlns(a->garbage);
    free(a);
}
