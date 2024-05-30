#include "stdio.h"
#define NOT_FOUND -1

int findDifference(int value1, int value2) {
    int temp = value1 - value2;
    if (temp > 0) {
        return temp;
    }
    return -1 * (temp);
}

int find_closest(int array[], int length, int searchedElement) {
    if (length <= 0) {
        return NOT_FOUND;
    }
    int left = 0;
    int right = length - 1;
    int closestElement = array[left];
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (findDifference(searchedElement, closestElement)
                > findDifference(searchedElement, array[mid])) {
            closestElement = array[mid];
        }
        if (closestElement == searchedElement) {
            return searchedElement;
        } else if (array[mid] < searchedElement) {
            left = ++mid;
        } else {
            right = --mid;
        }
    }
    return closestElement;
}

int find_closest_recursive(int array[], int left, int right, int searchedElement, int closestElement) {
    if (left >= right) {
        return closestElement;
    }
    // ...


    int closesElement = array[left];
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (findDifference(searchedElement, closestElement)
            > findDifference(searchedElement, array[mid])) {
            closestElement = array[mid];
        }
        if (closestElement == searchedElement) {
            return searchedElement;
        } else if (array[mid] < searchedElement) {
            left = ++mid;
        } else {
            right = --mid;
        }
    }
    return closestElement;
}

int main() {
    int A[] = {2, 5, 10, 12, 16, 17, 25, 32};
    int length = sizeof(A) / sizeof(A[0]);
    int searchedElement = 20;
    int closestNumber = find_closest(A, length, searchedElement);
    printf("Closest number: %d ", closestNumber);
    return 0;
}