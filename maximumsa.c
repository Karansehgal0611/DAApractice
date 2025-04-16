#include <stdio.h>
#include <limits.h>

typedef struct {
    int start;
    int end;
    int sum;
} MaxSubarray;

MaxSubarray maxCrossingSum(int arr[], int low, int mid, int high) {
    MaxSubarray result;

    int leftSum = INT_MIN;
    int sum = 0;
    int leftIndex = mid;

    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum > leftSum) {
            leftSum = sum;
            leftIndex = i;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    int rightIndex = mid + 1;

    for (int i = mid + 1; i <= high; i++) {
        sum += arr[i];
        if (sum > rightSum) {
            rightSum = sum;
            rightIndex = i;
        }
    }

    result.start = leftIndex;
    result.end = rightIndex;
    result.sum = leftSum + rightSum;

    return result;
}

MaxSubarray maxSubarraySum(int arr[], int low, int high) {
    MaxSubarray result;

    if (low == high) {
        result.start = low;
        result.end = high;
        result.sum = arr[low];
        return result;
    }

    int mid = (low + high) / 2;

    MaxSubarray left = maxSubarraySum(arr, low, mid);
    MaxSubarray right = maxSubarraySum(arr, mid + 1, high);
    MaxSubarray cross = maxCrossingSum(arr, low, mid, high);

    if (left.sum >= right.sum && left.sum >= cross.sum) {
        return left;
    } else if (right.sum >= left.sum && right.sum >= cross.sum) {
        return right;
    } else {
        return cross;
    }
}

int main() {
    int n;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    MaxSubarray maxSub = maxSubarraySum(arr, 0, n - 1);

    printf("Maximum subarray sum: %d\n", maxSub.sum);
    printf("Starting position: %d\n", maxSub.start);
    printf("Ending position: %d\n", maxSub.end);

    return 0;
}

