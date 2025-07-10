

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytar.h"

extern char *use;



int copynFile(FILE * origin, FILE * destination, int nBytes){
    
    
    char* c = (char*) malloc(nBytes * sizeof(char));

    
    int n = fread(c, sizeof(char), nBytes, origin);

    
    fwrite(c, sizeof(char), n, destination);

    
    free(c);

    
    return n;
}



char* loadstr(FILE * file){

    
    int counter = 0;

    
    while(getc(file) != '\0')
        counter++;

    
    fseek(file, -(counter + 1), SEEK_CUR);

    
    char* c = (char*) malloc(counter * sizeof(char));

    
    fread(c, sizeof(char), counter + 1, file);

    
    return c;
}



stHeaderEntry* readHeader(FILE * tarFile, int *nFiles){

    
    fread(nFiles, sizeof(int), 1, tarFile);

    
    stHeaderEntry* pair = (stHeaderEntry*) malloc(sizeof(stHeaderEntry) * (*nFiles));

    
    for(int i = 0; i < *nFiles; i++){
        
        pair[i].name = loadstr(tarFile);
        
        fread(&(pair[i].size), sizeof(int), 1, tarFile);
    }

    
    return pair;
}



int createTar(int nFiles, char *fileNames[], char tarName[]){

    
    FILE * f = fopen(tarName, "w");

    
    int headerSize = sizeof(int);
    for(int i = 0; i < nFiles; i++)
        headerSize += strlen(fileNames[i]) + 1 + sizeof(int);

    
    fseek(f, headerSize, SEEK_SET);

    
    int* fileSizes = (int*) malloc(nFiles * sizeof(int));
    
    
    for(int i = 0; i < nFiles; i++){
        
        FILE * a = fopen(fileNames[i], "r");
        
        int t = copynFile(a, f, 100);
        
        fileSizes[i] = 0;
        while(t != 0){
            
            fileSizes[i] += t;
            
            t = copynFile(a, f, 100);
        }
        
        fclose(a);
    }
    
    
    fseek(f, 0, SEEK_SET);

    
    fwrite(&nFiles, sizeof(int), 1, f);

    
    for(int i = 0; i < nFiles; i++){
        
        fwrite(fileNames[i], sizeof(char), strlen(fileNames[i]) + 1, f);
        
        fwrite(&fileSizes[i], sizeof(int), 1, f);
    }

    
    fclose(f);
    
    free(fileSizes);

    
    return EXIT_SUCCESS;
}



int extractTar(char tarName[]){

    
    FILE * f = fopen(tarName, "r");

    
    int nFiles;
    stHeaderEntry* s = readHeader(f, &nFiles);

    
    for(int i = 0; i < nFiles; i++){
        
        FILE * a = fopen(s[i].name, "w");
        
        copynFile(f, a, s[i].size);
        
        fclose(a);
    }

    
    fclose(f);
    
    return EXIT_SUCCESS;
}
