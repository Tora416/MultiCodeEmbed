#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 14
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
char* make1darr(int n){
    char *x;
    MALLOC(x,n*sizeof(*x));
    return x;
}
char*** make3darr(int rows, int cols,int hei){
    char ***x;
    MALLOC(x,rows*sizeof(**x));
    int i,j;
    for(i=0;i<rows;i++){
        MALLOC(x[i],cols*sizeof(**x));
        for(j=0;j<hei;j++){
            MALLOC(x[i][j],hei*sizeof(***x));
        }
    }
    return x;
}
int main(){
    FILE *ans;
    FILE *myans;
    char name[50];
    ans=fopen("output_20201011.txt","r");
    myans=fopen("4108056029output.txt","r");

    if(NULL==ans || NULL == myans){
        printf("Open failure\n");
        if(NULL == myans){
            printf("my ans Open failure\n");
        }
        if(NULL == ans){
            printf("ans Open failure\n");
        }
        return 1;
    }

    else{
        int nans,nmy,i;
        int ansmin,ansLimit,anspathnum;
        int min,Limit,pathnum;
        for(i=0;i<100;i++){
            fscanf(ans,"test %d starts now.",&nans);
            
            char y=fgetc(ans);
            
            fscanf(ans,"Shortest path: %d, The number of different paths: %d",&ansmin,&anspathnum);
            
            y=fgetc(ans);
            
            y=fgetc(ans);
            

            fscanf(myans,"test %d starts now.",&nmy);
            

            char x =fgetc(myans);
            
            fscanf(myans,"Shortest path: %d, The number of different paths: %d",&min,&pathnum);
            
            x=fgetc(myans);
            
            x=fgetc(myans);
            
            if(min!=ansmin){
                printf("Shortest path error in test%d\n",nmy);
                printf("ans's min : %d   my min : %d\n\n",ansmin,min );
            }
            if(pathnum!=anspathnum){
                printf("pathnum error in test%d\n",nmy);
                printf("ans's  : %d   my  : %d\n\n",anspathnum,pathnum );
            }
        }



    }
    fclose(ans);
    fclose(myans);

}
