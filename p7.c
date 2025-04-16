#include<stdio.h>
#include<string.h>
#define max1 20
int max(int a, int b) {
    return (a > b) ? a : b;
}

void printlcs(char *x,char *y, int m, int n, int dp[max1][max1])
{
    int i=m,j=n;
    int index=dp[m][n];
    char lcs[max1];
    while(i>0 && j>0)
    {
        if(x[i-1]==y[j-1])
        {
            lcs[index-1]=x[i-1];
            i--;
            j--;
            index--;
        }
        else if(dp[i-1][j] > dp[i][j-1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    printf("%s",lcs);
}

int lcs(char *x, char *y , int m , int n)
{
    int dp[max1][max1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
             if(i==0 || j==0)
             {
                 dp[i][j]=0;
             }
             else if(x[i-1]==y[j-1])
             {
                 dp[i][j]=1+dp[i-1][j-1];
             }
             else
             {
                 dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
             }
        }
    }
   printlcs(x,y,m,n,dp);

   return dp[m][n];
}
int main() {
    char X[max1];
    char Y[max1];

    printf("Enter the first string: ");
    scanf("%s", X);

    printf("Enter the second string: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    int result = lcs(X, Y, m, n);
    printf("\n");

    printf("Length of Longest Common Subsequence: %d\n", result);

    return 0;
}
