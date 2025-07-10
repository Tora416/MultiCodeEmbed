
#include<stdio.h>
int N;
void display(int arr[N][N]){
    static int n=1;
    printf("\nSolution No. %d: \n",n++);
    for (int i = 0; i < N; i++){
        if(i==0){
            for (int k = 0; k < N; k++)
                printf(" ---");
            printf("\n");
        }
        printf("|");
        for (int j = 0; j < N; j++){
            if(arr[i][j])
                printf(" R |");
            else
                printf("   |");
        }
        printf("\n");
        for (int k = 0; k < N; k++)
            printf(" ---");
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
void rooks(int arr[N][N], int n){
    if(n>=N){
        display(arr);
        int trs[N][N], t=0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                trs[j][i]=arr[i][j];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if(trs[i][j]==arr[i][j])
                    t++;
        if(t!=(N*N))
            display(trs);
        return;
    }
    for (int i = 0; i < N; i++){
        if(safe(arr,i,n)){
            arr[i][n]=1;
            rooks(arr,n+1);
            arr[i][n]=0;
        }
    }
}
int main(){
    int n=1;
    while(n){
        printf("Enter valid N i.e no of rows and columns: ");
        scanf("%d",&N);
        if(N>0)
            n=0;
    }
    int arr[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            arr[i][j]=0;
    rooks(arr,0);
    return 0;
}