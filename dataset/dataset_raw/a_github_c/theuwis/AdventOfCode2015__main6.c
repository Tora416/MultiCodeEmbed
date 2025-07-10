#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define NR_OF_SUES 500

int main(void){
    
    
    
    int sues[NR_OF_SUES][10];
    int analysis[10] = {3, 7, 2, 3, 0, 0, 5, 3, 2, 1};
    int sue_nr = 0;
    int index = 0, amount = 0;
    bool found_her = true;


    
    for(int i = 0; i < NR_OF_SUES; i++){
        for(int j = 0; j < 10; j++){
            sues[i][j] = 999;
        }
    }

    
    FILE * fp_data;
    fp_data = fopen("data", "r");
    char * data_read = NULL, * token = NULL, * dummy = NULL;
    size_t len = 0;
    ssize_t read;

    while((read = getline(&data_read, &len, fp_data)) != -1){
        char * data_dummy = data_read;

        
        token = strtok(data_dummy, ":");
        data_dummy = strtok(NULL, "");

        
        token = strtok(data_dummy, ",");
        while(token != NULL){
            
            if(strstr(token, "children") != NULL){
                index = 0;
            }
            else if(strstr(token, "cats") != NULL){
                index = 1;
            }
            else if(strstr(token, "samoyeds") != NULL){
                index = 2;
            }           
            else if(strstr(token, "pomeranians") != NULL){
                index = 3;
            }
            else if(strstr(token, "akitas") != NULL){
                index = 4;
            }
            else if(strstr(token, "vizslas") != NULL){
                index = 5;
            }
            else if(strstr(token, "goldfish") != NULL){
                index = 6;
            }
            else if(strstr(token, "trees") != NULL){
                index = 7;
            }
            else if(strstr(token, "cars") != NULL){
                index = 8;
            }
            else if(strstr(token, "perfumes") != NULL){
                index = 9;
            }

            
            dummy = token;
            while (*dummy){
                if(isdigit(*dummy)){
                    amount = (int) strtol(dummy, &dummy, 10);
                }
                else{
                    dummy++;
                }
            }

            
            sues[sue_nr][index] = amount;
            
            
            token = strtok(NULL, ",");
        }

        sue_nr++;
    }

    
    for(int i = 0; i < NR_OF_SUES; i++){
        for(int j = 0; j < 10; j++){
            if((sues[i][j] != 999) && (sues[i][j] != analysis[j])){
                    found_her = false;
            }
        }

        if(found_her){
            printf("answer=%d\n", i + 1);
            break;
        }
        else{
            found_her = true;
        }
    }

    return EXIT_SUCCESS;
}