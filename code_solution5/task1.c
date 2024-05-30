#include <stdio.h>

int leftChild(int index) {
    return index * 2 + 1;
}

int rightChild(int index) {
    return index * 2 + 2;
}

void swap(int array[], int index1, int index2) {
    int tmp = array[index2];
    array[index2] = array[index1];
    array[index1] = tmp;
}

int controlMaxHeap(int array[], int currentIndex, int length) {
    int leftIndex = leftChild(currentIndex);
    if (leftIndex < length) {
        if (array[currentIndex] < array[leftIndex]) {
            return currentIndex;
        }
        int temp = controlMaxHeap(array, leftIndex, length);
        if (temp != -1) {
            return temp;
        }
    }
    int rightIndex = rightChild(currentIndex);
    if (rightIndex < length) {
        if (array[currentIndex] < array[rightIndex]) {
            return currentIndex;
        }
        int temp = controlMaxHeap(array, rightIndex, length);
        if (temp != -1) {
            return temp;
        }
    }
    return -1;
}

void heapify(int array[], int currentIndex, int length) {
    int leftIndex = leftChild(currentIndex);
    int rightIndex = rightChild(currentIndex);
    int m = currentIndex;
    if (leftIndex < length) {
        if (array[leftIndex] > array[m]) {
            m = leftIndex;
        }
    }
    if (rightIndex < length) {
        if (array[rightIndex] > array[m]) {
            m = rightIndex;
        }
    }
    if (m != currentIndex) {
        swap(array, m, currentIndex);
        heapify(array, m, length);
    }
}

void fixHeap(int array[], int length) {
    int problemIndex = controlMaxHeap(array, 0, length);
    while (problemIndex != -1) {
        heapify(array, problemIndex, length);
        problemIndex = controlMaxHeap(array, 0, length);
    }
    // The loop is necessary to cover cases such as [5, 5, 3, 2, 1, 6].
    // You could also make this part a bit more efficient by comparing the element directly with the parent node.
    // However, for the sake of simplicity, this optimization has not been done.
}

int main() {
    int array[] = {2,3,7,9,1,8, 5};
    int length = sizeof(array) / sizeof(array[0]);
    heapify(array, 0, length);
    for(int i = 0; i < length; i++) {
        printf("%d, ", array[i]);
    }

    return 0;
}
