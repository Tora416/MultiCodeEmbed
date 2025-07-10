#include <stdio.h>
#include <stdlib.h>

int main(void){
    int answer1 = 0, answer2 = 0, curr_level = 1;
    FILE *fp;

    int garbage_flag = 0;

    
    if(!(fp = fopen("data", "r"))){
        fprintf(stderr, "Error opening file\n");
        return EXIT_FAILURE;
    }

    char c;
    while((c = fgetc(fp)) != EOF){
        if(garbage_flag == 0){
            switch(c){
                case '{' :
                    answer1 += curr_level;
                    curr_level++;
                    break;
                case '}' :
                    curr_level--;
                    break;
                case '<' :
                    garbage_flag = 1;
                    break;
                case '!' :
                    fgetc(fp); 
                    break;
            }
        }
        else{
            switch(c){
                case '>' :
                    garbage_flag = 0;
                    break;
                case '!' :
                    fgetc(fp); 
                    break;
                default :
                    answer2++;
            }
        }
    }

    printf("answer1=%d\nanswer2=%d\n", answer1, answer2);

    fclose(fp);
    return EXIT_SUCCESS;
}
