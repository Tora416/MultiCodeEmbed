#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void parse_instructions(void);

int regs[4] = {0};
int curr_instr = 0, max_instr = 0;

struct instructions_s {
    enum instructions {cpy_reg, cpy_val, inc, dec, jnz_reg, jnz_val} cmd;
    int x;
    int y;
} instr[1000];


int main(void){
    parse_instructions();
    max_instr = curr_instr;
    curr_instr = 0;

    while(curr_instr < max_instr){
        switch(instr[curr_instr].cmd){
            case 0 :
                regs[instr[curr_instr].y] = regs[instr[curr_instr].x];
                curr_instr++;
                break;

            case 1 :
                regs[instr[curr_instr].y] = instr[curr_instr].x;
                curr_instr++;
                break;

            case 2 :
                regs[instr[curr_instr].x]++;
                curr_instr++;
                break;

            case 3 :
                regs[instr[curr_instr].x]--;
                curr_instr++;
                break;

            case 4 :
                if(regs[instr[curr_instr].x] != 0){
                    curr_instr += instr[curr_instr].y;
                }
                else{
                    curr_instr++;
                }
                break;

            case 5:
                if(instr[curr_instr].x != 0){
                    curr_instr += instr[curr_instr].y;
                }
                else{
                    curr_instr++;
                }
                break;

            default :
                printf("Not a valid instruction!\n");
                exit(EXIT_FAILURE);
        }
    }

    printf("ans=%d\n", regs[0]);
    return EXIT_SUCCESS;
}

void parse_instructions(void){
    FILE *fp;
    char * data_read = NULL;
    size_t len; ssize_t read;

    if(!(fp = fopen("data", "r"))){
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }

    while((read = getline(&data_read, &len, fp)) != -1){
        data_read[strcspn(data_read, "\r\n")] = 0;  

        switch(data_read[0]){
            case 'c' :
                if(isalpha(data_read[4]) != 0){         
                    instr[curr_instr].cmd = cpy_reg;
                    instr[curr_instr].x = data_read[4] - 97;
                    instr[curr_instr].y = data_read[6] - 97;
                }
                else{                                               
                    instr[curr_instr].cmd = cpy_val;
                    instr[curr_instr].x = atoi(data_read + 4);
                    instr[curr_instr].y = data_read[strlen(data_read) - 1] - 97;
                }
                break;

            case 'i' :
                instr[curr_instr].cmd = inc;
                instr[curr_instr].x = data_read[4] - 97;
                break;

            case 'd' :
                instr[curr_instr].cmd = dec;
                instr[curr_instr].x = data_read[4] - 97;
                break;

            case 'j' :
                if(isalpha(data_read[4]) != 0){
                    instr[curr_instr].cmd = jnz_reg;
                    instr[curr_instr].x = data_read[4] - 97;
                    instr[curr_instr].y = atoi(data_read + 6);
                }
                else{
                    instr[curr_instr].cmd = jnz_reg;
                    instr[curr_instr].x = atoi(data_read + 4);
                    instr[curr_instr].y = atoi(data_read + 6);
                }
                break;

            default :
                printf("Not a valid instruction!\n");
                exit(EXIT_FAILURE);
        }

        curr_instr++;
    }

    
    fclose(fp);
    free(data_read);
}