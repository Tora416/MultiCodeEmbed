#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char string[4];
bool in_brackets = false;
int ip_counter = 0;

int main(){
   FILE * fp_data;
   fp_data = fopen("data", "r");

   char * data_read = NULL;
   size_t len = 0;
   ssize_t read;

   while((read = getline(&data_read, &len, fp_data)) != -1){
      char ABA[300] = "";
      char BAB[300] = "";

      for(int current_char = 0; current_char < (strlen(data_read) - 4); current_char++){
         for(int i = 0; i < 3; i++){
            string[i] = data_read[current_char + i];
         }
   

         if(strstr(string, "[") != NULL){
            in_brackets = true;
         }
         else if(strstr(string, "]") != NULL){
            in_brackets = false;
         }
         else{
            if((string[0] == string[2]) && (string[0] != string[1])){
               if(in_brackets) strcat(BAB, string);
               else strcat(ABA, string);
            }
         }
      }

      char ABA_temp[4]; char BAB_temp[4];
      int ABA_loop = strlen(ABA) / 3;
      bool not_added = false;

      while(ABA_loop-- > 0){
         memcpy(ABA_temp, ABA + (ABA_loop * 3), 3); ABA_temp[3] = '\0';

         int BAB_loop = strlen(BAB) / 3;
         while(BAB_loop-- > 0){
            memcpy(BAB_temp, BAB + (BAB_loop * 3), 3); BAB_temp[3] = '\0';

            if((ABA_temp[0] == BAB_temp[1]) && (ABA_temp[1] == BAB_temp[0])){
               if(!not_added){
                  ip_counter++;
                  not_added = true;
               }
            }
         }
      }
      in_brackets = false;
   }

   printf("answer=%d\n", ip_counter);
   return 0;
}
