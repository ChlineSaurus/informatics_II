#include <stdio.h>

int max(int a, int b) {
    if (b <= a) {
        return a;
    }
    return b;
}

int cost(int val, int len, int c) {
    int factor = len - c;
    return val * factor;
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

int maxCost(int array[], int len) {
    int helper[len + 1][len + 1];
    int allTimeMax = 0;

    for (int m = 0; m <= len; m++) {
        for (int n = 0; m + n <= len; n++) {
            if (m > 0 && n > 0) {
                helper[m][n] = max(helper[m - 1][n]+ cost(array[m - 1], len, len - m - n),
                                   helper[m][n - 1]+ cost(array[len - n], len, len - m - n));
            } else if (m > 0) {
                helper[m][n] = helper[m - 1][n]+cost(array[m - 1], len, len - m - n);
            } else if (n > 0) {
                helper[m][n] = helper[m][n - 1]+cost(array[len - n], len, len - m - n);
            } else {
                helper[m][n] = 0;
            }
            allTimeMax = max(allTimeMax, helper[m][n]);
        }
    }
    return allTimeMax;
}

int main() {
    int array[] = {3, 2, 4, 1};
    maxCost(array, sizeof(array) / sizeof(array[0]));
    return 0;
}