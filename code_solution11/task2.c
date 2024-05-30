#include <stdio.h>

int max(int a, int b) {
    if (b <= a) {
        return a;
    }
    return b;
}

void printLongestPath(int lengthM, int lengthN, int matrix[lengthM][lengthN], int helper[lengthM][lengthN], int max) {
    printf("Original Matrix: \n");
    for (int m = 0; m < lengthM; m++) {
        for (int n = 0; n < lengthN; n++) {
            if(matrix[m][n] < 10) {
                printf(" ");
            }
            printf("%d, ", matrix[m][n]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Helper Matrix: \n");
    for (int m = 0; m < lengthM; m++) {
        for (int n = 0; n < lengthN; n++) {
            if(helper[m][n] < 10) {
                printf(" ");
            }
            printf("%d, ", helper[m][n]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Maximum: %d", max);
    printf("\n\n");
}

int longestPath(int lengthM, int lengthN, int matrix[lengthM][lengthN]) {
    int helper[lengthM][lengthN];
    int allTimeMax = 0;

    for (int m = 0; m < lengthM; m++) {
        for (int n = 0; n < lengthN; n++) {
            if (m > 0 && n > 0 && matrix[m][n] > matrix[m - 1][n] && matrix[m][n] > matrix[m][n - 1]) {
                helper[m][n] = 1 + max(helper[m - 1][n], helper[m][n - 1]);

            } else if (m > 0 && matrix[m][n] > matrix[m - 1][n]) {
                helper[m][n] = 1 + helper[m - 1][n];

            } else if (n > 0 && matrix[m][n] > matrix[m][n - 1]) {
                helper[m][n] = 1 + helper[m][n - 1];

            } else {
                helper[m][n] = 1;
            }
            allTimeMax = max(allTimeMax, helper[m][n]);
        }
    }
    printLongestPath(lengthM, lengthN, matrix, helper, allTimeMax);
    return allTimeMax;
}

int main() {
    const int lengthM = 4;
    const int lengthN = 6;
    int matrix[lengthM][lengthN] = {
            {1, 7, 3, 10, 6,  18},
            {3, 2, 5, 6,  9,  16},
            {6, 3, 2, 10, 12, 13},
            {8, 7, 5, 4,  8,  15}
    };
    longestPath(lengthM, lengthN, matrix);
    return 0;
}