#include <stdio.h>

void printLongestSequence(int array[], int helper[], int parent[], int length, int maxIndex) {
    printf("Original Array: ");
    for (int i = 0; i < length; i++) {
        printf("%d, ", array[i]);
    }
    printf("\n");

    printf("Helper Array: ");
    for (int i = 0; i < length; i++) {
        printf("%d, ", helper[i]);
    }
    printf("\n");

    printf("Parent Array: ");
    for (int i = 0; i < length; i++) {
        printf("%d, ", parent[i]);
    }
    printf("\n");

    printf("Max length: %d\n", helper[maxIndex]);

    printf("Max Subsequence: ");
    while (maxIndex >= 0) {
        printf("%d, ", array[maxIndex]);
        maxIndex = parent[maxIndex];
    }
    printf("\n\n");
}

int longestSequence(int array[], int length) {
    int helper[length];
    int parent[length];
    int legalPreviousMax;
    int allTimeMaxIndex = 0;

    for (int i = 0; i < length; i++) {
        legalPreviousMax = 0;
        for (int j = 0; j < i; j++) {
            if (array[j] <= array[i] && legalPreviousMax < helper[j]) {
                legalPreviousMax = helper[j];
                parent[i] = j;
            }
        }
        if (legalPreviousMax == 0) {
            helper[i] = 1;
            parent[i] = -1;
        } else {
            helper[i] = legalPreviousMax + 1;
            if (helper[allTimeMaxIndex] < legalPreviousMax + 1) {
                allTimeMaxIndex = i;
            }
        }
    }
    printLongestSequence(array, helper, parent, length, allTimeMaxIndex);
    return array[allTimeMaxIndex];
}

int main() {
    int array1[] = {5, 10, 7, 4, 8, 9, 2, 10};
    longestSequence(array1, sizeof(array1) / sizeof(array1[0]));
    int array2[] = {7, 10, 4, 9, 7, 10, 8, 12};
    longestSequence(array2, sizeof(array2) / sizeof(array2[0]));
    return 0;
}