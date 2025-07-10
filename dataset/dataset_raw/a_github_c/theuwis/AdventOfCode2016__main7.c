
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ROWS 6
#define COLS 50

bool screen[ROWS][COLS] = {false};
int x = 0, y = 0, char_index;
char * loc;

int main(){
   FILE * fp_data;
   fp_data = fopen("data", "r");

   char * data_read = NULL;
   size_t len = 0;
   ssize_t read;

   while((read = getline(&data_read, &len, fp_data)) != -1){
      if(strstr(data_read, "rect") != NULL){
         loc = strstr(data_read, "rect ");
         char_index = (int)(loc - data_read) + 5;
         while(isdigit(data_read[char_index]) != 0){
            x = x * 10 + (data_read[char_index] - '0');
            char_index++;
         }
         char_index++;
         while(isdigit(data_read[char_index]) != 0){
            y = y * 10 + (data_read[char_index] - '0');
            char_index++;
         }

         for(int row = 0; row < y; row++){
            for(int col = 0; col < x; col++){
               screen[row][col] = true;
            }
         }
      }

      else{
         loc = strstr(data_read, "=");
         char_index = (int)(loc - data_read);
         while(isdigit(data_read[char_index + 1]) != 0){
            x = x * 10 + data_read[char_index + 1] - '0';
            char_index++;
         }

         loc = strstr(data_read, "by ");
         char_index = (int)(loc - data_read);
         while(isdigit(data_read[char_index + 3]) != 0){
            y = y * 10 + data_read[char_index + 3] - '0';
            char_index++;
         }

         if(strstr(data_read, "column") != NULL){
            for(int pixels_down = 0; pixels_down < y; pixels_down++){
               bool temp = screen[ROWS - 1][x];
               for(int i = (ROWS - 1); i > 0; i--){
                  screen[i][x] = screen[i - 1][x];
               }
               screen[0][x] = temp;
            }
         }
         else if(strstr(data_read, "row") != NULL){
            x ^= y; 
            y ^= x;
            x ^= y;

            for(int pixels_right = 0; pixels_right < x; pixels_right++){
               bool temp = screen[y][COLS - 1];
               for(int i = (COLS - 1); i > 0; i--){
                  screen[y][i] = screen[y][i - 1];
               }
               screen[y][0] = temp;
            }
         }
      }
      x = 0; y = 0;
   }

   int lit_pixels = 0;
   for(int row = 0; row < ROWS; row++){
      for(int col = 0; col < COLS; col++){
         if(screen[row][col] == true){
            printf("#");
            lit_pixels++;
         }
         else{
            printf(".");
         }
      }
      printf("\n");
   }

   printf("\nanswer=%d\n", lit_pixels);
   return 0;
}
