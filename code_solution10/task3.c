#include <stdio.h>
#include <stdlib.h>

#define N 10
#define success 1
#define failure 0

int hash(int value) {
    return (value + 4) % N;
}

int insertKey(int *hashTable, int insertKey) {
    int collision = 0;
    int currentIndex = hash(insertKey);

    while (collision < N) {
        if (hashTable[currentIndex] != -1) {
            collision++;
            currentIndex = (currentIndex + 1) % N;
        } else {
            hashTable[currentIndex] = insertKey;
            break;
        }
    }

    if (collision == N) {
        return failure;
    }

    return success;
}

int deleteKey(int *hashTable, int deleteKey) {
    int hashValue = hash(deleteKey);
    int shift = 0;
    int currentIndex = hashValue;

    while (hashTable[currentIndex] != deleteKey) {
        if (shift >= N || hashTable[currentIndex] == -1) {
            return failure;
        }
        shift++;
        currentIndex = (hashValue + shift) % N;
    }

    int walker = currentIndex;
    int runner = (currentIndex + 1) % N;

    while (hashTable[runner] != -1 && runner != currentIndex) {
        if (hash(hashTable[runner]) <= walker) {
            if (walker < runner || (runner < hash(hashTable[runner]))) {
                hashTable[walker] = hashTable[runner];
                walker = runner;
            }
        }
        runner = (runner + 1) % N;
    }
    hashTable[walker] = -1;
    return success;
}
//overwrite the last value we deleted/replaced with where currently at
//remember this place as the new spot we want to overwrite
                /*
                 * Check that we not only pass the if-condition thanks to the modulo operation:
                 * We do this by saying, that if we experience the case, that the runner is smaller than the walker
                 * (and therefore already run into the modulo operation), we only do the overwriting, if the hash value
                 * of the value at the runner index would instead belong the right side of the runner index.
                 */


void initHashTable(int *HT) {
    for (int i = 0; i < N; ++i) {
        HT[i] = -1;
    }
}

void printHT(int *HT) {
    printf("Hash Table: ");
    for (int i = 0; i < N; ++i) {
        printf("%d, ", HT[i]);
    }
    printf("\n");
}

void fillHashTable(int hashTable[], int array[], int length) {
    for (int i = 0; i < length; i++) {
        insertKey(hashTable, array[i]);
    }
}

int main(int argc, char *argv[]) {
    int hashTable[N];
    initHashTable(hashTable);
    int array[] = {32, 52, 33, 74, 96};
    fillHashTable(hashTable, array, sizeof(array) / sizeof(array[0]));
    printHT(hashTable);
    deleteKey(hashTable, 32);
    printHT(hashTable);
    printf("\n");

    initHashTable(hashTable);
    int array2[] = {32, 52, 33, 74, 95};
    fillHashTable(hashTable, array2, sizeof(array2) / sizeof(array2[0]));
    printHT(hashTable);
    deleteKey(hashTable, 32);
    printHT(hashTable);
    printf("\n");

    initHashTable(hashTable);
    int array3[] = {32, 52, 42, 74, 95};
    fillHashTable(hashTable, array3, sizeof(array3) / sizeof(array3[0]));
    printHT(hashTable);
    deleteKey(hashTable, 32);
    printHT(hashTable);
    printf("\n");

    initHashTable(hashTable);
    int array4[] = {32, 51, 31, 11, 21, 41};
    fillHashTable(hashTable, array4, sizeof(array4) / sizeof(array4[0]));
    printHT(hashTable);
    deleteKey(hashTable, 32);
    printHT(hashTable);
    printf("\n");

    return 0;
}
