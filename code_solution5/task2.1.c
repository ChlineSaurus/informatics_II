#include "stdio.h"

void swap(int array[], int index1, int index2) {
    int tmp = array[index2];
    array[index2] = array[index1];
    array[index1] = tmp;
}

int lomutoPartition(int array[], int leftIndex, int rightIndex) {
    int pivot = array[rightIndex];
    int i = leftIndex - 1;
    for (int j = leftIndex; j < rightIndex; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array, i, j);
        }
    }
    i++;
    swap(array, i, rightIndex);
    return i;
}

int main() {
    int array[] = {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0};
    int n = sizeof(array) / sizeof(array[0]);
    printf("%d \n", lomutoPartition(array, 0, n - 1));
    for (int i = 0; i < n; i++) {
        printf("%i, ", array[i]);
    }
    return 0;
}