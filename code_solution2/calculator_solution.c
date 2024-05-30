//
// Created by Marvin Wiedenkeller on 27.02.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Find the position of the operator with the lowest
 * priority between index h and index t
*/
int findOperator(char *expr, int h, int t) {
    int count = 0;
    // use count to make sure you are outside of a pair of ()
    for (int i = t; i >= h; --i) {
        if (expr[i] == ')') {
            count++;
        } else if (expr[i] == '(') {
            count--;
        } else if ((expr[i] == '+' || expr[i] == '-') && count == 0) {
            return i;
        }
    }

    for (int i = t; i >= h; --i) {
        if (expr[i] == ')') {
            count++;
        } else if (expr[i] == '(') {
            count--;
        } else if ((expr[i] == '*' || expr[i] == '/') && count == 0) {
            return i;
        }
    }

    return -1;
}

/**
 * Calculate the result of the expression between index h and index t
*/
float calculator(char *expr, int h, int t) {
    if (h > t) {
        return 0.0;
    }

    // check if both sides have a pair of ()
    // remove them because they are meaning less
    if (expr[h] == '(' && expr[t] == ')') {
        int flag = 1, count = 0;
        // check the remaining part
        for (int k = h + 1; k <= t - 1; k++) {
            if (expr[k] == '(') count++;
            else if (expr[k] == ')') count--;

            if (count < 0) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            h++;
            t--;
        }
    }

    int opIndex = findOperator(expr, h, t);
    // printf("op idx %d", opIndex);

    if (opIndex == -1 || (opIndex == h && expr[h] == '-')) {
        // no operator or the given expr is a negative number (-xxx)
        char num[20];
        int numIndex = 0;
        for (int i = h; i <= t; ++i) {
            num[numIndex++] = expr[i];
        }
        num[numIndex] = '\0';
        return (float) (atoi(num));
    } else {
        char op = expr[opIndex];

        printf("\nLeft: ");
        for (int k = h; k <= opIndex - 1; k++) {
            printf("%c", expr[k]);
        }
        float left = calculator(expr, h, opIndex - 1);

        printf("\nRight: ");
        for (int k = opIndex + 1; k <= t; k++) {
            printf("%c", expr[k]);
        }
        float right = calculator(expr, opIndex + 1, t);

        printf("\nOP: %c, Left=%f, Right=%f", op, left, right);

        switch (op) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                return left / right;
            default:
                printf("ERROR - Unknown Operator!\n");
                return 0;
        }
    }
}

int main() {
    char expr[] = "(3+4)*5/6+7*8*(1+(-2)-1+1)";

    // Remove trailing newline character
    if (expr[strlen(expr) - 1] == '\n') {
        expr[strlen(expr) - 1] = '\0';
    }

    float result = calculator(expr, 0, strlen(expr) - 1);

    printf("\nAns = %f\n", result);

    return 0;
}