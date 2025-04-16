#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 4

// State space tree node
struct Node {
    // Stores the parent node of the current node
    // Helps in tracing the path when the answer is found
    struct Node* parent;

    // Contains the cost for ancestor nodes
    // Including the current node
    int pathCost;

    // Contains the least promising cost
    int cost;

    // Contains the worker number
    int workerID;

    // Contains the Job ID
    int jobID;

    // Boolean array assigned will contain
    // Info about available jobs
    int assigned[N];
};

// Function to allocate a new search tree node
// Here, Person x is assigned to job y
struct Node* newNode(int x, int y, int assigned[], struct Node* parent) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    for (int j = 0; j < N; j++)
        node->assigned[j] = assigned[j];
    node->assigned[y] = 1;

    node->parent = parent;
    node->workerID = x;
    node->jobID = y;

    return node;
}

// Function to calculate the least promising cost
// Of node after worker x is assigned to job y.
int calculateCost(int costMatrix[N][N], int x, int y, int assigned[]) {
    int cost = 0;

    // To store unavailable jobs
    int available[N];
    for (int i = 0; i < N; i++)
        available[i] = 1;

    // Start from the next worker
    for (int i = x + 1; i < N; i++) {
        int min = INT_MAX, minIndex = -1;

        // Do for each job
        for (int j = 0; j < N; j++) {
            // If the job is unassigned
            if (!assigned[j] && available[j] && costMatrix[i][j] < min) {
                // Store the job number
                minIndex = j;

                // Store the cost
                min = costMatrix[i][j];
            }
        }

        // Add the cost of the next worker
        cost += min;

        // The job becomes unavailable
        available[minIndex] = 0;
    }

    return cost;
}

// Comparison object to be used to order the heap
struct comp {
    int operator()(const struct Node* lhs, const struct Node* rhs) const {
        return lhs->cost > rhs->cost;
    }
};

// Print Assignments
void printAssignments(struct Node* min) {
    if (min->parent == NULL)
        return;

    printAssignments(min->parent);
    printf("Assign Worker %c to Job %d\n", min->workerID + 'A', min->jobID);
}

// Finds the minimum cost using Branch and Bound.
int findMinCost(int costMatrix[N][N]) {
    // Create an array of pointers to store live nodes of
    // The search tree;
    struct Node* pq[N * N];
    int pqSize = 0;

    // Initialize the array to a dummy node with cost 0
    int assigned[N] = {0};
    struct Node* root = newNode(-1, -1, assigned, NULL);
    root->pathCost = root->cost = 0;
    root->workerID = -1;

    // Add the dummy node to the array of live nodes;
    pq[pqSize++] = root;

    // Find a live node with the least estimated cost,
    // Add its children to the array of live nodes, and
    // Finally delete it from the array.
    while (pqSize > 0) {
        // Find a live node with the least estimated cost
        struct Node* min = pq[--pqSize];

        // i stores the next worker
        int i = min->workerID + 1;

        // If all workers are assigned a job
        if (i == N) {
            printAssignments(min);
            return min->cost;
        }

        // Do for each job
        for (int j = 0; j < N; j++) {
            // If unassigned
            if (!min->assigned[j]) {
                // Create a new tree node
                struct Node* child = newNode(i, j, min->assigned, min);

                // Cost for ancestor nodes, including the current node
                child->pathCost = min->pathCost + costMatrix[i][j];

                // Calculate its lower bound
                child->cost = child->pathCost + calculateCost(costMatrix, i, j, child->assigned);

                // Add child to the array of live nodes;
                pq[pqSize++] = child;
            }
        }
    }
}

// Driver code
int main() {
    // x-coordinate represents a Worker
    // y-coordinate represents a Job
    int costMatrix[N][N] = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}};

    printf("\nOptimal Cost is %d\n", findMinCost(costMatrix));

    return 0;
}
