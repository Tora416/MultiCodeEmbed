#include <stdio.h>
#include <stdlib.h>

void Count(){
    FILE *rf, *wf;
    int i, j, k, a, b, c;
    double count[27][27][27], total = .0;
    for(i = 0; i < 27; i++){
        for(j = 0; j < 27; j++){
            for(k = 0; k < 27; k++) count[i][j][k] = .0;
        }
    }
    if((rf = fopen("outtext.txt", "r")) != NULL){
        b = fgetc(rf);
        c = fgetc(rf);
        while( ! feof(rf)){
            a = b;
            b = c;
            c = fgetc(rf);
            if('A' <= a && a <= 'Z'){
                if('A' <= b && b <= 'Z'){
                    if('A' <= c && c <= 'Z') count[a-'A'][b-'A'][c-'A']++;
                    else if(c == 0X20) count[a-'A'][b-'A'][26]++;
                }else if(b == 0X20){
                    if('A' <= c && c <= 'Z') count[a-'A'][26][c-'A']++;
                    else if(c == 0X20) count[a-'A'][26][26]++;
                }
            }else if(a = 0X20){
                if('A' <= b && b <= 'Z'){
                    if('A' <= c && c <= 'Z') count[26][b-'A'][c-'A']++;
                    else if(c == 0X20) count[26][b-'A'][26]++;
                }else if(b == 0X20){
                    if('A' <= c && c <= 'Z') count[26][26][c-'A']++;
                    else if(c == 0X20) count[26][26][26]++;
                }
            }
            total++;
        }
        fclose(rf);
    }else printf("File not open\n");
    wf = fopen("probability3.txt", "w");
    for(i = 0; i < 27; i++){
        for(j = 0; j < 27; j++){
            for(k = 0; k < 27; k++){
                printf("%c%c%c : %g\n", i+65, j+65, k+65, count[i][j][k]);
                fprintf(wf, "%.6lf\n", count[i][j][k]/total);
            }
        }
    }
}

int main(){
    Count();
    return 0;
}
 
