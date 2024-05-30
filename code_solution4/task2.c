
#include <printf.h>

int findMaxOverlap(int array[], int left, int right) {
    int mid = left + (right - left) / 2;

    int leftTotalSum = array[mid];
    int leftMaxOverlap = array[mid];
    for (int i = mid - 1; i >= left; i--) {
        leftTotalSum += array[i];
        if (leftTotalSum > leftMaxOverlap) {
            leftMaxOverlap = leftTotalSum;
        }
    }

    int rightTotalSum = array[mid + 1];
    int rightMaxOverlap = array[mid + 1];
    for (int i = mid + 2; i <= right; i++) {
        rightTotalSum += array[i];
        if (rightTotalSum > rightMaxOverlap) {
            rightMaxOverlap = rightTotalSum;
        }
    }
    return leftMaxOverlap + rightMaxOverlap;
}

int findMaxSubarray(int array[], int left, int right) {
    if (left >= right) {
        return array[left];
    }

    int mid = left + (right - left) / 2;
    int leftMaximum = findMaxSubarray(array, left, mid);
    int rightMaximum = findMaxSubarray(array, mid + 1, right);
    int overlapMaximum = findMaxOverlap(array, left, right);

    int overallMaximum = leftMaximum;
    if (overallMaximum < rightMaximum) {
        overallMaximum = rightMaximum;
    }
    if (overallMaximum < overlapMaximum) {
        overallMaximum = overlapMaximum;
    }
    return overallMaximum;
}

int main() {
    int array[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int length = sizeof(array) / sizeof(array[0]);
    printf("Max Subarray: %d", findMaxSubarray(array, 0, length - 1));
    return 0;
}