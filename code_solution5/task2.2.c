#include "stdio.h"

void swap(int array[], int index1, int index2) {
    int tmp = array[index2];
    array[index2] = array[index1];
    array[index1] = tmp;
}

int hoarePartition(int array[], int leftIndex, int rightIndex) {
    int i = leftIndex - 1;
    int j = rightIndex + 1;
    int pivot = array[rightIndex];
    while (1) {
        do {
            j--;
        } while (array[j] > pivot);
        do {
            i++;
        } while (array[i] < pivot);
        if (i >= j) {
            return i;
        }
        swap(array, i, j);
    }
}

int main() {
    int array[] = {7,1,4,6,0,9,2,8,5,3};
    int n = sizeof(array) / sizeof(array[0]);
    printf("%d \n", hoarePartition(array, 0, n - 1));

    for (int i = 0; i < n; i++) {
        printf("%i, ", array[i]);
    }
    return 0;
}
