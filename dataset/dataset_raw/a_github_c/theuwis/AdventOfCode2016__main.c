#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[] = "R4,R1,L2,R1,L1,L1,R1,L5,R1,R5,L2,R3,L3,L4,R4,R4,R3,L5,L1,R5,R3,L4,R1,R5,L1,R3,L2,R3,R1,L4,L1,R1,L1,L5,R1,L2,R2,L3,L5,R1,R5,L1,R188,L3,R2,R52,R5,L3,R79,L1,R5,R186,R2,R1,L3,L5,L2,R2,R4,R5,R5,L5,L4,R5,R3,L4,R4,L4,L4,R5,L4,L3,L1,L4,R1,R2,L5,R3,L4,R3,L3,L5,R1,R1,L3,R2,R1,R2,R2,L4,R5,R1,R3,R2,L2,L2,L1,R2,L1,L3,R5,R1,R4,R5,R2,R2,R4,R4,R1,L3,R4,L2,R2,R1,R3,L5,R5,R2,R5,L1,R2,R4,L1,R5,L3,L3,R1,L4,R2,L2,R1,L1,R4,R3,L2,L3,R3,L2,R1,L4,R5,L1,R5,L2,L1,L5,L2,L5,L2,L4,L2,R3";

enum e_coord {NORTH, EAST, SOUTH, WEST};

enum e_coord coord_next = NORTH;
enum e_coord coord_prev = NORTH;

int current_char = 0, current_step = 0, dummy_step = 0;
char c;
signed int x = 0, y = 0;


int main() {
   while (str[current_char] != '\0') {
      c = str[current_char];

      if(c != ',') {
         if(c == 'R'){
            (coord_prev == WEST) ? coord_next = NORTH : coord_next++;
         }

         else if(c == 'L') {
            (coord_prev == NORTH) ? coord_next = WEST : coord_next--;
         }

         else {
            current_step = c - '0';
            dummy_step = dummy_step * 10 + current_step;

            if( (str[current_char + 1] == ',') || (str[current_char + 1] == '\0') ) {
               if(dummy_step != 0){
                  current_step = dummy_step;
                  dummy_step = 0;
               }

               coord_prev = coord_next;

               switch(coord_next){
                  case NORTH :
                     y += current_step;
                     break;
                  case EAST :
                     x += current_step;
                     break;
                  case SOUTH :
                     y -= current_step;
                     break;
                  case WEST :
                     x -= current_step;
                     break;
                  }
            }
         }
      }
      current_char++;
   }

   printf("done! (x=%d, y=%d => total=%d)\n", x, y, abs(x) + abs(y));
   return 0;
}
