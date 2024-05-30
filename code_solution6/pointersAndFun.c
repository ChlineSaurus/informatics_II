#include <stdio.h>
#include <stdlib.h>

// 2 Ways to define a struct:
struct Point2D_1 {
    int x;
    int y;
};

typedef struct {
    int x;
    int y;
} Point2D_2;

// To return a struct in a function, use keyword struct and the name of the struct
struct Point2D_1 structShowcase() {

    // Use of structs:
    struct Point2D_1 aPoint;
    aPoint.x = 1;
    aPoint.y = 2;
    printf("X: %d, Y: %d \n", aPoint.x, aPoint.y);
    struct Point2D_1 anotherPoint = {5, 1};
    printf("X: %d, Y: %d \n", anotherPoint.x, anotherPoint.y);

    // Can also be put into arrays:
    printf("Size of Point in Bytes: %ld", sizeof(aPoint));
    struct Point2D_1 pointArray[2];

    // Can be returned as normal:
    return aPoint;
}

// Can be returned
int *pointerShowcase() {
    int var = 1;
    printf("Variable as we know it: %d \n", var);
    printf("Where in memory the variable is saved: %p \n", &var);
    int *varLocation = &var;
    printf("Value of the pointer that points to var: %p \n", varLocation);
    printf("Where in memory the pointer is saved: %p \n", &varLocation);
    printf("Value the pointer points to: %d \n", *varLocation);

    int array[] = {1, 2, 3, 4};
    printf("Where the array is saved: %p \n", &array);
    printf("Where the first Element of the array is saved: %p \n", &array[0]);
    printf("Print third element with normal way %d \n", array[2]);
    printf("Print third element with pointers %d \n", *(array + 2));

    struct Point2D_1 *aPoint2DPointer = malloc(sizeof(aPoint2DPointer));
    (*aPoint2DPointer).x = 15;
    aPoint2DPointer->y = 42;
}

int *mallocShowcase() {
    int *a = malloc(sizeof(int));
    *a = 8;
    printf("%d", *a);
    return a;
}

int main() {
    setbuf(stdout, 0);
    structShowcase();
    pointerShowcase();

    int var = 1;
    long anotherVar = 2;
    int array[] = {1, 2, 3};
    struct Point2D_1 anotherPoint = {5, 1};
    int *varLocation = &var;
    int **varLocationLocation = &varLocation;

    int *a = mallocShowcase();
    printf("%d", *a);
}