#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 100

// Structure to represent an item
struct Item {
    char name[20];
    int weight;
    int profit;
};

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to perform 0/1 knapsack using dynamic programming
void knapsack(int W, struct Item items[], int n) {
    int i, w;
    int dp[MAX_ITEMS + 1][W + 1];

    // Build table dp[][] in bottom-up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].profit + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Print the selected items and maximum profit
    int res = dp[n][W];
    printf("Maximum Profit: %d\n", res);

    w = W;
    printf("Selected items:\n");

    for (i = n; i > 0 && res > 0; i--) {
        if (res != dp[i - 1][w]) {
            printf("Item: %s, Weight: %d, Profit: %d\n", items[i - 1].name, items[i - 1].weight, items[i - 1].profit);
            res = res - items[i - 1].profit;
            w = w - items[i - 1].weight;
        }
    }
}

int main() {
    int n, i, capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct Item items[MAX_ITEMS];

    for (i = 0; i < n; i++) {
        printf("Enter the name, weight, and profit for item %d:\n", i + 1);
        scanf("%s %d %d", items[i].name, &items[i].weight, &items[i].profit);
    }

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    knapsack(capacity, items, n);

    return 0;
}

