#include<stdio.h>
int N;
int safe(int arr[N][N], int row, int col){
    int i,j;
    for ( i = 0; i < col; i++){
        if(arr[row][i])
            return 0;
    }
    for ( i = row, j = col; i >= 0 && j >= 0; i--, j--){
        if(arr[i][j])
            return 0;
    }
    for ( i = row, j = col; i < N && j >= 0; i++, j--){
        if(arr[i][j])
            return 0;
    }
    return 1;
}
int queens(int arr[N][N],int n){
    if(n>=N)
        return 1;
    for (int i = 0; i < N; i++)
    {
        if(safe(arr,i,n)){
            arr[i][n]=1;
            if(queens(arr,n+1))
                return 1;
            arr[i][n]=0;
        }
    }
    return 0;
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
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            arr[i][j]=0;
    }
    int ans=queens(arr,0);
    if(ans==0)
        printf("\nSolution doesn't exist.\n");
    else{
        printf("\nSolution by placing queens at:");
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if(arr[i][j])
                    printf(" %d,%d",i,j);
        printf(".\n");
    }
    return 0;
}