#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define NR_ROWS 400000 
#define NR_COLS 100

char input[] = "^^.^..^.....^..^..^^...^^.^....^^^.^.^^....^.^^^...^^^^.^^^^.^..^^^^.^^.^.^.^.^.^^...^^..^^^..^.^^^^";
bool traps[NR_ROWS][NR_COLS] = {false};
bool left, center, right;
int nr_safe = 0;


int main(){
   clock_t start = clock(), diff;

   for(int i = 0; i < strlen(input); i++){
      if(input[i] == '^'){
         traps[0][i] = true;
      }
      else{
         nr_safe++;
      }
   }

   for(int row = 1; row < NR_ROWS; row++){
      for(int col = 0; col < NR_COLS; col++){
         if(col == 0){
            left = false;
            center = traps[row - 1][col];
            right = traps[row - 1][col + 1];
         }
         else if(col == NR_COLS - 1){
            left = traps[row - 1][col - 1];
            center = traps[row - 1][col];
            right = false;
         }
         else{
            left = traps[row - 1][col - 1];
            center = traps[row - 1][col];
            right = traps[row - 1][col + 1];
         }

         if((left && center && !right) || (!left && center && right) ||
               (!left && !center && right) || (left && !center && !right)){
            traps[row][col] = true;
         }
         else{
            traps[row][col] = false;
            nr_safe++;
         }
      }
   }

   diff = clock() - start;
   int msec = diff * 1000 / CLOCKS_PER_SEC;

   printf("answer=%d\n", nr_safe);
   printf("time: %ds %dms", msec/1000, msec%1000);

   return EXIT_SUCCESS;
}
