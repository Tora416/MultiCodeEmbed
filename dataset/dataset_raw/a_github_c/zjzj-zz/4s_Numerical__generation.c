#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *rf, *wf;
int a , i = 0, n;
double count[28], kakuritu[27];
double r, sum, total = .0;

void Conversion(){
    if((rf = fopen("intext.txt", "r")) != NULL){
        wf = fopen("outtext.txt", "w");
        while((a = fgetc(rf)) != EOF){
            if('A' <= a && a <= 'Z') a = a;
            else if('a' <= a && a <= 'z') a = a-0X20;
            else if(a == 0X0A) a = a;
            else a = 0X20;
            fputc(a, wf);
        }
        fclose(rf);
        fclose(wf);
    }else printf("File not open\n");
}

void Count(){
    for(i = 0; i < 28; i++) count[i] = .0;
    if((rf = fopen("outtext.txt", "r")) != NULL){
        while((a = fgetc(rf)) != EOF){
            if('A' <= a && a <= 'Z') count[a-'A']++;
            else if(a == 0X20) count[26]++;
            else if(a == 0X0A) count[27]++;
            if(a != 0X0A) total++;
        }
        fclose(rf);
    }else printf("File not open\n");
    wf = fopen("probability.txt", "w");
    for(i = 0; i < 27; i++) fprintf(wf, "%.6lf\n", count[i]/total);
    fclose(wf);
}

void Create(){
    srand(time(NULL));
    i = 0;
    rf = fopen("probability.txt", "r");
    while(! feof(rf)){
        fscanf(rf, "%lf\n", &kakuritu[i]);
        i++;
    }
    for(i = 0; i < 100; i++){
        r = (rand() % 1000000 + 1);
        r /= 1000000;
        for(sum = n = 0; sum < 1; n++){
            sum += kakuritu[n];
            if(r < sum){
                if(n == 26){
                    printf("%c", 0X20);
                    break;
                }else{
                    printf("%c", n+65);
                    break;
                }
            }
        }
    }
    printf("\n");
    fclose(rf);
}

int main(){
    Conversion();
    Count();
    Create();
    return 0;
}
