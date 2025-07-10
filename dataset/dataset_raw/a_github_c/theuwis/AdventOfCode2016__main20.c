#include <stdio.h>
#include <string.h>

int main() {
   FILE * fp_data;
   fp_data = fopen("data", "r");

   char c;
   int x = 2, y = 2;

   char answer_key[5][5] = {
      {'0', '0', '1', '0', '0'},
      {'0', '2', '3', '4', '0'},
      {'5', '6', '7', '8', '9'},
      {'0', 'A', 'B', 'C', '0'},
      {'0', '0', 'D', '0', '0'}
   };

   for(int lines = 0; lines < 5; lines++){
      while ((c = getc(fp_data)) != ('\n') && c != EOF) {
         switch(c){
            case 'R' :
               if(y < 4) {
                  if(answer_key[x][y + 1] != '0'){
                     y++;
                  }
               }
               break;
            case 'L' :
               if(y > 0) {
                  if(answer_key[x][y - 1] != '0'){
                     y--;
                  }
               }
               break;

            case 'U' :
               if(x > 0) {
                  if(answer_key[x - 1][y] != '0'){
                     x--;
                  }
               }
               break;
            case 'D' :
               if(x < 4) {
                  if(answer_key[x + 1][y] != '0'){
                     x++;
                  }
               }
               break;
         }
      }

      printf("%c", answer_key[x][y]);
   }
   return 0;
}
