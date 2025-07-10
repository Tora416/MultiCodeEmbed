#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "flash.h"
#include "fdevicedriver.c"
#include <unistd.h>
#include <sys/types.h>

FILE *flashfp;

void optionC(char *fileName, int blocks);
int optionW(char *fileName, int ppn, char *sectordata, char *sparedata);
int optionR(char* fileName, int ppn);
int emptyPage(int ppn);
int emptyBlock();
void copyBlock(int from, int to, int except);
void copyPage(int from, int to);
void insertPage(int ppn, char *sectordata, char *sparedata);

char pagebuf[PAGE_SIZE];

int main(int argc, char *argv[])
{   
    char option = argv[1][0];
    switch(option) {
        case 'c' : optionC(argv[2], atoi(argv[3]));
                   break;
        case 'w' : optionW(argv[2], atoi(argv[3]), argv[4], argv[5]);
                   break;
        case 'r' : optionR(argv[2], atoi(argv[3]));
                   break;
        case 'e' : flashfp = fopen(argv[2], "r+t");
                   dd_erase(atoi(argv[3]));
                   break;
    }
    return 0;
}

void optionC(char *fileName, int blocks) {
    int fileMemory = blocks * BLOCK_SIZE;
    flashfp = fopen(fileName, "w+t");
    truncate(fileName, fileMemory);
    for(int i = 0; i < blocks; i++)
        dd_erase(i);
}

int optionW(char *fileName, int ppn, char *sectordata, char *sparedata) {
    char ch;
    flashfp = fopen(fileName, "r+t");
    int ppnBlock = ppn / 4;
    fseek(flashfp, PAGE_SIZE * ppn, SEEK_SET);
    if(ch = fgetc(flashfp) != 0xFF) {
        int emptyBlockIndex = emptyBlock();
        copyBlock(ppnBlock, emptyBlockIndex, ppn);
        dd_erase(ppnBlock);
        copyBlock(emptyBlockIndex, ppnBlock, ppn);
        dd_erase(emptyBlockIndex);
        insertPage(ppn, sectordata, sparedata);
    }
    else insertPage(ppn, sectordata, sparedata); 
}

int optionR(char* fileName, int ppn) {
    flashfp = fopen(fileName, "r+t");
    dd_read(ppn, pagebuf);
    for(int i = 0; i < SECTOR_SIZE && pagebuf[i] != (char)0xFF; i++)
        printf("%c", pagebuf[i]);
    printf(" ");
    for(int i = SECTOR_SIZE; i < PAGE_SIZE && pagebuf[i] != (char)0xFF; i++)
        printf("%c", pagebuf[i]);
}

int emptyBlock() {
    fseek(flashfp, 0, SEEK_END);
    int blocks = ftell(flashfp) / BLOCK_SIZE;
    int emptyBlock;
    char ch;
    for(int i = 0; i < blocks; i++) {
        int emptyPageNum = 0;
        for(int j = 0; j < PAGE_NUM; j++) {
            fseek(flashfp, (BLOCK_SIZE * i) + (PAGE_SIZE * j), SEEK_SET);
            if((ch = fgetc(flashfp)) != 0xFF) emptyPageNum++;
            if(emptyPageNum == PAGE_NUM) emptyBlock = i;
        }
    }
    return emptyBlock;
}

void copyBlock(int from, int to, int except) {
    for(int i = 0; i < PAGE_NUM; i++) {
        int fromPpn = from * PAGE_NUM + i;
        int toPpn = to * PAGE_NUM + i;
        if(fromPpn == except) i++;
        copyPage(fromPpn, toPpn);
    }
}      

void copyPage(int from, int to) {
    dd_read(from, pagebuf);
    dd_write(to, pagebuf);
}

void insertPage(int ppn, char *sectordata, char *sparedata) {
    memset(pagebuf, (char)0xFF, PAGE_SIZE);
    memcpy(pagebuf, sectordata, strlen(sectordata));
    memcpy(pagebuf + SECTOR_SIZE, sparedata, strlen(sparedata));
    dd_write(ppn, pagebuf);
}
