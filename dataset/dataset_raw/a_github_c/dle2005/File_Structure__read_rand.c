#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define SUFFLE_NUM 10000

void GenRecordSequence(int *list, int n);
void swap(int *a, int *b);

int main(int argc, char* argv[]) {

    FILE *fp = fopen(argv[1], "r");

    struct timeval startTime, endTime;
    int diffTime;

    int *read_order_list;
    int num_of_records;
    int i;
    char buffer[101];

    fseek(fp, 0, SEEK_END);
    num_of_records = ftell(fp) / 100;
    read_order_list = malloc(sizeof(int) * num_of_records +1);

    GenRecordSequence(read_order_list, num_of_records);

    gettimeofday(&startTime, NULL);

    for(i=0; i<num_of_records; i++) {
        fseek(fp, read_order_list[i]*100, SEEK_SET);
        fread(buffer, sizeof(char), 100, fp);
        memset(buffer, 0, 100);
    }

    gettimeofday(&endTime, NULL);
    diffTime = (endTime.tv_usec - startTime.tv_usec) * 1000;
    printf("#records: %d timecost: %d us\n", num_of_records, diffTime);

    return 0;
}

void GenRecordSequence(int *list, int n) {

    int i, j, k;

    srand((unsigned int)time(0));

    for(i=0; i<n; i++)
        list[i] = i;

    for(i=0; i<SUFFLE_NUM; i++) {
        j = rand() % n;
        k = rand() % n;
        swap(&list[j], &list[k]);
    }

    return;
}

void swap(int *a, int *b) {
    
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;

    return;
}
