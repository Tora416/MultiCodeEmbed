#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int distance(int, int, int);
void move(char *);
void parse_data(void);


int x = 0, y = 0, z = 0;
int max_distance = 0;


int main(void){
    parse_data();
    printf("d=%d, max_d=%d\n", distance(x, y, z), max_distance);

    return EXIT_SUCCESS;
}

int distance(int x, int y, int z){
    return (abs(x) + abs(y) + abs(z))/2;
}

void move(char * command){
    if(strncmp(command, "n\0", 2) == 0){
        y++;
        z--;
    }
    else if(strncmp(command, "ne", 2) == 0){
        x++;
        z--;
    }
    else if(strncmp(command, "se", 2) == 0){
        x++;
        y--;

    }
    else if(strncmp(command, "s\0", 2) == 0){
        y--;
        z++;
    }
    else if(strncmp(command, "sw", 2) == 0){
        x--;
        z++;
    }
    else if(strncmp(command, "nw", 2) == 0){
        x--;
        y++;
    }
}

void parse_data(void){
    FILE *fp;

    
    if(!(fp = fopen("data", "r"))){
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }

    char * data_read = NULL;
    size_t len; ssize_t read;
    while((read = getline(&data_read, &len, fp)) != -1){
        data_read[strcspn(data_read, "\r\n")] = 0;  
        char * pch;
        pch = data_read;

        pch = strtok(pch, ",");
        while(pch != NULL){
            move(pch);
            if(distance(x, y, z) > max_distance) max_distance = distance(x, y, z);
            pch = strtok(NULL, ",");
        }
    }

    free(data_read);
    fclose(fp);
}
