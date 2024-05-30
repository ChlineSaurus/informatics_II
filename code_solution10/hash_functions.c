#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 150

int hash1(int value) {
    return value % 7;
}

int hash2(int value) {
    return value % 139;
}

int hash3(int value) {
    return value % 149;
}

int hash4(int value) {
    return value * value % N;
}

int hash5(int value) {
    return 97 * value % N;
}

/* Implement */
int insertKeyH1(int *hashTable, int currentElement) {
    int collision = 0;
    int currentIndex = hash1(currentElement);

    while (collision < N) {
        if (hashTable[currentIndex] != -1) {
            collision++;
            currentIndex = (currentIndex + 1) % N;
        } else {
            hashTable[currentIndex] = currentElement;
            break;
        }
    }

    return collision;
}

/* Implement */
int insertKeyH2(int *hashTable, int currentElement) {
    int collision = 0;
    int currentIndex = hash2(currentElement);

    while (collision < N) {
        if (hashTable[currentIndex] != -1) {
            collision++;
            currentIndex = (currentIndex + 1) % N;
        } else {
            hashTable[currentIndex] = currentElement;
            break;
        }
    }

    return collision;
}

int insertKeyH3(int *hashTable, int currentElement) {
    int collision = 0;
    int currentIndex = hash3(currentElement);

    while (collision < N) {
        if (hashTable[currentIndex] != -1) {
            collision++;
            currentIndex = (currentIndex + 1) % N;
        } else {
            hashTable[currentIndex] = currentElement;
            break;
        }
    }

    return collision;
}

int insertKeyH4(int *hashTable, int currentElement) {
    int collision = 0;
    int currentIndex = hash4(currentElement);

    while (collision < N) {
        if (hashTable[currentIndex] != -1) {
            collision++;
            currentIndex = (currentIndex + 1) % N;
        } else {
            hashTable[currentIndex] = currentElement;
            break;
        }
    }

    return collision;
}

int insertKeyH5(int *hashTable, int currentElement) {
    int collision = 0;
    int currentIndex = hash5(currentElement);

    while (collision < N) {
        if (hashTable[currentIndex] != -1) {
            collision++;
            currentIndex = (currentIndex + 1) % N;
        } else {
            hashTable[currentIndex] = currentElement;
            break;
        }
    }

    return collision;
}

/* given */
void initHT(int *HT) {
    for (int i = 0; i < N; ++i) {
        HT[i] = -1;
    }
}

/* given */
void printHT(int *HT) {
    for (int i = 0; i < N; ++i) {
        printf("%d,", HT[i]);
    }
    printf("\n");
}

void printHT2(int *HT) {
    for (int i = 0; i < N; ++i) {
        if (i % 15 == 0) {
            printf("\n");
        }
        if (HT[i] == -1) {
            printf("- ");
        } else {
            printf("X ");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    clock_t start_time, end_time;
    int collisions = 0;
    int HT[N];
    int keys[100] = {73, 148, 29, 214, 101, 47, 92, 201, 164, 88, 133, 19,
                     176, 58, 123, 82, 209, 37, 147, 66, 112, 193, 79, 155,
                     11, 98, 181, 44, 119, 71, 207, 23, 162, 94, 136, 52,
                     185, 67, 144, 32, 199, 77, 120, 17, 158, 26, 191, 49,
                     105, 14, 173, 55, 129, 84, 201, 38, 168, 59, 112, 70,
                     141, 33, 196, 80, 117, 22, 153, 102, 66, 125, 47, 108,
                     31, 177, 14, 86, 172, 41, 95, 164, 75, 188, 57, 133,
                     16, 121, 74, 144, 39, 109, 168, 81, 201, 53, 97, 24,
                     137, 62, 116, 9};

    initHT(HT);

    start_time = clock();
    for (int i = 0; i < 100; ++i) {
        collisions += insertKeyH1(HT, keys[i]);
    }
    end_time = clock();

    printHT2(HT);
    printf("H1: completed in %.2f clocks, %d collisions\n",
           (double) (end_time - start_time), collisions);

    /* improved hash function */
    initHT(HT);
    collisions = 0;

    start_time = clock();
    for (int i = 0; i < 100; ++i) {
        collisions += insertKeyH2(HT, keys[i]);
    }
    end_time = clock();

    printHT2(HT);
    printf("H2: completed in %.2f clocks, %d collisions\n\n",
           (double) (end_time - start_time), collisions);

    /* improved hash function 2 */
    initHT(HT);
    collisions = 0;

    start_time = clock();
    for (int i = 0; i < 100; ++i) {
        collisions += insertKeyH3(HT, keys[i]);
    }
    end_time = clock();

    printHT2(HT);
    printf("H3: completed in %.2f clocks, %d collisions\n\n",
           (double) (end_time - start_time), collisions);

    /* improved hash function 2 */
    initHT(HT);
    collisions = 0;

    start_time = clock();
    for (int i = 0; i < 100; ++i) {
        collisions += insertKeyH4(HT, keys[i]);
    }
    end_time = clock();

    printHT2(HT);
    printf("H4: completed in %.2f clocks, %d collisions\n\n",
           (double) (end_time - start_time), collisions);

    /* improved hash function 2 */
    initHT(HT);
    collisions = 0;

    start_time = clock();
    for (int i = 0; i < 100; ++i) {
        collisions += insertKeyH5(HT, keys[i]);
    }
    end_time = clock();

    printHT2(HT);
    printf("H5: completed in %.2f clocks, %d collisions\n\n",
           (double) (end_time - start_time), collisions);

    return 0;
}
