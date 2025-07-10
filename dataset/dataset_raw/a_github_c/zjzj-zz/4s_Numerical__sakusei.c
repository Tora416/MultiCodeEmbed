#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void Create(){
    FILE *rf;
    double sum, a, kakuritu[27];
    int i = 0, n;

    srand(time(NULL));
    rf = fopen("probability.txt", "r");
    while( ! feof(rf)){
        fscanf(rf, "%lf\n", &kakuritu[i]);
        i++;
    }
    for(i = 0; i < 100; i++){
        a = (rand() % 1000000 + 1);
        a /= 1000000;
        for(sum = n = 0; sum < 1; n++){
            sum += kakuritu[n];
            if(a < sum){
                if(n == 26){
                    printf("%c", 0x20);
                    break;
                }else{
                    printf("%c", n+65);
                    break;
                }
            }
        }
    }
    printf("\n");
}

int main(){
    Create();
    return 0;
}
