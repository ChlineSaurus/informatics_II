#include <stdio.h>
#include <stdlib.h>

#define N 10
#define notFound (-1)
#define true 1
#define false 0

struct cuckooTable {
    int table1[N];
    int table2[N];
};

int hash1(int value) {
    return value % N;
}

int hash2(int value) {
    return (value / 10) % N;
}

int couldFindLoop(struct cuckooTable *cuckooTable, int currentElement) {
    int visitedPositions[N * 2];
    for(int i = 0; i < 2 * N; i++) {
        visitedPositions[i] = 0;
    }
    int currentTable = 1;
    int currentPos = 0;
    int count = 0;

    while (count < N * 2) {
        if (currentTable == 1) {
            currentPos = hash1(currentElement);
            if (visitedPositions[currentPos] == 1) {
                return true;
            }
            visitedPositions[currentPos] = 1;
            currentElement = cuckooTable->table1[currentPos];
            currentTable = 2;
        } else {
            currentPos = hash2(currentElement);
            if (visitedPositions[N + currentPos] == 1) {
                return true;
            }
            visitedPositions[N + currentPos] = 1;
            currentElement = cuckooTable->table2[currentPos];
            currentTable = 1;
        }
        if (currentElement == -1) {
            break;
        }
        count++;
    }

    return false;
}

int cuckooInsertKey(struct cuckooTable *cuckooTable, int insertKey) {
    int hashValue;
    int currentValue = insertKey;
    int temp;
    while (1) {
        for (int i = 0; i < 30; i++) {
            hashValue = hash1(currentValue);
            temp = cuckooTable->table1[hashValue];
            cuckooTable->table1[hashValue] = currentValue;
            if (temp == -1) {
                return 1;
            }
            hashValue = hash2(temp);
            currentValue = cuckooTable->table2[hashValue];
            cuckooTable->table2[hashValue] = temp;
            if (currentValue == -1) {
                return 2;
            }
        }
        if (couldFindLoop(cuckooTable, currentValue) == true) {
            return notFound;
        }
    }
}

int cuckooInsertKeyNoLoopProtection(struct cuckooTable *cuckooTable, int insertKey) {
    int hashValue;
    int currentValue = insertKey;
    int temp;

    while (1) {
        hashValue = hash1(currentValue);
        temp = cuckooTable->table1[hashValue];
        cuckooTable->table1[hashValue] = currentValue;
        if (temp == -1) {
            return 1;
        }
        hashValue = hash2(temp);
        currentValue = cuckooTable->table2[hashValue];
        cuckooTable->table2[hashValue] = temp;
        if (currentValue == -1) {
            return 2;
        }
    }
}

void printCuckooTable(struct cuckooTable *cuckooTable) {
    printf("Table 1: ");
    for (int i = 0; i < N; i++) {
        printf("%d, ", cuckooTable->table1[i]);
    }
    printf("\n");
    printf("Table 2: ");
    for (int i = 0; i < N; i++) {
        printf("%d, ", cuckooTable->table2[i]);
    }
    printf("\n\n");
}

void cuckooPrintKey(struct cuckooTable *cuckooTable, int searchKey) {
    if (cuckooTable->table1[hash1(searchKey)] == searchKey) {
        printf("Table 1 at Index %d\n", hash1(searchKey));
    } else if (cuckooTable->table2[hash2(searchKey)] == searchKey) {
        printf("Table 2 at Index %d\n", hash2(searchKey));
    } else {
        printf("Not found");
    }
}

int cuckooGetKey(struct cuckooTable *cuckooTable, int searchKey, int *tableFoundIn) {
    if (cuckooTable->table1[hash1(searchKey)] == searchKey) {
        *tableFoundIn = 1;
        return hash1(searchKey);
    } else if (cuckooTable->table2[hash2(searchKey)] == searchKey) {
        *tableFoundIn = 2;
        return hash2(searchKey);
    } else {
        *tableFoundIn = notFound;
        return -1;
    }
}

void initCuckooTable(struct cuckooTable *cuckooTable) {
    for (int i = 0; i < N; i++) {
        cuckooTable->table1[i] = -1;
        cuckooTable->table2[i] = -1;
    }
}

int main() {
    struct cuckooTable *aCuckooTable = malloc(sizeof(struct cuckooTable));
    initCuckooTable(aCuckooTable);
    printCuckooTable(aCuckooTable);

    int array[] = {1, 2, 3, 4, 11, 14};
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        cuckooInsertKey(aCuckooTable, array[i]);
        printCuckooTable(aCuckooTable);
    }

    initCuckooTable(aCuckooTable);
    printf("Last insertion in table: %d \n", cuckooInsertKey(aCuckooTable, 0));
    printf("Last insertion in table: %d \n", cuckooInsertKey(aCuckooTable, 100));
    printf("Last insertion in table: %d \n", cuckooInsertKey(aCuckooTable, 200));
    printCuckooTable(aCuckooTable);


    return 0;
}