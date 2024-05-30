#include <stdio.h>

void rleCompression(char string[], int length) {
    if(length == 0) {
        return;
    }
    int charCount = 1;
    char mostRecentChar = string[0];
    for (int i = 1; i < length; i++) {
        if (mostRecentChar == string[i]) {
            charCount++;
        } else {
            printf("%d%c", charCount, mostRecentChar);
            charCount = 1;
            mostRecentChar = string[i];
        }
    }
    printf("%d%c", charCount, mostRecentChar);
}

int main() {
    char string[] = "AAABBAAAA";
    int length = (sizeof(string)/sizeof(string[0]))-1;
    rleCompression(string, length);
    return 0;
}
