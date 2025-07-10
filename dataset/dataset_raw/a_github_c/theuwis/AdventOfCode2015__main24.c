#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int properties[4][5];
int line_count = 0, property_count = 0;

int main(){
   FILE * fp_data;
   fp_data = fopen("data", "r");

   char * data_read = NULL;
   size_t len = 0;
   ssize_t read;

   
   while((read = getline(&data_read, &len, fp_data)) != -1){
      for(int char_count = 0; char_count < len; char_count++){
         char c = data_read[char_count];

         if(c == '-'){
            properties[line_count][property_count] = (data_read[char_count + 1] - '0') * -1;
            property_count++;
            char_count++;
         }
         else if(isdigit(c) != 0){
            properties[line_count][property_count] = data_read[char_count] - '0';
            property_count++;
         }
      }

      line_count++;
      property_count = 0;
   }

   
   for(int i = 0; i < 4; i++){
      for(int j = 0; j < 5; j++){
         printf("%d ", properties[i][j]);
      }
      printf("\n");
   }

   
   int properties_data[5];
   int score = 1, max_score = 0;
   for(int a = 0; a <= 100; a++){
      for(int b = 0; b <= 100; b++){
         for(int c = 0; c <= 100; c++){
            int d = 100 - a - b - c;

            for(int i = 0; i < 5; i++){
               properties_data[i] = a * properties[0][i] + b * properties[1][i] + c * properties[2][i] + d * properties[3][i];
               properties_data[i] = MAX(properties_data[i], 0);

               if(i < 4){ 
                  score = score * properties_data[i];
               }
            }

            if((properties_data[4] <= 500) && (score > max_score)){
               max_score = score;
            }
            score = 1;
         }
      }
   }

   printf("max score = %d\n", max_score);
   return 0;
}
