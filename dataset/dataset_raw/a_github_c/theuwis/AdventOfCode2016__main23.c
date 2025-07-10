#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "md5.c"

int main(){
   char * msg = "abbhdwsy", * dummy = NULL;
   char code[9] = "--------\0"; int code_counter = 0;
   bool done[8] = {false};

   long index = 0;
   size_t len = 0;
   uint8_t * md5_result;

   clock_t start = clock(), diff;
   while(1){
      asprintf(&dummy,"%s%ld" , msg, index);
      len = strlen(dummy);
      md5(dummy, len);

      md5_result = (uint8_t *) &h0;

      char str[10];
      sprintf(str, "%2.2X%2.2X%2.2X%2.2X", md5_result[0], md5_result[1], md5_result[2], md5_result[3]);

      if(strncmp(str, "00000", 5) == 0){
         printf("hash found - input=%s - MD5=%s - index=%ld\n", dummy, str, index);
         int index = str[5] - '0';

         if(code_counter >= 8){
            printf("done! code=%s\n", code);
            diff = clock() - start;
            int msec = diff * 1000 / CLOCKS_PER_SEC;
            printf("time: %ds %dms", msec/1000, msec%1000);
            break;
         }
         else{
            if( (index < 8) && (done[index] == false) ){
               code[index] = str[6];
               done[index] = true;
               code_counter++;
               printf("current code = %s\n\n", code);
            }
         }
      }
      index++;
   }
   return 0;
}
