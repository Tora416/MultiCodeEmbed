#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tokenizer.h"
#include "tokenizer-tables.h"


typedef enum {
    common, charsymbol, space
} CHARTYPE;

typedef struct {
    char* str;
    int size;
    int count;
} STRING;


STRING* mkstring(int size);
void append(STRING* s, char c);
void freestr(STRING* str);


TOKEN* appendtokenraw(TOKEN* curitem, STRING* token, int definedat, TOKENTYPE type);
TOKEN* appendtoken(TOKEN* curitem, STRING* token, char* file, int definedat);
#define mktoken() (TOKEN*)malloc(sizeof(TOKEN))


CHARTYPE getchartype(unsigned char c);
bool iskeyword(STRING* tk);
bool issymbol(STRING* tk);
bool isint(char* str);
bool isintcons(STRING* tk);
bool isidentifier(STRING* tk);
TOKENTYPE gettokentype(STRING* tk, char* file, int definedat);


void skipln(FILE* input);
void skipmultiln(FILE* input, int* lnscount);
bool handlecomment(FILE* input, int* lnscount);
void readstr(FILE* input, STRING* tmp, int definedat);


STRING* mkstring(int size) {
    STRING* str = (STRING*)malloc(sizeof(STRING));
    str->size = sizeof(char) * size; 
    str->str = (char*)malloc(str->size);
    str->count = 0;
    return str;
}

void append(STRING* s, char c) {
    int targsize = sizeof(char) * (s->count + 1);
    if(s->size <= targsize) {
        s->size = targsize * 2;
        s->str = (char*)realloc(s->str, s->size);
    }

    s->str[s->count] = c;
    s->count++;
}

void freestr(STRING* str) {
    free(str->str);
    free(str);
}


TOKEN* appendtokenraw(TOKEN* curitem, STRING* token, int definedat, TOKENTYPE type) {
    curitem->token = (char*)malloc(sizeof(char)*token->count);
    strcpy(curitem->token, token->str);
    curitem->definedat = definedat;
    curitem->type = type;
    TOKEN* nextitem = mktoken();
    curitem->next = nextitem;
    token->count = 0;
    return nextitem;
}

void freetokens(TOKEN* t) {
    free(t->token);
    TOKEN* next = t->next;
    free(t);
    if(next != NULL)
        freetokens(next);
}

TOKEN* appendtoken(TOKEN* curitem, STRING* token, char* file, int definedat) {
    append(token, '\0');
    return appendtokenraw(curitem, token, definedat, gettokentype(token, file, definedat));
}


CHARTYPE getchartype(unsigned char c) {
    if(isspace(c)) return space;
    if(isalnum(c) || c == '_' || c == '"') return common;
    return charsymbol;
}

bool iskeyword(STRING* tk) {
    return existsinarray(&keywords, tk->str);
}

bool issymbol(STRING* tk) {
    if(tk->count != 2)
        return false;
    return existsinarray(&symbols, tk->str);
}

bool isint(char* str) {
    int i = 0;
    while(str[i] != '\0') {
        if(!isdigit(str[i]))
            return false;
        i++;
    }
    return true;
}

bool isintcons(STRING* tk) {
    if(!isint(tk->str))
        return false;
    int val = atoi(tk->str);
    return val <= 65535;
}

bool isidentifier(STRING* tk) {
    if(isdigit(tk->str[0]))
        return false;

    int count = tk->count - 1;
    for(int i = 0; i < count; i++)
        if(!isalnum(tk->str[i]) && tk->str[i] != '_')
            return false;
    return true;
}

TOKENTYPE gettokentype(STRING* tk, char* file, int definedat) {
    if(iskeyword(tk)) return keyword;
    if(issymbol(tk)) return symbol;
    if(isintcons(tk)) return integer;
    if(isidentifier(tk)) return identifier;
    eprintf("Unexpected token '%s'; file '%s', line %i\n", tk->str, file, definedat);
    exit(1);
}


void skipln(FILE* input) {
    unsigned char c;
    while(c = fgetc(input), c != '\0')
        if(c == '\n')
            break;
}

void skipmultiln(FILE* input, int* lnscount) {
    unsigned char c;
    while(c = fgetc(input), c != '\0')
        if(c == '\n')
            (*lnscount)++;
        else if(c == '*')
            if(fgetc(input) == '/')
                break;
}

bool handlecomment(FILE* input, int* lnscount) {
    unsigned char nextc = fgetc(input);
    if(nextc == '/') {
        skipln(input);
        (*lnscount)++;
        return true;
    }
    else if(nextc == '*') {
        unsigned char furtherc = fgetc(input);
        if(furtherc == '*') {
            skipmultiln(input, lnscount);
            return true;
        }
        ungetc(furtherc, input);
    }
    ungetc(nextc, input);
    return false;
}

void readstr(FILE* input, STRING* tmp, int definedat) {
    unsigned char c;
    while(c = fgetc(input), c != '\0') {
        if(c == '\n') {
            eprintf("Unexpected end of line; line %i", definedat);
            exit(1);
        }
        if(c == '"')
            break;
        append(tmp, c);
    }
    append(tmp, '\0');
}

TOKEN* tokenize(char* file) {
    TOKEN* head = mktoken();
    TOKEN* lastitem = head;
    TOKEN* curitem = head;

    STRING* tmptoken = mkstring(200);
    CHARTYPE lasttype = space;
    CHARTYPE curtype;

    int lnscount = 1;
    FILE* input = fopen(file, "r");
    
    unsigned char c;
    while(!feof(input)) {
        c = fgetc(input);
        if(c == '\n')
            lnscount++;
        else if(c == '/' && handlecomment(input, &lnscount)) 
            continue;
        else if(c == '"') {
            if(lasttype != space)
                curitem = appendtoken(curitem, tmptoken, file, lnscount);
            readstr(input, tmptoken, lnscount);
            lastitem = curitem;
            curitem = appendtokenraw(curitem, tmptoken, lnscount, string);
            lasttype = space;
            continue;
        }

        curtype = getchartype(c);

        if(curtype == common) {
            if(lasttype == charsymbol) {
                lastitem = curitem;
                curitem = appendtoken(curitem, tmptoken, file, lnscount);
            }
            append(tmptoken, c);
        } else {
            if(lasttype != space){
                lastitem = curitem;
                curitem = appendtoken(curitem, tmptoken, file, lnscount);
            }
            if(curtype == charsymbol)
                append(tmptoken, c);
        }
        lasttype = curtype;
    }

    if(curitem == head) {
        eprintf("File '%s' is empty\n", file);
        exit(1);
    }

    lastitem->next = NULL;
    free(curitem);
    freestr(tmptoken);
    fclose(input);
    return head;
}
