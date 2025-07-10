#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int data_array[8][26] = {0};
char output[8];

int main(){
   FILE * fp_data;
   fp_data = fopen("data", "r");

   char * data_read = NULL;
   size_t len = 0;
   ssize_t read;

   while((read = getline(&data_read, &len, fp_data)) != -1){
      for(int i = 0; i < 8; i++){
         data_array[i][(int)(data_read[i] - 'a')]++;
      }
   }

   int min = 100;
   for(int i = 0; i < 8; i++){
      for(int j = 0; j < 26; j++){
         if((data_array[i][j] < min) && (data_array[i][j] != 0)){
            output[i] = j + 'a';
            min = data_array[i][j];
         }

      }
      min = 100;
   }

   printf("answer=%s\n", output);
   return 0;
}
