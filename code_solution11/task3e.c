#include <stdio.h>

int max(int a, int b) {
    if (b <= a) {
        return a;
    }
    return b;
}

void copyArray(int from[], int to[], int numberItems) {
    for (int i = 0; i < numberItems; i++) {
        to[i] = from[i];
    }
}

int knapsack(int weight[], int value[], int capacity, int numberItems) {
    int previous[capacity + 1];
    int current[capacity + 1];

    for (int n = 0; n <= capacity; n++) {
        if (n < weight[0]) {
            previous[n] = 0;
        } else {
            previous[n] = value[0];
        }
    }

    for (int m = 1; m < numberItems; m++) {
        for (int n = 0; n <= capacity; n++) {
            if (n < weight[m]) {
                current[n] = previous[n];
            } else {
                current[n] = max(previous[n], previous[n - weight[m]] + value[m]);
            }
        }
        copyArray(current, previous, capacity + 1);
    }

    return current[capacity];
}

int main() {
    int weight[] = {2, 4, 5, 3, 9};
    int value[] = {3, 5, 8, 4, 10};
    int numberItems = sizeof(weight) / sizeof(weight[0]);
    int weightMaximum = 20;

    printf("%d", knapsack(weight, value, weightMaximum, numberItems));

    return 0;
}