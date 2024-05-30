
int linear_search(int A[], int n, int t) {
    for(int i = 0; i < n; i++) {
        if (A[i] == t) {
            return 1; // found in the array
        }
    }
    return 0; // not found
}

int binary_search(int A[], int n, int t) {
    int l = 0, r = n - 1;
    int mid;
    while (l <= r) {
        mid = (l + (r - l) / 2);
        if (A[mid] == t) {
            return 1;
        } else if(A[mid] > t) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return 0;
}

int binary_search_recursive(int A[], int l, int r, int t) {
    if (l > r) {
        return 0; // Target not found
    }
    int mid = l + (r - l) / 2;
    if (A[mid] == t) {
        return 1;
    } else if (A[mid] > t) {
        return binary_search_recursive(A, l, mid - 1, t); // Search in the left half
    } else {
        return binary_search_recursive(A, mid + 1, r, t); // Search in the right half
    }
}