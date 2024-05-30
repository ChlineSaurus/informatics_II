#include <stdio.h>

void swap(int array[], int index1, int index2) {
    int tmp = array[index2];
    array[index2] = array[index1];
    array[index1] = tmp;
}

void bubbleSort(int array[], int length) {
    long counter = 0;
    for (int i = length - 1; i > 0; i--) {
        for (int j = 1; j <= i; j++) {
            if (array[j] < array[j - 1]) {
                swap(array, j, j - 1 );
            }
            counter++;
        }
    }
    printf("Counter: %ld \n", counter);
}

int main() {
    int length = 100000;
    bubbleSort(array, length);
    return 0;
}