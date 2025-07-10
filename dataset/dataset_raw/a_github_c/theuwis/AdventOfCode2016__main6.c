#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char string[4];
bool in_brackets = false, approved_IP[2] = {false, true};
int ip_counter = 0;

int main(){
   FILE * fp_data;
   fp_data = fopen("data", "r");

   char * data_read = NULL;
   size_t len = 0;
   ssize_t read;

   while((read = getline(&data_read, &len, fp_data)) != -1){
      for(int current_char = 0; current_char < (strlen(data_read) - 5); current_char++){
         for(int i = 0; i < 4; i++){
            string[i] = data_read[current_char + i];
         }
   

         if(strstr(string, "[") != NULL){
            in_brackets = true;
         }
         else if(strstr(string, "]") != NULL){
            in_brackets = false;
         }
         else{
            if((string[0] == string[3]) && (string[1] == string[2]) && (string[0] != string[1])){
               if(in_brackets) approved_IP[1] = false;
               if(!in_brackets) approved_IP[0] = true;
            }
         }
      }
      if(approved_IP[0] && approved_IP[1]){
         ip_counter++;
      }
      approved_IP[0] = false;
      approved_IP[1] = true;
      in_brackets = false;
   }

   printf("answer=%d\n", ip_counter);
   return 0;
}
