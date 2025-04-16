#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

void printLCS(char* X, char* Y, int m, int n, int dp[MAX_LENGTH][MAX_LENGTH]) {
    int i = m, j = n;
    int index = dp[m][n];
    char lcs[MAX_LENGTH];

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Longest Common Subsequence: %s\n", lcs);
}

int lcs(char* X, char* Y, int m, int n) {
    int dp[MAX_LENGTH][MAX_LENGTH];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    printLCS(X, Y, m, n, dp);

    return dp[m][n];
}

int main() {
    char X[MAX_LENGTH];
    char Y[MAX_LENGTH];

    printf("Enter the first string: ");
    scanf("%s", X);

    printf("Enter the second string: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    int result = lcs(X, Y, m, n);

    printf("Length of Longest Common Subsequence: %d\n", result);

    return 0;
}

