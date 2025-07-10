#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int data[9][3] = {
   {22, 8, 165},
   {8, 17, 114},
   {18 , 6 , 103},
   {25 , 6 , 145},
   {11 , 12 , 125},
   {21 , 6 , 121},
   {18 , 3 , 50},
   {20 , 4 , 75},
   {7 , 20 , 119}
};

int distances[9] = {0};

#define TOTAL_TIME 2503

int distance, time_flown, time_rested;

int main(){
   for(int reindeer = 0; reindeer < 9; reindeer++){
      distance = 0;
      time_flown = data[reindeer][1];
      time_rested = 0;

      for(int time = 0; time < TOTAL_TIME; time++){
         if(time_flown > 0){
            distance += data[reindeer][0];
            time_flown--;
         }

         else if(time_flown == 0){
            time_rested++;
            if(time_rested == data[reindeer][2]){
               time_flown = data[reindeer][1];
               time_rested = 0;
            }
         }
      }
      distances[reindeer] = distance;
   }

   distance = 0;
   for(int reindeer = 0; reindeer < 9; reindeer++){
      if(distances[reindeer] > distance){
         distance = distances[reindeer];
      }
   }

   printf("winner=%d\n", distance);
   return 0;
}
