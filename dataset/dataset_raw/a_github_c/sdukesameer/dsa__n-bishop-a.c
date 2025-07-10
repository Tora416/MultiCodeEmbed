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
    int i,j;
    for (i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--)
        if(arr[i][j])
            return 0;
    for (i = row+1, j = col+1; i < N && j < N; i++, j++)
        if(arr[i][j])
            return 0;
    for (i = row+1, j = col-1; i < N && j >= 0; i++, j--)
        if(arr[i][j])
            return 0;
    for (i = row-1, j = col+1; i >= 0 && j < N; i--, j++)
        if(arr[i][j])
            return 0;
    return 1;
}
void bishops(int arr[N][N], int c){
    if(c>=N){
        printboard(arr);
        if(N>1){
            int trs[N][N];
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    trs[j][i]=arr[i][j];
            printboard(trs);
        }
        return;
    }
    for (int i = 0; i < N; i++){
        if(safe(arr,i,c)){
            arr[i][c]=1;
            bishops(arr,c+1);
            arr[i][c]=0;
        }
    }
}
int main(){
    int x=1;
    while(x){
        printf("Enter valid N i.e. for no of rows and columns: ");
        scanf("%d",&N);
        if(N>0)
            x=0;
    }
    int arr[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            arr[i][j]=0;
    bishops(arr,0);
    return 0;
}