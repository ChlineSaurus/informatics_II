#include <stdio.h>

int max(int a, int b) {
    if (b <= a) {
        return a;
    }
    return b;
}

int deletionCost(int currentValue, int totalLength, int currentLength) {
    int factor = totalLength - currentLength;
    return currentValue * factor;
}

int printMaxCost(int max, int length, int helper[length + 1][length + 1]) {
    printf("Helper Matrix: \n");
    for (int m = 0; m <= length; m++) {
        for (int n = 0; n <= length; n++) {
            if (m + n > length) {
                printf(" X, ");
            } else {
                if (helper[m][n] < 10) {
                    printf(" ");
                }
                printf("%d, ", helper[m][n]);
            }
        }
        printf("\n");
    }
    printf("\n Total Max: %d", max);
    printf("\n\n");
}

int maxCost(int array[], int length) {
    int helper[length + 1][length + 1];
    int subarrayLength, leftIndex, rightIndex;
    int allTimeMax = 0;

    for (int leftDeletions = 0; leftDeletions <= length; leftDeletions++) {
        for (int rightDeletions = 0; leftDeletions + rightDeletions <= length; rightDeletions++) {
            // Important: The current deletion didn't happen yet.
            // Example: we are filling in the max cost after 2 left deletions, however, only the first deletion already
            // happened, so the element we want to consider in the array is at index 1.
            leftIndex = leftDeletions - 1;
            rightIndex = length - rightDeletions;
            subarrayLength = length - leftDeletions - rightDeletions;

            if (leftDeletions > 0 && rightDeletions > 0) {
                helper[leftDeletions][rightDeletions] = max(
                        helper[leftDeletions - 1][rightDeletions]
                        + deletionCost(array[leftIndex], length, subarrayLength),
                        helper[leftDeletions][rightDeletions - 1]
                        + deletionCost(array[rightIndex], length, subarrayLength)
                );
            } else if (leftDeletions > 0) {
                helper[leftDeletions][rightDeletions] = helper[leftDeletions - 1][rightDeletions]
                                                        +
                                                        deletionCost(array[leftIndex], length, subarrayLength);
            } else if (rightDeletions > 0) {
                helper[leftDeletions][rightDeletions] = helper[leftDeletions][rightDeletions - 1]
                                                        +
                                                        deletionCost(array[rightIndex], length, subarrayLength);
            } else {
                helper[leftDeletions][rightDeletions] = 0;
            }
            allTimeMax = max(allTimeMax, helper[leftDeletions][rightDeletions]);
        }
    }
    printMaxCost(allTimeMax, length, helper);
    return allTimeMax;
}

int main() {
    int array[] = {3, 2, 4, 1};
    maxCost(array, sizeof(array) / sizeof(array[0]));
    return 0;
}