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
    int control;
    char ansname[50],myansname[50];
    FILE *pfile;
    char name[50];

    for(control=1;control<=100;control++){
        sprintf(ansname,"test%d_ans.txt",control);
        sprintf(myansname,"4108056029test%d_ans.txt",control);
        sprintf(name,"test%d.txt",control);
        pfile = fopen(name,"r");
        ans=fopen(ansname,"r");
        myans=fopen(myansname,"r");
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
            int i,j,k;
            int nans,nmy;
            fscanf(ans,"%*[a-zA-Z] %*[a-zA-Z]: ");
            fscanf(ans,"%d",&nans);
            printf("%d: %d ",control,nans );
            fscanf(myans,"%*[a-zA-Z] %*[a-zA-Z]: ");
            fscanf(myans,"%d",&nmy);
            printf("%d\n",nmy );
            if(nans!=nmy){
                printf("path length error in test%d\n",control);
                printf("ans : %d   myans : %d\n\n",nans,nmy );
            }

            fscanf(ans,"%*s");
            
            
            fscanf(myans,"%*s");
            
            char* ansb = make1darr(MAXLEN);
            char* myb = make1darr(MAXLEN);
            char* bottom = make1darr(MAXLEN);
            int n=0;
            char y;
            fgetc(ans);
            fgetc(myans);
            
            
            
            ansb[n]=fgetc(ans);
            myb[n]=fgetc(myans);
            bottom[n]=fgetc(pfile);
            
            while(ansb[n]!='\n' || myb[n]!='\n'){
                fgetc(ans);
                fgetc(myans);
                fgetc(pfile);
                ansb[++n]=fgetc(ans);
                myb[n]=fgetc(myans);
                bottom[n]=fgetc(pfile);
            }
            
            int len=0;
            char ansm[n/2+1][n][n],mym[n/2+1][n][n],maze[n/2+1][n][n];
            for(i=0;i<n/2+1;i++){
                for(j=0;j<n;j++){
                    for(k=0;k<n;k++){
                        if(i==0 && j==0){
                            
                            ansm[i][j][k]=ansb[k];
                            mym[i][j][k]=myb[k];
                            maze[i][j][k]=bottom[k];

                        }
                        else if(j >= len && j < n-len && k >= len && k < n-len){
                            

                            fscanf(ans,"%c ",&ansm[i][j][k]);
                            
                            fscanf(myans,"%c ",&mym[i][j][k]);
                            fscanf(pfile,"%c ",&maze[i][j][k]);

                        }
                        else{
                            
                            mym[i][j][k]='X';
                            ansm[i][j][k]='X';
                            maze[i][j][k]='X';
                        }

                    }
                }
                len++;
            }
            
            int check=0,counter=0;
            int hei[10],row[10],col[10];
            char ans[10],myans[10];
            for(i=0;i<n/2+1;i++){
                for(j=0;j<n;j++){
                    for(k=0;k<n;k++){
                        if(mym[i][j][k]!=ansm[i][j][k]){
                            
                            
                            row[counter]=j;
                            col[counter]=k;
                            hei[counter]=i;
                            ans[counter]=ansm[i][j][k];
                            myans[counter]=mym[i][j][k];
                            counter++;
                            check=1;
                        }
                    }
                    
                }
                
            }

            if(check){
                if((((row[0]+1==row[1]  || row[0]-1==row[1]) && (col[0]+1==col[1] ||  col[0]-1==col[1])) &&(ans[0]==myans[1]&&ans[1]==myans[0])&&counter==2)){
                    
                }
                else {

                    printf("map error\n");
                    for(i=0;i<counter;i++){
                        printf("in %d %d %d\n",hei[i],row[i],col[i]);
                        printf("ans : %c  myans : %c\n", ans[i],myans[i]);
                    }
                    printf("\n----------myans & ans---------\n" );
                    for(i=0;i<n/2+1;i++){
                        for(j=0;j<n;j++){
                            for(k=0;k<n;k++){
                                printf("%c ",mym[i][j][k] );
                            }
                            printf("    ");
                            for(k=0;k<n;k++){
                                printf("%c ",ansm[i][j][k] );
                            }
                            printf("    ");
                            for(k=0;k<n;k++){
                                printf("%c ",maze[i][j][k] );
                            }
                            printf("\n");
                        }
                        printf("\n");
                    }

                }

            }
        }
        fclose(ans);
        fclose(myans);
    }

}
