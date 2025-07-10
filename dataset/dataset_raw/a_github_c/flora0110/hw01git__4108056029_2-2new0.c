
#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 14
#define MAX_STACK_SIZE 1000
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
        fprintf(stderr, "佇列已空");
    }
    return queue[++front];
}

typedef struct{
    short int vert;
    short int horiz;
    short int hei;
}offsets;
offsets move[6];


int min;
int n;

int bfs(char*** maze,int*** d,int sr,int sc,int sh){
    rear=-1;front=-1;

    int arrive=0;
    element position;
    position.row = sr;
    position.col = sc;
    position.hei = sh;
    

    addq(position);
    int i,j,k;
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
        

        if(maze[hei][row][col]=='F'){
            
            if(min>d[hei][row][col]){
                min = d[hei][row][col];
            }
            min = d[hei][row][col];
            
            arrive=1;
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
                if (maze[nh][nr][nc]!='X' && d[nh][nr][nc]>d[hei][row][col]+1){
                    d[nh][nr][nc]=d[hei][row][col]+1;
                    if(maze[nh][nr][nc]=='T'){
                        d[nh][nr][nc]=d[nh][nr][nc]+2;
                    }
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

            if (maze[nh][nr][nc]!='X' && d[nh][nr][nc]>d[hei][row][col]+1){
                d[nh][nr][nc]=d[hei][row][col]+1;
                if(maze[nh][nr][nc]=='T'){
                    d[nh][nr][nc]=d[nh][nr][nc]+2;
                }
                element nextposition;
                nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;
                addq(nextposition);
            }

        }
        

    }
    return arrive;
}
int pathnum=0;

void dfs(char*** maze,char*** mark,char*** road,int row,int col,int hei,int count){

    int i,j,k;

    if(count>=(min+5)){
        return;
    }
    else{
        int i;
        int nh,nr,nc;
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;
            if(mark[nh][nr][nc]!='X'){
                mark[nh][nr][nc]='X';
                road[nh][nr][nc]='*';
                if(maze[nh][nr][nc]=='T'){
                    dfs(maze,mark,road,nr,nc,nh,count+3);
                }

                else{
                    dfs(maze,mark,road,nr,nc,nh,count+1);
                }
                mark[nh][nr][nc]=maze[nh][nr][nc];
                road[nh][nr][nc]=maze[nh][nr][nc];

            }
        }
        if(maze[hei][row][col]=='U'){
            if(mark[hei+1][row][col]!='X'){
                mark[hei+1][row][col]='X';
                road[hei+1][row][col]='*';
                if(maze[hei+1][row][col]=='T'){

                    dfs(maze,mark,road,row,col,hei+1,count+3);

                }
                else if(maze[hei+1][row][col]=='F'){
                    pathnum++;
                }
                else{
                    dfs(maze,mark,road,row,col,hei+1,count+1);
                }
                mark[hei+1][row][col]=maze[hei+1][row][col];
                road[hei+1][row][col]=maze[hei+1][row][col];
            }



        }
        else if(maze[hei][row][col]=='D' && hei>0){
            if(mark[hei-1][row][col]!='X'){

                mark[hei-1][row][col]='X';
                road[hei-1][row][col]='*';
                if(mark[hei-1][row][col]='T'){
                    dfs(maze,mark,road,row,col,hei-1,count+3);
                }
                else{

                    dfs(maze,mark,road,row,col,hei-1,count+1);
                }
                mark[hei-1][row][col]=maze[hei-1][row][col];
                road[hei-1][row][col]=maze[hei-1][row][col];
            }
        }

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
    FILE *wfile;
    wfile = fopen( "4108056029output.txt","w" );
    if( NULL == wfile ){
        printf( "wfile open failure" );
        return 1;
    }
    else{
        for(control=58;control<=58;control++){
            min = 100000;
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
                int sr,sc,sh;
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
                            road[i][j][k]=maze[i][j][k];
                            mark[i][j][k]=maze[i][j][k];
                        }
                    }
                    len++;
                }
                fprintf(wfile, "test %d starts now.\n",control );
                if(bfs(maze,d,sr,sc,sh)){
                    mark[sh][sr][sc]='X';
                    pathnum=0;
                    dfs(maze,mark,road,sr,sc,sh,0);
                    printf("Sortest path : %d, Limit: %d, The number of different paths: %d\n\n",min,min+5,pathnum);
                    fprintf(wfile,"Shortest path: %d, Limit: %d, The number of different paths: %d\n\n",min,min+5,pathnum);
                }
                else fprintf(wfile,"The maze does not have a path\n" );
                free(bottom);
                free(maze);
                free(mark);
                free(road);
                free(d);
            }
            fclose(pfile);

        }
    }
    fclose(wfile);
}
