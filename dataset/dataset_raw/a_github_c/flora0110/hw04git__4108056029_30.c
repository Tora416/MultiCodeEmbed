#include <stdio.h>
#include <stdlib.h>
typedef struct position{
    int row;
    int col;
    int mirror;
}position;
typedef struct Orien{
    int row;
    int col;
}Orien;
Orien orien[4];
void mark(char**,int**,int,int,int,int,int,int,int,int,int);

int n;
int main(){
    FILE* rptr;
    FILE* wptr;
    rptr=fopen("test4.txt","r");
    if(rptr==NULL){
        printf("error\n");
        return 0;
    }
    
    orien[0].row=1;
    orien[0].col=0;
    orien[1].row=0;
    orien[1].col=-1;
    orien[2].row=-1;
    orien[2].col=0;
    orien[3].row=0;
    orien[3].col=1;
    int v,z,g;
    fscanf(rptr,"%d %d %d\n",&v,&z,&g);
    fscanf(rptr,"%d\n",&n);
    int** see=(int**)malloc((n*4)*sizeof(int*));
    int i,j;
    for(i=0;i<n*4;i++){
        see[i]=(int*)malloc(4*sizeof(int));
        fscanf(rptr,"%d ",&see[i][0]);
        if(i<n){
            see[i][1]=1;
            see[i][2]=i+1;
            see[i][3]=0;
        }
        else if(i<2*n){
            see[i][1]=n;
            see[i][2]=i-n+1;
            see[i][3]=2;
        }
        else if(i<3*n){
            see[i][1]=i-2*n+1;
            see[i][2]=1;
            see[i][3]=3;
        }
        else{
            see[i][1]=i-n*3+1;
            see[i][2]=n;
            see[i][3]=1;
        }
    }
    char **ans=(char**)malloc((n+2)*sizeof(char*));
    for(i=0;i<n+2;i++){
        ans[i]=(char*)malloc((n+2)*sizeof(char));
        for(j=0;j<n+2;j++){
            if(i==0 || j==0 || i==n+1 || j==n+1){
                ans[i][j]='x';
            }
            else{
                fscanf(rptr,"%c",&ans[i][j]);
            }
        }
        if(i!=0 &&i!=n+1){
            fgetc(rptr);
        }
    }
    mark(ans,see,0,v,z,g,see[0][0],1,1,0,0);
    free(see);
    free(ans);
    for(i=0;i<n+2;i++){
        free(ans[i]);
    }
    for(i=0;i<3;i++){
        free(see[i]);
    }
    fclose(rptr);
}

void mark(char** ans,int** see,int seen,int v,int z,int g,int monsta,int row,int col,int mirror,int dir){
    int i,j;
    char origin=ans[row][col];
    if(v<0||z<0||g<0||monsta<0 || monsta>see[seen][0]){
        return;
    }
    if(ans[row][col]=='x' && monsta!=0){
        return;
    }
    if(ans[row][col]=='x' && monsta==0){
        if(seen==4*n-1){
            
            for(i=0;i<n+2;i++){
                for(j=0;j<n+2;j++){
                    printf("%c",ans[i][j]);
                }
                printf("\n");
            }
            return;
        }
        mark(ans,see,seen+1,v,z,g,see[seen+1][0],see[seen+1][1],see[seen+1][2],0,see[seen+1][3]);
        return;
    }
    if(ans[row][col]=='\\'){
        mirror=1;
        switch (dir) {
            case 0: dir=3;break;      case 1: dir=2;break;     case 2: dir=1;break;    case 3: dir=0;break;
        }
    }
    else if(ans[row][col]=='/'){
        mirror=1;
        switch (dir) {
            case 0: dir=1;break;  case 1: dir=0;break;  case 2: dir=3;break;  case 3: dir=2;break;
        }
    }
    int nextrow=row+orien[dir].row,nextcol=col+orien[dir].col,nextmonsta=monsta;
    if(ans[row][col]=='Z'||ans[row][col]=='G'||ans[row][col]=='V'){
        if(ans[row][col]=='Z') nextmonsta--;
        if(mirror==1 && ans[row][col]=='G') nextmonsta--;
        else if(mirror==0 && ans[row][col]=='V') nextmonsta--;
        mark(ans,see,seen,v,z,g,nextmonsta,nextrow,nextcol,mirror,dir);
    }
    else if(ans[row][col]=='.'){
        ans[row][col]='Z';
        mark(ans,see,seen,v,z-1,g,monsta-1,nextrow,nextcol,mirror,dir);
        if(mirror==1){
            ans[row][col]='G';
            mark(ans,see,seen,v,z,g-1,monsta-1,nextrow,nextcol,mirror,dir);
            ans[row][col]='V';
            mark(ans,see,seen,v-1,z,g,monsta,nextrow,nextcol,mirror,dir);
        }
        else if(mirror==0){
            ans[row][col]='G';
            mark(ans,see,seen,v,z,g-1,monsta,nextrow,nextcol,mirror,dir);
            ans[row][col]='V';
            mark(ans,see,seen,v-1,z,g,monsta-1,nextrow,nextcol,mirror,dir);
        }
    }
    else mark(ans,see,seen,v,z,g,monsta,nextrow,nextcol,mirror,dir);
    ans[row][col]=origin;
    return;
}
