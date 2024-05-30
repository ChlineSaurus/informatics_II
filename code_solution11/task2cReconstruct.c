#include <stdio.h>
#include "stdlib.h"

#define heapSize 24

struct heapNode {
    int m;
    int n;
    int value;
};

struct heap {
    struct heapNode *array[heapSize];
    int lastIndex;
};

int leftChild(int index) {
    return index * 2 + 1;
}

int rightChild(int index) {
    return index * 2 + 2;
}

void swap(struct heap *heap, int index1, int index2) {
    struct heapNode *temp = heap->array[index2];
    heap->array[index2] = heap->array[index1];
    heap->array[index1] = temp;
}

void heapify(struct heap *heap, int currentIndex) {
    int leftIndex = leftChild(currentIndex);
    int rightIndex = rightChild(currentIndex);
    int m = currentIndex;
    if (leftIndex <= heap->lastIndex) {
        if (heap->array[leftIndex]->value < heap->array[m]->value) {
            m = leftIndex;
        }
    }
    if (rightIndex <= heap->lastIndex) {
        if (heap->array[rightIndex]->value < heap->array[m]->value) {
            m = rightIndex;
        }
    }
    if (m != currentIndex) {
        swap(heap, m, currentIndex);
        heapify(heap, m);
    }
}

struct heap *createHeap(int lengthM, int lengthN, int matrix[lengthM][lengthN]) {
    struct heap *heap = malloc(sizeof(struct heap));
    heap->lastIndex = heapSize - 1;
    int i = 0;

    for (int m = 0; m < lengthM; m++) {
        for (int n = 0; n < lengthN; n++) {
            heap->array[i] = malloc(sizeof(struct heapNode));
            heap->array[i]->m = m;
            heap->array[i]->n = n;
            heap->array[i]->value = matrix[m][n];
            i++;
        }
    }

    for (int j = heapSize / 2 + 1; j >= 0; j--) {
        heapify(heap, j);
    }
    return heap;
}

struct heapNode *pop(struct heap *heap) {
    swap(heap, 0, heap->lastIndex);
    heap->lastIndex--;
    heapify(heap, 0);
    return heap->array[heap->lastIndex + 1];
}

void printVisitOrder(struct heap *heap) {
    struct heapNode *currentNode;
    while (heap->lastIndex >= 0) {
        currentNode = pop(heap);
        printf("M: %d, N: %d, Value: %d\n", currentNode->m, currentNode->n, currentNode->value);
    }
}

void printLongestPath(int lengthM, int lengthN, int matrix[lengthM][lengthN], int helper[lengthM][lengthN], int max) {
    printf("Original Matrix: \n");
    for (int m = 0; m < lengthM; m++) {
        for (int n = 0; n < lengthN; n++) {
            if (matrix[m][n] < 10) {
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
            if (helper[m][n] < 10) {
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

int max(int array[], int length) {
    if (length <= 0) {
        return 0;
    }
    int maximum = array[0];
    for (int i = 1; i < length; i++) {
        if (array[i] > maximum) {
            maximum = array[i];
        }
    }
    return maximum;
}

void reconstruct(int lengthM, int lengthN, int matrix[lengthM][lengthN], int helper[lengthM][lengthN], int max) {
    printf("Reconstruction of longest path: \n");
    int m, n;
    for (m = 0; m < lengthM; m++) {
        for (n = 0; n < lengthN; n++) {
            if (helper[m][n] == max) {
                break;
            }
        }
        if (helper[m][n] == max) {
            break;
        }
    }

    // Not correct, we would also need to check that we see a decrease in value in the original matrix
    // (However, only if there are multiple options)
    while (max != 0) {
        printf("M: %d, N: %d, Value: %d, Action: ", m, n, matrix[m][n]);
        if (m > 0 && helper[m][n] == helper[m - 1][n] + 1) {
            printf("Down");
            m--;
        } else if (m < lengthM - 1 && helper[m][n] == helper[m + 1][n] + 1) {
            printf("Up");
            m++;
        } else if (n > 0 && helper[m][n] == helper[m][n - 1] + 1) {
            printf("Left");
            n--;
        } else {
            printf("Right");
            n++;
        }
        max--;
        printf("\n");
    }
}

int longestPath(int lengthM, int lengthN, int matrix[lengthM][lengthN]) {
    struct heap *heap = createHeap(lengthM, lengthN, matrix);
    int helper[lengthM][lengthN];
    int allTimeMax = 0;

    struct heapNode *currentNode;
    int possibleValue[5];
    int numberOfPossibleValue, m, n;

    while (heap->lastIndex >= 0) {
        currentNode = pop(heap);
        m = currentNode->m;
        n = currentNode->n;

        possibleValue[0] = 1;
        numberOfPossibleValue = 1;


        if (m > 0 && matrix[m][n] > matrix[m - 1][n]) {
            possibleValue[numberOfPossibleValue] = 1 + helper[m - 1][n];
            numberOfPossibleValue++;
        }
        if (n > 0 && matrix[m][n] > matrix[m][n - 1]) {
            possibleValue[numberOfPossibleValue] = 1 + helper[m][n - 1];
            numberOfPossibleValue++;
        }
        if (m < (lengthM - 1) && matrix[m][n] > matrix[m + 1][n]) {
            possibleValue[numberOfPossibleValue] = 1 + helper[m + 1][n];
            numberOfPossibleValue++;
        }
        if (n < (lengthN - 1) && matrix[m][n] > matrix[m][n + 1]) {
            possibleValue[numberOfPossibleValue] = 1 + helper[m][n + 1];
            numberOfPossibleValue++;
        }
        helper[m][n] = max(possibleValue, numberOfPossibleValue);
        if (allTimeMax < helper[m][n]) {
            allTimeMax = helper[m][n];
        }
    }

    printLongestPath(lengthM, lengthN, matrix, helper, allTimeMax);
    reconstruct(lengthM, lengthN, matrix, helper, allTimeMax);
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
    struct heap *heap = createHeap(lengthM, lengthN, matrix);
    printVisitOrder(heap);
    printf("\n");
    longestPath(lengthM, lengthN, matrix);
    return 0;
}