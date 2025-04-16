#include <stdio.h>
#include <stdlib.h>

// Structure to represent a job
struct Job {
    int id;
    int profit;
    int deadline;
};

// Function to compare jobs based on profit
int compare(const void* a, const void* b) {
    return ((struct Job*)b)->profit - ((struct Job*)a)->profit;
}

// Function to find the maximum profit job schedule using Greedy method
void jobSequencing(struct Job jobs[], int n) {
    // Sort jobs based on profit in non-increasing order
    qsort(jobs, n, sizeof(struct Job), compare);

    // Array to keep track of time slots
    int timeslots[n];

    // Initialize all slots to be empty
    for (int i = 0; i < n; i++)
        timeslots[i] = -1;

    // Iterate through each job and assign it to the latest possible time slot before its deadline
    for (int i = 0; i < n; i++) {
        for (int j = (jobs[i].deadline - 1); j >= 0; j--) {
            if (timeslots[j] == -1) {
                timeslots[j] = i;
                break;
            }
        }
    }

    // Display the schedule
    printf("Job Schedule:\n");
    printf("Job ID\tProfit\tDeadline\n");
    for (int i = 0; i < n; i++) {
        if (timeslots[i] != -1) {
            printf("%d\t%d\t%d\n", jobs[timeslots[i]].id, jobs[timeslots[i]].profit, jobs[timeslots[i]].deadline);
        }
    }
}

// Driver code
int main() {
    int n;
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    struct Job jobs[n];
    printf("Enter profit, execution time, and deadline for each job:\n");
    for (int i = 0; i < n; i++) {
        jobs[i].id = i + 1;
        printf("Job %d: ", i + 1);
        scanf("%d%d%d", &jobs[i].profit, &jobs[i].deadline, &jobs[i].deadline);
    }

    jobSequencing(jobs, n);

    return 0;
}
