#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 1000
#define NR_OF_BURSTS 10000000

int grid[GRID_SIZE][GRID_SIZE]; 

int parse_data(void); 
void print_square(void);

int main(void){
    int true_grid_size = parse_data();

    int row = GRID_SIZE/2 - 1 + true_grid_size/2, col = GRID_SIZE/2 - 1 + true_grid_size/2;
    int direction = 0; 
    int nr_infected = 0;

    for(int steps = 0; steps < NR_OF_BURSTS; steps++){
        
        switch(grid[row][col]){
            case 0 : 
                (direction > 0) ? (direction--) : (direction = 3);
                break;
            case 1 : 
                break;
            case 2 : 
                (direction < 3) ? (direction++) : (direction = 0);
                break;
            case 3 : 
                switch(direction){
                    case 0 :
                        direction = 2;
                        break;
                    case 1 :
                        direction = 3;
                        break;
                    case 2 :
                        direction = 0;
                        break;
                    case 3 :
                        direction = 1;
                        break;
                }
                break;
        }

        
        switch(grid[row][col]){
            case 0 : 
                grid[row][col]++;
                break;
            case 1 : 
                grid[row][col]++;
                nr_infected++;
                break;
            case 2 : 
                grid[row][col]++;
                break;
            case 3 : 
                grid[row][col] = 0;
                break;
        }

        
        switch(direction){
            case 0 : 
                row--;
                break;
            case 1 : 
                col++;
                break;
            case 2 : 
                row++;
                break;
            case 3 : 
                col--;
                break;
        }
    }

    printf("answer=%d\n", nr_infected);
    return EXIT_SUCCESS;
}

void print_square(void){
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            switch(grid[i][j]){
                case 0 : 
                    printf(". ");
                    break;
                case 1 : 
                    printf("W ");
                    break;
                case 2 : 
                    printf("# ");
                    break;
                case 3 : 
                    printf("F ");
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int parse_data(void){
    FILE *fp;

    if(!(fp = fopen("data", "r"))){
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }

    int curr_x = GRID_SIZE/2 - 1, curr_y = GRID_SIZE/2 - 1;
    char c;
    while( (c = fgetc(fp)) != EOF ){
        switch(c){
            case '.' :
                grid[curr_y][curr_x] = 0;
                curr_x++;
                break;
            case '#' :
                grid[curr_y][curr_x] = 2;
                curr_x++;
                break;
            case '\n' :
                curr_y++;
                curr_x = GRID_SIZE/2 - 1;
                break;
        }
    }

    
    fclose(fp);

    return (curr_y - GRID_SIZE/2 + 1);
}
