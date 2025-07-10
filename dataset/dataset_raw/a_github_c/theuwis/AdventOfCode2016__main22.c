#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char line_nodash[100];
long char_counter = 0;
char c = 'a';
int line_counter = 0, sector_ID = 0, processed = 0;

int main() {
   FILE * fp_data;
   fp_data = fopen("data", "r");

   char * data_read = NULL;
   size_t size = 0;

   fseek(fp_data, 0, SEEK_END);
   size = ftell(fp_data);
   rewind(fp_data);
   data_read = malloc((size + 1) * sizeof(* data_read));

   fread(data_read, size, 1, fp_data);
   data_read[size] = '\0';


   while(1){
      c = data_read[char_counter];
      if(c == '\0'){
         printf("WORD NOT FOUND (processed=%d)\n", processed);
         return 0;
      }

      while(c != '\n'){
         if(c == '['){
            char_counter++; size = 0;
         }

         else{
            if(isalpha(c)){ 
               line_nodash[line_counter] = c;
               line_counter++;
            }
            if(isdigit(c)){
               sector_ID = sector_ID * 10 + (c - '0');
            }
            char_counter++;
         }

         c = data_read[char_counter];
      }

      line_nodash[line_counter] = '\0';
      line_counter = 0;
      char_counter++;

      #ifdef DEBUG
         printf("line=%s\tbrackets=%s\tID=%d\n", line_nodash, line_brackets, sector_ID);
      #endif

      int key = sector_ID;

      if(key > 26){
         key %= 26;
      }
      for(int j = 0; j < strlen(line_nodash); j++) {
         int char_val = line_nodash[j] - 'a';

         if( (char_val + key) > 25){
            int keytemp = key - (26 - char_val);
            line_nodash[j] = keytemp + 'a';
         }
         else {
            line_nodash[j] += key;
         }

      }

      printf("output=%s\n", line_nodash);
      if(strstr(line_nodash, "north") != NULL){
         printf("ID=%d (processed=%d)\n", sector_ID, processed);
         return 0;
      }

      sector_ID = 0;
      processed++;
   }

   return 0;
}
