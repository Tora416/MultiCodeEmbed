#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include "util.h"
#include "io.h"

#include <limits.h>
#ifndef PATH_MAX
#ifdef __linux__
#include <linux/limits.h>
#else
#define PATH_MAX 512
#endif
#endif

char* strtail(char* str, int len, int count) {
    int index = len - count;
    if (index <= 0) return str;
    return str + (sizeof(char) * (index));
}

char* strhead(char* str, int count) {
    return str + (sizeof(char) * count);
}

char* trimstr(char* str, int len, int end) {
    int count = len - end;
    char oldchar = str[count];
    str[count] = '\0';
    char* newstr = (char*)malloc(sizeof(char) * (1 + count));
    strcpy(newstr, str);
    str[count] = oldchar;
    return newstr;
}

char* getname(char* f, int len) {
    int startind = 0;
    int endind = len - 1;
    bool readsmt = false;
 
    for(int i = endind; i >= 0; i--) {
        if(f[i] == '/') {
            if(!readsmt) {
                endind = i-1;
                f[i] = '\0';
                continue;
            }
            startind = i+1;
            break;
        }
        readsmt = true;
    }

    int sz = sizeof(char)*(endind - startind + 2);
    char* startstr = strhead(f, startind);
    char* retstr = (char*)malloc(sz);
    snprintf(retstr, sz, "%s", startstr);
    return retstr;
}

char* getfullname(char* fname, int fnamelen, char* dirname, int dirlen) {
    int sz = sizeof(char)*(fnamelen+dirlen+2);
    char* fullname = (char*)malloc(sz);
    sprintf(fullname, "%s/%s", dirname, fname);
    return fullname;
}

bool isdotjack(char* f, int len) {
    const char* ext = ".jack";
    return strcmp(strtail(f, len, strlen(ext)), ext) == 0;
}

bool isdir(char* f, int len) {
    bool readsmt = false;
    for(int i = len-1; i >= 0; i--) {
        if(f[i] == '.') {
            if(readsmt)
                return false;
            else
                continue;
        }
        if(f[i] == '/')
            return 1;
        readsmt = true;
    }
    return true;
}

char* getoutname(char* fullname, int len) {
    char* trimmed = trimstr(fullname, len, 4);
    int sz = sizeof(char) * (len-1);
    char* outname = (char*)malloc(sz);
    sprintf(outname, "%svm", trimmed);
    free(trimmed);
    return outname;
}

FILELIST* addfile(FILELIST* l, char* fullname, char* name) {
    FILELIST* new = (FILELIST*)malloc(sizeof(FILELIST));
    new->name = name;
    new->fullname = fullname;
    new->next = l;
    new->outname = getoutname(fullname, strlen(fullname));
    return new;
}

FILELIST* getfilesfromdir(char* dir) {
    FILELIST* filelist = NULL;
    DIR* d = opendir(dir);

    if(d == NULL) {
        eprintf("Error while opening directory '%s': %s\n", dir, strerror(errno));
        exit(errno);
    }

    int len = strlen(dir);
    struct dirent* thisfile;
    while(thisfile = readdir(d), thisfile != NULL) {
        int thislen = strlen(thisfile->d_name);
        if(isdotjack(thisfile->d_name, thislen)) {
            char* fullname = getfullname(thisfile->d_name, thislen, dir, len);
            char* name = ezheapstr(thisfile->d_name);
            filelist = addfile(filelist, fullname, name);
        }
    }
    
    closedir(d);

    if(filelist == NULL) {
        eprintf("Directory '%s' doesn't have any .jack file\n", dir);
        exit(1);
    }
    return filelist;
}

FILELIST* getsinglefile(char* file) {
    int len = strlen(file);
    if(isdotjack(file, len)){
        char* name = getname(file, len);
        char* fullname = heapstr(file, len);

        FILE* input = fopen(fullname, "r");
        if(input == NULL) {
            eprintf("Error while reading file '%s': %s\n", file, strerror(errno));
            exit(errno);
        }
        fclose(input);

        return addfile(NULL, fullname, name);
    }
    else {
        eprintf("Input file must be named like 'Xxx.vm'\n");
        exit(1);
    }
}

FILELIST* getfiles(char* input) {
    int inplen = strlen(input);
    bool isitdir = isdir(input, inplen);

    if(isitdir)
        return getfilesfromdir(input);
    else
        return getsinglefile(input);
}

void freefilelist(FILELIST* fs) {
    free(fs->name);
    free(fs->fullname);
    free(fs->outname);
    FILELIST* next = fs->next;
    free(fs);
    if(next != NULL)
        freefilelist(next);
}
