#include <stdio.h>

int max(int a, int b) {
    if (b <= a) {
        return a;
    }
    return b;
}

void printKnapsack(int capacity, int numberItems, int helper[numberItems][capacity + 1]) {
    printf("Helper Matrix: \n");
    for (int m = 0; m < numberItems; m++) {
        for (int n = 0; n <= capacity; n++) {
            if (helper[m][n] < 10) {
                printf(" ");
            }
            printf("%d, ", helper[m][n]);
        }
        printf("\n");
    }
    printf("\n");
}

void reconstruct(int weight[], int capacity, int numberItems, int helper[numberItems][capacity + 1]) {
    int n = capacity;
    int m = numberItems - 1;
    printf("Reconstruction: \n");
    while (m >= 0) {
        printf("Item at Index %d: ", m);
        if(helper[m][n] == helper[m-1][n]) {
            printf("Not included");
        } else {
            printf("Included");
            n = n - weight[m];
        }
        printf("\n");
        m--;
    }
}

int knapsack(int weight[], int value[], int capacity, int numberItems) {
    int helper[numberItems][capacity + 1];

    for (int n = 0; n <= capacity; n++) {
        if (n < weight[0]) {
            helper[0][n] = 0;
        } else {
            helper[0][n] = value[0];
        }
    }

    for (int m = 1; m < numberItems; m++) {
        for (int n = 0; n <= capacity; n++) {
            if (n < weight[m]) {
                helper[m][n] = helper[m - 1][n];
            } else {
                helper[m][n] = max(helper[m - 1][n], helper[m - 1][n - weight[m]] + value[m]);
            }
        }
    }
    printKnapsack(capacity, numberItems, helper);
    reconstruct(weight, capacity, numberItems, helper);

    return helper[numberItems - 1][capacity];
}

int main() {
    int weight[] = {1, 3, 3, 4};
    int value[] = {2, 4, 4, 5};
    int numberItems = sizeof(weight) / sizeof(weight[0]);
    int weightMaximum = 6;

    knapsack(weight, value, weightMaximum, numberItems);

    return 0;
}