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

int temp[9][3] = {0};
int distances[9] = {0}, points[9] = {0};
int longest_distance, time_flown, time_rested;

#define TOTAL_TIME 2503

int main(){
   
   memcpy(temp, data, sizeof(data));

   for(int time = 0; time < TOTAL_TIME; time++){
      
      for(int reindeer = 0; reindeer < 9; reindeer++){
         if(temp[reindeer][1] > 0){
            distances[reindeer] += data[reindeer][0];
            temp[reindeer][1]--;
         }
         else if(temp[reindeer][1] == 0){
            temp[reindeer][2]--;
            if(temp[reindeer][2] == 0){
               temp[reindeer][1] = data[reindeer][1];
               temp[reindeer][2] = data[reindeer][2];
            }
         }
      }

      
      longest_distance = 0;
      for(int reindeer = 0; reindeer < 9; reindeer++){
         if(distances[reindeer] > longest_distance){
            longest_distance = distances[reindeer];
         }
      }
      for(int reindeer = 0; reindeer < 9; reindeer++){
         if(distances[reindeer] == longest_distance){
            points[reindeer]++;
         }
      }
   }

   
   int most_points = 0;
   for(int reindeer = 0; reindeer < 9; reindeer++){
      if(points[reindeer] > most_points){
         most_points = points[reindeer];
      }
   }

   printf("winner=%d\n", most_points);
   return 0;
}
