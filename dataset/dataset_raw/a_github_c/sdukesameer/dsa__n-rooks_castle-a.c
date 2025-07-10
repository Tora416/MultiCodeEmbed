#include<stdio.h>
int N;
void printboard(int arr[N][N]){
    static int n=1;
    printf("\nSolution No. %d: \n",n++);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if(arr[i][j])
                printf(" R ");
            else
                printf(" - ");
        }
        printf("\n");
    }
}
int safe(int arr[N][N], int row, int col){
    for (int i = 0; i < row; i++)
        if(arr[row][i])
            return 0;
    for (int i = 0; i < col; i++)
        if(arr[row][i])
            return 0;
    return 1;
}
void rooks(int arr[N][N], int c){
    if(c>=N){
        printboard(arr);
        int trs[N][N], t=0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                trs[j][i]=arr[i][j];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if(trs[i][j]==arr[i][j])
                    t++;
        if(t!=(N*N))
            printboard(trs);
        return;
    }
    for (int i = 0; i < N; i++){
        if(safe(arr,i,c)){
            arr[i][c]=1;
            rooks(arr,c+1);
            arr[i][c]=0;
        }
    }
}
int main(){
    int x=1;
    while(x){
        printf("Enter valid N i.e for no of rows and columns: ");
        scanf("%d",&N);
        if(N>0)
            x=0;
    }
    int arr[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            arr[i][j]=0;
    rooks(arr,0);
    return 0;
}