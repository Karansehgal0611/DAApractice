 #include <stdio.h>

#define MAX_STATIONS 6
#define MAX_LINES 2

int min(int a, int b, int *line) {
    if (a < b) {
        *line = 0;
        return a;
    } else {
        *line = 1;
        return b;
    }
}

// Function to perform assembly line scheduling using dynamic programming
int assemblyLineScheduling(int a[MAX_LINES][MAX_STATIONS], int t[MAX_LINES][MAX_STATIONS - 1], int e[MAX_LINES], int x[MAX_LINES], int path[MAX_LINES][MAX_STATIONS]) {
    int dp[MAX_LINES][MAX_STATIONS];

    // Calculate time to reach each station on the first line
    dp[0][0] = e[0] + a[0][0];
    for (int j = 1; j < MAX_STATIONS; ++j) {
        int line;
        dp[0][j] = min(dp[0][j - 1] + a[0][j], dp[1][j - 1] + t[1][j - 1] + a[0][j], &line);
        path[0][j] = line;
    }

    // Calculate time to reach each station on the second line
    dp[1][0] = e[1] + a[1][0];
    for (int j = 1; j < MAX_STATIONS; ++j) {
        int line;
        dp[1][j] = min(dp[1][j - 1] + a[1][j], dp[0][j - 1] + t[0][j - 1] + a[1][j], &line);
        path[1][j] = line;
    }

    // Calculate the exit time for both lines
    int exitTime = min(dp[0][MAX_STATIONS - 1] + x[0], dp[1][MAX_STATIONS - 1] + x[1], &path[0][MAX_STATIONS - 1]);

    return exitTime;
}

void printPath(int path[MAX_LINES][MAX_STATIONS], int lastLine, int lastStation) {
    if (lastStation > 0) {
        printPath(path, path[lastLine][lastStation], lastStation - 1);
    }

    printf(" -> Line %d, Station %d", lastLine + 1, lastStation + 1);
}

int main() {
    int a[MAX_LINES][MAX_STATIONS];
    int t[MAX_LINES][MAX_STATIONS - 1];
    int e[MAX_LINES];
    int x[MAX_LINES];
    int path[MAX_LINES][MAX_STATIONS];
    int n;

    // Get user input
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
    int exitTime = assemblyLineScheduling(a, t, e, x, path);

    // Print the result
    printf("Minimum time to exit: %d\n", exitTime);
    printf("Optimal path:");
    printPath(path, path[0][MAX_STATIONS - 1], MAX_STATIONS - 1);
    printf("\n");

    return 0;
}

