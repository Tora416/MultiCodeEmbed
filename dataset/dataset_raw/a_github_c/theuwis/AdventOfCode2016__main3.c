#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char line_nodash[100];
char line_brackets[20];
long char_counter = 0, total_sector = 0;
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
         printf("TOTAL=%ld (processed=%d)\n", total_sector, processed);
         return 0;
      }

      while(c != '\n'){
         if(c == '['){
            char_counter++; size = 0;

            while(data_read[char_counter] != ']'){
               line_brackets[size] = data_read[char_counter];
               char_counter++; size++;
            }
            line_brackets[size] = '\0';
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

      int count[26] = {0}, parse_count = 0;

      while(line_nodash[parse_count] != '\0'){
         count[line_nodash[parse_count] - 'a']++;
         parse_count++;
      }

      #ifdef DEBUG
         for(int j = 0; j < 26; j++){
            if(count[j] != 0){

                  printf("%c => %d\n", j + 'a', count[j]);

            }
         }
      #endif

      parse_count = 0;
      int ok_counter = 0;
      bool is_ok = true;
      while(line_brackets[parse_count] != '\0'){
            if( (count[line_brackets[parse_count] - 'a']) < (count[line_brackets[parse_count + 1] - 'a']) ){ 
               is_ok = false;
               #ifdef DEBUG
                  printf("smaller\n");
               #endif
               break;
            }

            if( (count[line_brackets[parse_count] - 'a']) > (count[line_brackets[parse_count + 1] - 'a']) ){
               #ifdef DEBUG
                  printf("bigger\n");
               #endif
               ok_counter++;
            }

            if( (count[line_brackets[parse_count] - 'a']) == (count[line_brackets[parse_count + 1] - 'a']) ){
               if( (line_brackets[parse_count]) < (line_brackets[parse_count + 1]) ){ 
                  #ifdef DEBUG
                     printf("same ok\n");
                  #endif
                  ok_counter++;
               }
               else{
                  is_ok = false;
                  #ifdef DEBUG
                     printf("same not ok\n");
                  #endif
                  break;
               }
            }

         #ifdef DEBUG
            printf("%c is %d\n", line_brackets[parse_count], count[line_brackets[parse_count] - 'a']);
         #endif
         parse_count++;
      }

      if(is_ok){
         #ifdef DEBUG
            printf("string is ok\n");
         #endif
         total_sector += sector_ID;
      }
      #ifdef DEBUG
         else{
            printf("string is not ok\n");
         }
      #endif

      sector_ID = 0;
      processed++;
   }
   printf("TOTAL=%ld (processed=%d)\n", total_sector, processed);
   return 0;
}
