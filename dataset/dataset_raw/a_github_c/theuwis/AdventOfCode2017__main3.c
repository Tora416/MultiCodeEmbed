#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long answer = 0;
char * data_read = NULL;
size_t len; ssize_t read;
FILE *fp;

char *pass[50];

int main(void){
    int i = 0, j = 0;
    int not_valid_flag = 0;

    
    if(!(fp = fopen("data", "r"))){
        fprintf(stderr, "Error opening file\n");
        return EXIT_FAILURE;
    }

    
    while((read = getline(&data_read, &len, fp)) != -1){
        data_read[strcspn(data_read, "\r\n")] = 0;  

        pass[i] = strtok(data_read, " ");
        while(data_read != NULL){
            data_read = strtok(NULL, " ");
            i++;
            pass[i] = data_read;
        }

        i = 0;
        while(pass[i] != NULL){
            j = i + 1;
            
            while(pass[j] != NULL){
                if(strcmp(pass[i], pass[j]) == 0){
                    not_valid_flag = 1;
                }
                j++;
            }
            i++;
        }

        if(not_valid_flag == 0){
            answer++;
        }

        not_valid_flag = 0;
        i = 0;
    }


    printf("answer=%ld\n", answer);

    free(data_read);
    fclose(fp);
    return EXIT_SUCCESS;
}