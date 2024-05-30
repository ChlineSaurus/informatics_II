#include <stdio.h>

int max(int a, int b) {
    if(b <= a) {
        return a;
    }
    return b;
}

int longestSequence(int array[], int length) {
    int helper[length];
    int allTimeMax = 0;
    int legalPreviousMax;

    for(int i = 0; i < length; i++) {
        legalPreviousMax = 0;
        for(int j = 0; j < i; j++) {
            if(array[j] <= array[i]) {
                legalPreviousMax = max(legalPreviousMax, helper[j]);
            }
        }
        if(legalPreviousMax == 0) {
            helper[i] = 1;
        } else {
            helper[i] = legalPreviousMax + 1;
            allTimeMax = max(allTimeMax, legalPreviousMax + 1);
        }
    }
    return allTimeMax;
}

int main() {
    int array1[] = {5, 10, 7, 4, 8, 9, 2, 10};
    printf("Array A: %d\n", longestSequence(array1, sizeof(array1) / sizeof(array1[0])));
    int array2[] = {7, 10, 4, 9, 7, 10, 8, 12};
    printf("Array B: %d\n", longestSequence(array2, sizeof(array2) / sizeof(array2[0])));
    return 0;
}