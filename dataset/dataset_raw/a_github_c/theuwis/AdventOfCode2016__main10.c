#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NR_DISCS 6

int input[NR_DISCS][3] = {
   { 5, 0,  2}, 
   {13, 0,  7},
   {17, 0, 10},
   { 3, 0,  2},
   {19, 0,  9},
   { 7, 0,  0}
};

bool not_zero = false;
int time = 1;

int main(){
   
   for(int i = 0; i < NR_DISCS; i++){
      for(int j = 0; j < i + 1; j++){
         if(input[i][0] - 1 > input[i][2]){
            input[i][2]++;
         }
         else{
            input[i][2] = 0;
         }
      }
   }

   
   while(1){
      for(int i = 0; i < NR_DISCS; i++){
         if(input[i][0] - 1 > input[i][2]){
            input[i][2]++;
            not_zero = true;
         }
         else{
            input[i][2] = 0;
         }
      }

      
      if(!not_zero){
         printf("answer=%d\n", time);
         break;
      }
      else{
         not_zero = false;
      }
      time++;
   }

   return EXIT_SUCCESS;
}
