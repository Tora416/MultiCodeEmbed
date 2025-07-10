#include <stdio.h>
#include <string.h>

int main() {
   FILE * fp_data;
   fp_data = fopen("data", "r");

   char c;
   int x = 1, y = 1;

   int answer_key[3][3] = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
   };

   for(int lines = 0; lines < 5; lines++){
      while ((c = getc(fp_data)) != ('\n') && c != EOF) {
         switch(c){
            case 'R' :
               if(y < 2) {
                  y++;
               }
               break;
            case 'L' :
               if(y > 0) {
                  y--;
               }
               break;
            case 'U' :
               if(x > 0) {
                  x--;
               }
               break;
            case 'D' :
               if(x < 2) {
                  x++;
               }
               break;
         }
      }
      printf("%d", answer_key[x][y]);
   }

   return 0;
}
