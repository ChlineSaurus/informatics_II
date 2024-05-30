#include <stdio.h>

struct item {
    char *name;
    int weight;
    int value;
};

int max(int a, int b) {
    if (b <= a) {
        return a;
    }
    return b;
}

void printKnapsack(int capacity, int numberItems, int helper[numberItems+1][capacity + 1]) {
    printf("\nHelper Matrix: \n");
    for (int m = 0; m <= numberItems; m++) {
        for (int n = 0; n <= capacity; n++) {
            if (helper[m][n] < 10) {
                printf(" ");
            }
            printf("%d, ", helper[m][n]);
        }
        printf("\n");
    }
    printf("\n");
}

void result(struct item possibleItems[], int capacity, int numberItems, int helper[numberItems][capacity + 1], int maximum) {
    int currentWeight = capacity;
    int currentItemIndex = numberItems;
    struct item currentItem;

    printf("We can get a maximum value of %d with the following combination:\n", maximum);
    while (currentItemIndex > 0) {
        currentItem = possibleItems[currentItemIndex-1];
        if(helper[currentItemIndex][currentWeight] == helper[currentItemIndex-1][currentWeight]) {
            printf("- Not included: ");
        } else {
            printf("+ Included: ");
            currentWeight = currentWeight - currentItem.weight;
        }
        printf("%s with weight %d and value %d", currentItem.name, currentItem.weight, currentItem.value);

        printf("\n");
        currentItemIndex--;
    }
}

int knapsack(struct item possibleItems[], int capacity, int numberItems) {
    int helper[numberItems + 1][capacity + 1];

    for (int n = 0; n <= capacity; n++) {
        helper[0][n] = 0;
    }

    struct item currentItem;
    // Row zero is with no item => the first item is in row one (similar to 1 indexing)
    for (int currentItemIndex = 1; currentItemIndex <= numberItems; currentItemIndex++) {
        // However, in the possibleItem we have zero indexing
        currentItem = possibleItems[currentItemIndex - 1];
        for (int currentWeight = 0; currentWeight <= capacity; currentWeight++) {
            if (currentWeight < currentItem.weight) {
                helper[currentItemIndex][currentWeight] = helper[currentItemIndex - 1][currentWeight];
            } else {
                helper[currentItemIndex][currentWeight] = max(
                        helper[currentItemIndex - 1][currentWeight],
                        helper[currentItemIndex - 1][currentWeight - currentItem.weight] + currentItem.value
                        );
            }
        }
    }

    printKnapsack(capacity, numberItems, helper);
    result(possibleItems, capacity, numberItems, helper, helper[numberItems][capacity]);
    return helper[numberItems][capacity];
}

int main() {
    struct item waterBottle = {"Water bottle", 2, 3};
    struct item food = {"Food", 4, 5};
    struct item shield = {"Shield", 5, 8};
    struct item shortSword = {"Short Sword", 3, 4};
    struct item longSword = {"Long Sword", 9, 10};

    struct item possibleItems[] = {waterBottle, food, shield, shortSword, longSword};
    int numberItems = sizeof(possibleItems)/ sizeof(possibleItems[0]);
    int weightMaximum = 20;

    knapsack(possibleItems, weightMaximum, numberItems);

    return 0;
}