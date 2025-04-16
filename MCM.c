#include <stdio.h>

#define MAX_MATRICES 100

void matrixChainMultiplication(int p[], int n, int cost[MAX_MATRICES][MAX_MATRICES], int paren[MAX_MATRICES][MAX_MATRICES]) {
    for (int i = 1; i <= n; ++i) {
        cost[i][i] = 0;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            cost[i][j] = __INT_MAX__;

            for (int k = i; k < j; ++k) {
                int tempCost = cost[i][k] + cost[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (tempCost < cost[i][j]) {
                    cost[i][j] = tempCost;
                    paren[i][j] = k;
                }
            }
        }
    }
}

void printParenthesis(int i, int j, int paren[MAX_MATRICES][MAX_MATRICES]) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printParenthesis(i, paren[i][j], paren);
        printParenthesis(paren[i][j] + 1, j, paren);
        printf(")");
    }
}

int main() {
    int n;
    int p[MAX_MATRICES];

    // Get user input
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    printf("Enter the dimensions of matrices (size of p array): ");
    for (int i = 0; i <= n; ++i) {
        scanf("%d", &p[i]);
    }

    int cost[MAX_MATRICES][MAX_MATRICES];
    int paren[MAX_MATRICES][MAX_MATRICES];

    // Calculate minimum cost and parenthization
    matrixChainMultiplication(p, n, cost, paren);

    // Print the minimum cost
    printf("Minimum cost of multiplication: %d\n", cost[1][n]);

    // Print the optimal parenthization
    printf("Optimal parenthization: ");
    printParenthesis(1, n, paren);
    printf("\n");

    return 0;
}

