#include<stdio.h>
#define maxs 6
#define maxl 2

int min(int a ,int b, int *line)
{
    if(a<b)
    {
        return a;
        *line=0;
    }
    else{
        return b;
        *line=1;
    }
}

int assembly(int a[maxl][maxs], int t[maxl][maxs-1], int e[maxl],int x[maxl],int path[maxl][maxs])
{
    int dp[maxl][maxs];

    dp[0][0]=e[0]+a[0][0];
    for(int i=1;i<maxs;i++)
    {
        int line;
        dp[0][i]=min(dp[0][i-1]+a[0][i],dp[1][i-1]+a[0][i]+t[1][i-1],&line);
        path[0][i]=line;
    }
    dp[1][0] = e[1] + a[1][0];
    for (int j = 1; j < maxs; ++j) {
        int line;
        dp[1][j] = min(dp[1][j - 1] + a[1][j], dp[0][j - 1] + t[0][j - 1] + a[1][j], &line);
        path[1][j] = line;
    }
    int exit=min(dp[0][maxs]+x[0],dp[1][maxs]+x[1],&path[0][maxs-1]);
    return exit;
}

void printstation(int path[maxl][maxs], int lastline, int laststation)
{
    if(laststation>0)
    {
        printstation(path, path[lastline][laststation],laststation-1);
    }
    printf("%d -> %d",lastline+1,laststation+1);
}
int main() {
    int a[maxl][maxs];
    int t[maxl][maxs - 1];
    int e[maxl];
    int x[maxl];
    int path[maxl][maxs];
    int n;

    printf("Enter the number of stations: ");
    scanf("%d",&n);
    printf("Enter assembly times, transfer times, entry times, and exit times:\n");
    for (int i = 0; i < 2; ++i) {
        printf("Line %d assembly times: ", i + 1);
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
        }

        printf("Line %d transfer times: ", i + 1);
        for (int j = 0; j < n - 1; ++j) {
            scanf("%d", &t[i][j]);
        }

        printf("Line %d entry time: ", i + 1);
        scanf("%d", &e[i]);

        printf("Line %d exit time: ", i + 1);
        scanf("%d", &x[i]);
    }

    // Perform assembly line scheduling
    int exitTime = assembly(a, t, e, x, path);

    // Print the result
    printf("Minimum time to exit: %d\n", exitTime);
    printf("Optimal path:");
    printstation(path, path[0][maxs - 1], maxs - 1);
    printf("\n");

    return 0;
}

