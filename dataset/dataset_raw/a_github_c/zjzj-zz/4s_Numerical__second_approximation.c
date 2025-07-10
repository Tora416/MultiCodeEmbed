#include <stdio.h>
#include <stdlib.h>

void Count(){
    FILE *rf, *wf;
    int i, n, a, b;
    double count[27][27], total = .0;
    for(i = 0; i < 27; i++) {
        for(n = 0; n < 27; n++) count[i][n] = .0;
    }
    if((rf = fopen("outtext.txt", "r")) != NULL){
        b = fgetc(rf);
        while( ! feof(rf)){
            a = b;
            b = fgetc(rf);
            if('A' <= a && a <= 'Z'){
                if('A' <= b && b <= 'Z') count[a-'A'][b-'A']++;
                else if(b == 0X20) count[a-'A'][26]++;
            }else if(a == 0X20){
                if('A' <= b && b <= 'Z') count[26][b-'A']++;
                else if(b == 0X20) count[26][26]++;
            }
            total++;
        }
        fclose(rf);
    }else{
        printf("File not open\n");
    }
    wf = fopen("probability2.txt", "w");
    for(i = 0; i < 27; i++){
        for(n = 0; n < 27; n++){
            printf("%c%c : %g\n", i+65, n+65, count[i][n]);
            fprintf(wf, "%.6lf\n", count[i][n]/total);
        }
    }
}

int main(){
    Count();
    return 0;
}
