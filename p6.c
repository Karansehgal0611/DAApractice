#include<stdio.h>
#include<limits.h>
#define max 100
void mcm(int p[], int n , int cost[max][max],int par[max][max])
{
    for(int i=0;i<n;i++)
    {
        cost[i][i]=0;
    }
    for( int len=2;len<=n;++len)
    {
        for(int i=1;i<=n-len+1;++i)
        {
            int j=i+len-1;
            cost[i][j]=__INT_MAX__;
            for(int k=i;k<j;k++)
            {
                int temp=cost[i][k]+cost[k+1][j]+p[i-1]*p[j]*p[k];
                if(temp<cost[i][j])
                {
                    cost[i][j]=temp;
                    par[i][j]=k;
                }
            }
        }
    }
}
void parenth(int i, int j, int par[max][max])
{
    if(i==j)
        printf("A%d",i);
    else
    {
        printf("(");
        parenth(i,par[i][j],par);
        parenth(par[i][j]+1,j,par);
        printf(")");
    }
}
int main() {
    int n;
    int p[max];

    // Get user input
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    printf("Enter the dimensions of matrices (size of p array): ");
    for (int i = 0; i <= n; ++i) {
        scanf("%d", &p[i]);
    }

    int cost[max][max];
    int paren[max][max];

    // Calculate minimum cost and parenthization
    mcm(p, n, cost, paren);

    // Print the minimum cost
    printf("Minimum cost of multiplication: %d\n", cost[1][n]);

    // Print the optimal parenthization
    printf("Optimal parenthization: ");
    parenth(1, n, paren);
    printf("\n");

    return 0;
}


