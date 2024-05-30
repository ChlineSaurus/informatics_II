#include <stdio.h>

void insertionSort(int array[], int length) {
    int counter = 0;
    for (int i = 1; i < length; i++) {
        int j = i - 1;
        int current = array[i];
        while (j >= 0 && array[j] > current) {
            array[j + 1] = array[j];
            j--;
            counter++;
        }
        array[j + 1] = current;
    }
    printf("Counter: %d \n", counter);
}

int main() {
    int array[] = {0, 1, 3, 4, 2, 8, 9, 5, 6, 7};
    int length = sizeof(array) / sizeof(array[0]);
    insertionSort(array, length);
    for (int i = 0; i < length; i++) {
        printf("%d \n", array[i]);
    }
    return 0;
}