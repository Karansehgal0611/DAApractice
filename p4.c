#include<stdio.h>
#include<stdbool.h>
#define N 15
int board[N][N];
bool isSafe(int row,int col,int n)
{
    int i,j;
    for(int i=0;i<col;i++)
    {
        if(board[row][i])
        {
            return false;
        }

    }
    for(int i=row,j=col;j>=0&&i>=0;i--,j--)
    {
        if(board[i][j])
            {
                return false;
            }
    }
    for(int i=row,j=col;j>=0 && i<n;i++,j--)
    {
        if(board[i][j])
           {
                return false;
           }
    }
    return true;
}

bool solveNQueens(int col, int n)
{
    if(col>=n)
        return true;

    for(int i=0;i<n;i++)
    {
        if(isSafe(i,col,n))
        {
            board[i][col]=1;
            if(solveNQueens(col+1,n))
                return true;

            board[i][col]=0;
        }
    }

    return false;
}

void printb(int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(board[i][j])
                printf("Q");
            else
                printf(". ");
        }
        printf("\n");
    }

}
int main()
{
    int n;
    scanf("%d",&n);
    if(n < 4 || n > N)
    {
        printf("Invalid Board size. Please Enter a value greater than 4");
        return 1;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            board[i][j]=0;
        }
    }
    if(solveNQueens(0,n)==false)
    {
        printf("No solutions");
        return false;
    }
    printb(n);
}
