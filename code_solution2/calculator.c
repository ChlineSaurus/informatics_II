#include <stdio.h>

#define true 1
#define false 0
#define notFound -1


int findOperator(char expr[], int h, int t) {
    int bracketCounter = 0;
    int multiplyDivisionIndex = notFound;
    for (int i = h; i < t; i++) {
        if (expr[i] == '(') {
            bracketCounter++;
        } else if (expr[i] == ')') {
            bracketCounter--;
        } else if (bracketCounter == 0) {
            if (expr[i] == '+' || expr[i] == '-') {
                return i;
            } else if (expr[i] == '*' || expr[i] == '/') {
                multiplyDivisionIndex = i;
            }
        }
    }
    return multiplyDivisionIndex;
}

int removableOutermostBracket(char expr[], int h, int t) {
    if (expr[h] != '(' || expr[t] != ')') {
        return false;
    }
    int bracketCounter = 0;
    for (int i = h + 1; i < t; i++) {
        if (expr[i] == '(') {
            bracketCounter++;
        } else if (expr[i] == ')') {
            bracketCounter--;
        }
        if (bracketCounter < 0) {
            return false;
        }
    }
    return true;
}

double parseDouble(char expr[], int h, int t) {
    int result = 0;
    for (int i = h; i <= t; i++) {
        result = result * 10 + (expr[i] - '0');
    }
    return (double) result;
}

void printBracketsRemoved(char expr[], int h, int t) {
    printf("Brackets Removed: ");
    printf("(  ");
    for(int i = h + 1; i < t; i++) {
        printf("%c", expr[i]);
    }
    printf("  )\n");
}

void printSplit(char expr[], int h, int t, int operatorIndex) {
    printf("Split: ");
    for(int i = h; i <= t; i++) {
        if (i == operatorIndex) {
            printf("  %c  ", expr[i]);
        } else {
            printf("%c", expr[i]);
        }
    }
    printf("\n");
}

void printMerge(double left, double right, char operator) {
    printf("Merge: %lf %c %lf \n", left, operator, right);
}

double calculator(char expr[], int h, int t) {
    if (removableOutermostBracket(expr, h, t)) {
        printBracketsRemoved(expr, h, t);
        h++;
        t--;
    }

    int operatorIndex = findOperator(expr, h, t);

    if (operatorIndex == h) {
        return (-1) * parseDouble(expr, h, t);
    } else if (operatorIndex == notFound) {
        return parseDouble(expr, h, t);
    }

    printSplit(expr, h, t, operatorIndex);
    double left = calculator(expr, h, operatorIndex - 1);
    double right = calculator(expr, operatorIndex + 1, t);

    char operator = expr[operatorIndex];
    printMerge(left, right, operator);

    if(operator == '+') {
        return left + right;
    } else if (operator == '-') {
        return left - right;
    } else if (operator == '*') {
        return left * right;
    } else {
        return left / right;
    }
}

int main() {
    char expr[] = "(3+4)*5/6+7*8*(1+(-2)-1+1)";
    int length = sizeof(expr) - 1;
    double result = calculator(expr, 0, length - 1);
    printf("Result: %lf", result);
    return 0;
}