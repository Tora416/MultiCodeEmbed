#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 14
#define MAX_STACK_SIZE 10000000
#define MAX 455
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

int*** make3darrint(int rows, int cols,int hei){
    int ***x;
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
typedef struct{
    short int row;
    short int col;
    short int hei;
    short int dir;
} element;
element queue[MAX_STACK_SIZE];
int rear = -1;
int front = -1;
void queueFull(){
    fprintf(stderr, "佇列已滿，不能再加入元素");
    exit(EXIT_FAILURE);
}
void addq(element item){
    if(rear==MAX_STACK_SIZE-1){
        queueFull();
    }
    queue[++rear] = item;
}
element deleteq(){
    if(front==rear){
        fprintf(stderr, "1佇列已空");
    }
    return queue[++front];
}

typedef struct{
    element t;
    int flag;
} tpoint;
tpoint queue2[MAX_STACK_SIZE];
int rear2 = -1;
int front2 = -1;
void addq2(tpoint item){
    if(rear2==MAX_STACK_SIZE-1){
        queueFull();
    }
    queue2[++rear2] = item;
}
tpoint deleteq2(){
    if(front2==rear2){
        fprintf(stderr, "1佇列已空");
    }
    return queue2[++front2];
}

typedef struct{
    short int vert;
    short int horiz;
    short int hei;
}offsets;
offsets move[6];


int min=10000;
int n;


int bfs(char*** maze,int*** d,int sr,int sc,int sh){

    int laststep=0;
    int arrive=0;
    element position;
    position.row = sr;
    position.col = sc;
    position.hei = sh;
    

    addq(position);
    int i,j,k,q;
    for(i=0;i<n/2+1;i++){
        for(j=0;j<n+2;j++){
            for(k=0;k<n+2;k++){
                d[i][j][k]=MAX;
            }
        }
    }
    d[sh][sr][sc]=0;
    

    int nr,nc,nh;
    int row,col,hei;
    while(rear!=front){
        

        
        position = deleteq();
        row = position.row;
        col = position.col;
        hei = position.hei;
        
        
        
        
        if(laststep!=d[hei][row][col] ){
            
            if(front2!=rear2){
                for(i=front2+1;i<=rear2;i++){
                    if(queue2[i].flag!=0){
                        if((queue2[i].flag-d[hei][row][col]+laststep)>=0){
                            queue2[i].flag-=(d[hei][row][col]-laststep);
                            
                            
                            
                        }
                        else queue2[i].flag=0;
                    }
                    if(queue2[i].flag==0){
                        addq(queue2[i].t);
                        deleteq2();
                        nr = queue2[i].t.row;
                        nc = queue2[i].t.col;
                        nh = queue2[i].t.hei;
                        
                        d[nh][nr][nc]=d[hei][row][col]+1;
                        
                    }
                }
            }
            laststep=d[hei][row][col];
        }
        
        
        
        
        if(maze[hei][row][col]=='U' || maze[hei][row][col]=='D'){
            
            
            int upanddown=-1;
            if(maze[hei][row][col]=='U'){
                
                upanddown=1;
            }
            

            nr = row;
            nc = col;
            nh = hei+upanddown;
            
            
            if(nh>=0){
                if(maze[nh][nr][nc]=='F'){
                    d[nh][nr][nc]=d[hei][row][col]+1;
                    
                    
                    if(min>d[nh][nr][nc]){
                        min = d[nh][nr][nc];
                    }
                    
                    return 1;
                }
                if(maze[nh][nr][nc]=='T'&& d[nh][nr][nc]==MAX){
                    
                    d[nh][nr][nc]=-1;
                    element nextposition;
                    nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;

                        tpoint Tpoint;

                        Tpoint.t=nextposition;
                        Tpoint.flag=2;
                        addq2(Tpoint);
                        
                        int r = queue2[front2].t.row;
                        int c = queue2[front2].t.col;
                        int h = queue2[front2].t.hei;
                        


                }
                else if (maze[nh][nr][nc]!='X'  && d[nh][nr][nc]==MAX){
                    
                    d[nh][nr][nc]=d[hei][row][col]+1;

                    element nextposition;
                    nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;
                    addq(nextposition);
                    
                }
            }

        }
        
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;
            if(maze[nh][nr][nc]=='T'&& d[nh][nr][nc]==MAX){
                d[nh][nr][nc]=-1;
                
                element nextposition;
                nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;

                    tpoint Tpoint;
                    Tpoint.t=nextposition;
                    Tpoint.flag=2;
                    addq2(Tpoint);
                    
                    int r = queue2[rear2].t.row;
                    int c = queue2[rear2].t.col;
                    int h = queue2[rear2].t.hei;
                    
                    


            }
            else if (maze[nh][nr][nc]!='X' && d[nh][nr][nc]==MAX){
                d[nh][nr][nc]=d[hei][row][col]+1;
                element nextposition;
                nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;
                addq(nextposition);
                
            }

        }
        if(rear==front){
            int lastflag=queue2[front2+1].flag;
            for(i=front2+1;i<=rear2;i++){
                if(queue2[i].flag==lastflag){
                    addq(queue2[i].t);
                    deleteq2();
                    nr = queue2[i].t.row;
                    nc = queue2[i].t.col;
                    nh = queue2[i].t.hei;
                    
                    d[nh][nr][nc]=d[hei][row][col]+3;
                    

                }
                else{
                    queue2[i].flag-=lastflag;
                    
                }
            }
            laststep=lastflag;
        }
        

    }
    return arrive;
}

void path(int ***d,char ***maze,char*** road,int fr,int fc,int fh){

    int row=fr;
    int col=fc;
    int hei=fh;
    int i,j,k,nr,nc,nh;
    road[hei][row][col]='*';

    
    while(maze[hei][row][col]!='S'){
        
        if ((d[hei][row+1][col]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei][row+1][col]==d[hei][row][col]-3 && maze[hei][row][col]=='T')){
            
            row++;
        }
        else if ((d[hei][row-1][col]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei][row-1][col]==d[hei][row][col]-3 && maze[hei][row][col]=='T')){
            
            row--;
        }
        else if ((d[hei][row][col+1]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei][row][col+1]==d[hei][row][col]-3 && maze[hei][row][col]=='T')){
            col++;
        }
        else if ((d[hei][row][col-1]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei][row][col-1]==d[hei][row][col]-3 && maze[hei][row][col]=='T')){
            col--;
        }
        else if(maze[hei-1][row][col]=='U' &&((d[hei-1][row][col]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei-1][row][col]==d[hei][row][col]-3 && maze[hei][row][col]=='T'))){
            hei--;
        }
        else if(maze[hei+1][row][col]=='U' &&((d[hei+1][row][col]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei+1][row][col]==d[hei][row][col]-3 && maze[hei][row][col]=='T'))){
            hei++;
        }
        road[hei][row][col]='*';
    }
}
int main(){
    move[0].vert=-1;
    move[0].horiz=0;
    move[0].hei=0;
    move[1].vert=0;
    move[1].horiz=1;
    move[1].hei=0;
    move[2].vert=1;
    move[2].horiz=0;
    move[2].hei=0;
    move[3].vert=0;
    move[3].horiz=-1;
    move[3].hei=0;
    move[4].vert=0;
    move[4].horiz=0;
    move[4].hei=1;
    move[5].vert=0;
    move[5].horiz=0;
    move[5].hei=-1;
    
    char y;
    int i,j,k;

    FILE *pfile;
    char name[50];
    int control;
    for(control=2;control<=100;control++){
        min=100000;
        rear=-1;front=-1;
        rear2=-1;front2=-1;
        sprintf(name,"test%d.txt",control);
        pfile = fopen(name,"r");
        if(NULL==pfile){
            printf("Open failure");
            return 1;
        }
        else{
            printf("reading %s\n",name);
            
            char* bottom = make1darr(MAXLEN);
            n=0;
            char y;
            bottom[n]=fgetc(pfile);
            while(bottom[n]!='\n'){
                fgetc(pfile);
                bottom[++n]=fgetc(pfile);
                
            }
            char ***maze=make3darr(n/2+1,n+2,n+2);
            char ***road=make3darr(n/2+1,n+2,n+2);
            char ***mark=make3darr(n/2+1,n+2,n+2);
            int ***d=make3darrint(n/2+1,n+2,n+2);
            int len=0;
            int sr,sc,sh,fr,fc,fh;
            for(i=0;i<n/2+1;i++){
                for(j=0;j<n+2;j++){
                    for(k=0;k<n+2;k++){
                        if(j==0 || k==0 || j==n+1 || k==n+1){
                            maze[i][j][k]='X';
                        }
                        else if(i==0 && j==1){
                            maze[i][j][k]=bottom[k-1];
                        }
                        else if(j > len && j <= n-len && k > len && k <= n-len){
                            fscanf(pfile,"%c ",&maze[i][j][k]);

                        }
                        else{
                            maze[i][j][k]='X';
                        }
                        if(maze[i][j][k]=='S'){
                            sh=i;
                            sr=j;
                            sc=k;
                        }
                        if(maze[i][j][k]=='F'){
                            fh=i;
                            fr=j;
                            fc=k;
                        }
                        road[i][j][k]=maze[i][j][k];
                        mark[i][j][k]=maze[i][j][k];
                    }
                }
                len++;
            }
            FILE *wfile;
            sprintf(name,"test%d_ans.txt",control);
            wfile = fopen(name,"w");
            if( NULL == wfile ){
                printf( "wfile open failure" );
                return 1;
            }
            else{
                if(bfs(maze,d,sr,sc,sh)){
                    
                    
                    path(d,maze,road,fr,fc,fh);
                    
                    
                    fprintf(wfile,"Path length: %d\n",min);
                    fprintf(wfile,"=====outMaze=====\n");
                    for(i=0;i<n/2+1;i++){
                        for(j=i+1;j<n+2-i-1;j++){
                            for(k=i+1;k<n+2-i-1;k++){
                                fprintf(wfile,"%c ",road[i][j][k] );
                            }
                            fprintf(wfile,"\n");
                        }
                        fprintf(wfile,"\n");
                    }
                }
                else fprintf(wfile,"The maze does not have a path\n" );
            }
            free(bottom);

            for(i = 0; i < n/2+1; i++) {
                for(j=0;j<n+2;j++){
                    free(maze[i][j]);
                }
            }
            for(i=0;i < n/2+1; i++){
                free(maze[i]);
            }
            free(maze);
            for(i = 0; i < n/2+1; i++) {
                for(j=0;j<n+2;j++){
                    free(mark[i][j]);
                }
            }
            for(i=0;i < n/2+1; i++){
                free(mark[i]);
            }
            free(mark);
            for(i = 0; i < n/2+1; i++) {
                for(j=0;j<n+2;j++){
                    free(road[i][j]);
                }
            }
            for(i=0;i < n/2+1; i++){
                free(road[i]);
            }
            free(road);
            for(i = 0; i < n/2+1; i++) {
                for(j=0;j<n+2;j++){
                    free(d[i][j]);
                }
            }
            for(i=0;i < n/2+1; i++){
                free(d[i]);
            }
            free(d);
        }
        fclose(pfile);

    }
}
