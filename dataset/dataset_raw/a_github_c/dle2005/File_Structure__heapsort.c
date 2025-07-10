#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

int heapsize = 0;
void swap(Person *x, Person *y) {
    Person temp = *x;
    *x = *y;
    *y = temp;
}

void insert_heap(Person *person, Person *p) {
    int i = ++heapsize;

    memcpy(&person[i], p, sizeof(Person));

    while((i != 1) && (strcmp(person[i].sn, person[i/2].sn) == -1)) {
        swap(&person[i], &person[i/2]);
        i = i/2;
    }

}

Person delete_heap(Person *person) {
    int parent, child;
    Person item, temp;

    item = person[1];
    temp = person[heapsize--];
    parent = 1;
    child = 2;

    while(child <= heapsize) {
        if((child < heapsize) && (strcmp(person[child].sn, person[child+1].sn) == 1)) {
            child++;
        }
        if(strcmp(temp.sn, person[child].sn) == -1)
            break;
        swap(&person[parent], &person[child]);
        parent = child;
        child *= 2;
    }

    person[parent] = temp;

    return item;
}

void readPage(FILE *fp, char *pagebuf, int pagenum) {
    fseek(fp, PAGE_SIZE * pagenum, SEEK_SET);
    fread(pagebuf, sizeof(char), PAGE_SIZE, fp);
}

void writePage(FILE *fp, const char *pagebuf, int pagenum) {
    fseek(fp, PAGE_SIZE * pagenum, SEEK_SET);
    fwrite(pagebuf, sizeof(char), PAGE_SIZE, fp);
}


void pack(char *recordbuf, const Person *p) {
    sprintf(recordbuf, "%s#%s#%s#%s#%s#%s#", p -> sn, p -> name, p -> age,  p -> addr, p -> phone, p -> email);
    memset(recordbuf + strlen(recordbuf), (char)0xFF, RECORD_SIZE - strlen(recordbuf));
}

void unpack(const char *recordbuf, Person *p) {
    sscanf(recordbuf, "%[^'#']#%[^'#']#%[^'#']#%[^'#']#%[^'#']#%[^'#']#",
    p -> sn, p -> name, p -> age, p -> addr, p -> phone, p -> email);
}

void setHeadPage(char *pagebuf, int pageNum, int recordNum, int deletePageNum, int deleteRecordNum) {
    memset(pagebuf, 0xFF, PAGE_SIZE);
    memcpy(pagebuf, &pageNum, sizeof(int));
    memcpy(pagebuf+4, &recordNum, sizeof(int));
    memcpy(pagebuf+8, &deletePageNum, sizeof(int));
    memcpy(pagebuf+12, &deleteRecordNum, sizeof(int));
}

int main(int argc, char* argv[]) {
    
    FILE *fp1;
    FILE *fp2;

    fp1 = fopen(argv[2], "r+");
    fp2 = fopen(argv[3], "w+");


    char pagebuf[PAGE_SIZE + 1] = { }; 
    memset(pagebuf, (char)0xFF, PAGE_SIZE);
    char *recordbuf = malloc(sizeof(char) * RECORD_SIZE);

    int pageNum;
    int recordNum;
    int recordPerPage = PAGE_SIZE / RECORD_SIZE;
    int recordCount = 0;
    int recordCount_2 = 0;

    readPage(fp1, pagebuf, 0);
    memcpy(&pageNum, pagebuf, sizeof(int));
    memcpy(&recordNum, pagebuf+4, sizeof(int));

    char filebuf[PAGE_SIZE * pageNum + 1];
    Person person[recordPerPage * pageNum];
    Person *p = (Person*)malloc(sizeof(Person));

    for(int i = 1; i < pageNum; i++) {
        readPage(fp1, pagebuf, i);
        for(int j = 0; j < recordPerPage; j++) {
            if(recordCount == recordNum) break;
            recordCount++;
            int index = j * RECORD_SIZE;
            int position = (i-1) * recordPerPage + j;
            memcpy(recordbuf, pagebuf + index, RECORD_SIZE);
            if(recordbuf[0] == '*' || recordbuf[0] == (char)0xFF) continue;
            unpack(recordbuf, p);
            insert_heap(person, p);
            recordCount_2++;
        }
    }

    recordCount = 0;
    readPage(fp1, pagebuf, 0);
    if(recordCount_2 % 2 == 0) pageNum = recordCount_2 / recordPerPage + 1;
    else pageNum = recordCount_2 / recordPerPage + 2;
    setHeadPage(pagebuf, pageNum, recordCount_2, -1, -1);
    writePage(fp2, pagebuf, 0);

    for(int i = 1; i < pageNum; i++) {
        memset(pagebuf, (char)0xFF, PAGE_SIZE);
        for(int j = 0; j < recordPerPage; j++) {
            if(recordCount == recordCount_2) break;
            recordCount++;
            int index = j * RECORD_SIZE;
            int position = (i-1) * recordPerPage + j;
            memset(recordbuf, (char)0xFF, RECORD_SIZE);
            Person temp = delete_heap(person);
            pack(recordbuf, &temp);
            memcpy(pagebuf + index, recordbuf, RECORD_SIZE);
        }
        writePage(fp2, pagebuf, i);
    }
}
    

