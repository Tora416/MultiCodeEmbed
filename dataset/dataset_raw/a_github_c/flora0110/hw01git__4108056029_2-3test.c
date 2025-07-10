#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 14
#define MAX_STACK_SIZE 100000
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

element stack[MAX_STACK_SIZE];
int top = -1;
void stackFull(){
    fprintf(stderr, "堆疊已滿，不能再加入元素");
    exit(EXIT_FAILURE);
}
void push(element item){
    if(top >=MAX_STACK_SIZE-1){
        stackFull();
    }
    stack [++top] = item;
}
element pop(){
    if(top==-1){
        fprintf(stderr, "堆疊已空");
    }
    return stack[top--];
}

element stack2[MAX_STACK_SIZE];
int top2 = -1;
void push2(element item){
    if(top2 >=MAX_STACK_SIZE-1){
    }
    stack2 [++top2] = item;
}
element pop2(){
    
    return stack2[top2--];
}

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


int pathnum=0;
int min=100000;
int step=0;
void path(char*** maze,char*** mark,char*** road,int sr,int sc,int sh,int n,int pnum){
    step=0;
    min=100000;
    pathnum=0;
    top=-1;
    int i,j,k;
    
    element position;
    int row,col,hei,dir;
    int nr,nc,nh;
    int countp=0;
    int found=1;
    int inproad=0;
    position.row = sr;
    position.col = sc;
    position.hei = sh;
    push(position);
    while(top>-1){
        
        position=pop();
        row = position.row;
        col = position.col;
        hei = position.hei;
        dir = position.dir;


        if(!found){
            
            while(top2>-1){
                element lastposition = pop2();
                int lr=lastposition.row;int lc=lastposition.col;int lh=lastposition.hei;int ld=lastposition.dir;
                
                
                if(lr+move[dir].vert==row && lc+move[dir].horiz==col && lh+move[dir].hei==hei ){

                    push2(lastposition);
                    break;
                }
                road[lh][lr][lc]=maze[lh][lr][lc];
                mark[lh][lr][lc]=maze[lh][lr][lc];
                if(maze[lh][lr][lc]=='T'){
                    step=step-3;
                }
                else step--;
                if(maze[lh][lr][lc]=='P'){
                    countp--;
                }
                
            }
        }
        mark[hei][row][col]='X';
        road[hei][row][col]='*';
        if(maze[hei][row][col]=='T'){
            step=step+3;
        }
        else step++;
        if(maze[hei][row][col]=='P'){
            inproad=1;
            countp++;
        }
        if(countp==pnum){
            inproad=0;
        }
        push2(position);

        printf("now %d %d %d\n",hei,row,col );
        
        road[hei][row][col]='@';
        printf("road!! \n");
        for(i=0;i<n/2+1;i++){
            for(j=i+1;j<n+2-i-1;j++){
                for(k=i+1;k<n+2-i-1;k++){
                    printf("%c ",road[i][j][k] );
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("countp %d\n\n",countp );
        printf("mark!! \n");
        for(i=0;i<n/2+1;i++){
            for(j=i+1;j<n+2-i-1;j++){
                for(k=i+1;k<n+2-i-1;k++){
                    printf("%c ",mark[i][j][k] );
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("countp %d\n\n",countp );
        printf("step %d\n\n",step );
        road[hei][row][col]='*';
        
        if(maze[hei][row][col]=='F' && countp==pnum){
            pathnum++;
            if(min>step){
                min=step;

            }
            printf("finally------------------------------------------------\n" );
            
            printf("road!! \n");
            for(i=0;i<n/2+1;i++){
                for(j=i+1;j<n+2-i-1;j++){
                    for(k=i+1;k<n+2-i-1;k++){
                        printf("%c ",road[i][j][k] );
                    }
                    printf("\n");
                }
                printf("\n");
            }
            printf("countp %d pnum %d\n",countp,pnum );
            printf("step %d\n\n",step );
            printf("pathnum %d\n",pathnum );
            

            
        }
        
        found=0;
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;
            if(inproad){
                if(mark[nh][nr][nc]!='X' && maze[nh][nr][nc]=='P'){
                    found=1;
                    

                    element nextposition;
                    nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;nextposition.dir=i;
                    push(nextposition);
                }
            }
            else{
                if(mark[nh][nr][nc]!='X'){
                    found=1;
                    

                    element nextposition;
                    nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;nextposition.dir=i;
                    push(nextposition);
                }
            }

        }
        if(maze[hei][row][col]=='U' || maze[hei][row][col]=='P'){
            if(inproad){
                if(mark[nh][nr][nc]!='X' && maze[hei+1][row][col]=='P'){
                    found=1;
                    element nextposition;
                    nextposition.row=row;nextposition.col=col;nextposition.hei=hei+1;nextposition.dir=4;
                    push(nextposition);
                }
            }
            else{
                if(mark[hei+1][row][col]!='X'){
                    
                    found=1;
                    element nextposition;
                    nextposition.row=row;nextposition.col=col;nextposition.hei=hei+1;nextposition.dir=4;
                    push(nextposition);
                }
            }




        }
        if((maze[hei][row][col]=='D'  || maze[hei][row][col]=='P')&& hei>0){
            if(inproad){
                if(mark[nh][nr][nc]!='X' && maze[hei-1][row][col]=='P'){
                    found=1;
                    element nextposition;
                    nextposition.row=row;nextposition.col=col;nextposition.hei=hei-1;nextposition.dir=5;
                    push(nextposition);
                }
            }
            else{
                if(mark[hei-1][row][col]!='X'){
                    
                    found=1;
                    element nextposition;
                    nextposition.row=row;nextposition.col=col;nextposition.hei=hei-1;nextposition.dir=5;
                    push(nextposition);
                }
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
    
    int n=0;
    char y;
    int i,j,k;

    FILE *pfile;
    char name[50];
    int control;
    for(control=2;control<=2;control++){
        sprintf(name,"test%d.txt",control);
        pfile = fopen(name,"r");
        if(NULL==pfile){
            printf("Open failure");
            return 1;
        }
        else{
            printf("reading %s\n",name);
            
            char* bottom = make1darr(MAXLEN);
            int n=0;
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
            int pnum=0;
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
                        if(maze[i][j][k]=='P'){
                            pnum++;
                        }
                        road[i][j][k]=maze[i][j][k];
                        mark[i][j][k]=maze[i][j][k];
                    }
                }
                len++;
            }
            
            FILE *wfile;
            wfile = fopen( "4108056029output.txt","a" );
            if( NULL == wfile ){
                printf( "wfile open failure" );
                return 1;
            }
            else{
                fprintf(wfile, "test%d Starts now.\n",control );

                
                if(1){
                    
                    mark[sh][sr][sc]='X';
                    pathnum=0;
                    path(maze,mark,road,sr,sc,sh,n,pnum);
                    printf("Shortest path: %d, The number of different paths: %d\n\n",min-1,pathnum);
                    fprintf(wfile,"Shortest path: %d, The number of different paths: %d\n\n",min-1,pathnum);
                }
                else fprintf(wfile,"The maze does not have a path\n" );
            }
            free(bottom);
            free(maze);
            free(mark);
            free(road);
            free(d);
        }
        fclose(pfile);

    }
}
