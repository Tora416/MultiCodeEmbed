#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE_GRID 100
#define NR_OF_TIMES 100


bool lights[SIZE_GRID + 2][SIZE_GRID + 2] = {false};
bool dummy[SIZE_GRID + 2][SIZE_GRID + 2] = {false};

int main(void){
    
    FILE * fp_data;
    fp_data = fopen("data", "r");
    char * data_read = NULL;
    size_t len = 0;
    ssize_t read;
    int x_coord = 1, y_coord = 1;
    int nr_neighbours = 0, nr_lights_on = 0;

    
    while((read = getline(&data_read, &len, fp_data)) != -1){
        while(y_coord < SIZE_GRID + 1){
            if(data_read[y_coord - 1] == '#'){
                lights[x_coord][y_coord] = true;
            }
            else{
                lights[x_coord][y_coord] = false;
            }
            y_coord++;
        }
        y_coord = 1;
        x_coord++;
    }

    
    lights[1][1] = true;
    lights[1][SIZE_GRID] = true;
    lights[SIZE_GRID][1] = true;
    lights[SIZE_GRID][SIZE_GRID] = true;

    
    for(int times = 0; times < NR_OF_TIMES; times++){
        
        for(int i = 1; i < SIZE_GRID + 1; i++){
            for(int j = 1; j < SIZE_GRID + 1; j++){
                dummy[i][j] = lights[i][j];
            }
        }

        for(int i = 1; i < SIZE_GRID + 1; i++){
            for(int j = 1; j < SIZE_GRID + 1; j++){
                
                for(int k = -1; k < 2; k++){
                    for(int l = -1; l < 2; l++){
                        if(dummy[i + k][j + l]){
                            nr_neighbours++;
                        }
                    }
                }
                
                if(dummy[i][j]) nr_neighbours--;

                if(dummy[i][j]){
                    
                    if((nr_neighbours != 2) && (nr_neighbours != 3)){
                        lights[i][j] = false;
                    }
                }
                else{
                    
                    if(nr_neighbours == 3){
                        lights[i][j] = true;
                    }
                }

                
                lights[1][1] = true;
                lights[1][SIZE_GRID] = true;
                lights[SIZE_GRID][1] = true;
                lights[SIZE_GRID][SIZE_GRID] = true;

                nr_neighbours = 0;
            }
        }
    }

    for(int i = 1; i < SIZE_GRID + 1; i++){
        for(int j = 1; j < SIZE_GRID + 1; j++){
            if(lights[i][j]) nr_lights_on++;
        }
    }

    printf("answer=%d\n", nr_lights_on);

    return EXIT_SUCCESS;
}