#include <stdio.h>
#include <stdlib.h>

void Count(){
    FILE *rf, *wf;
    int i, a;
    double count[28], total = .0, total2 = .0;
    for(i = 0; i < 28; i++) count[i] = .0;
    if((rf = fopen("outtext.txt", "r")) != NULL){
        while((a = fgetc(rf)) != EOF){
            if('A' <= a && a <= 'Z') count[a-'A']++;
            else if(a == 0x20) count[26]++;
            else if(a == 0x0A) count[27]++;
            if(a != 0x0A) total++;
        }
        fclose(rf);
    }else{
        printf("File open error!\n");
    }
    wf = fopen("probability.txt", "w");
    for(i = 0; i < 26; i++) printf("%c  : %g\n", i+65, count[i]);
    printf("SPC: %g\n", count[26]);
    printf("LF : %g\n", count[27]);
    printf("total : %g\n", total);
    for(i = 0; i < 27; i++) total2 += count[i];
    printf("total : %g\n", total2);
    for(i = 0; i < 27; i++) fprintf(wf, "%.6lf\n", count[i]/total);
}
int main(){
    Count();
    return 0;
}
