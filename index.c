#include <stdio.h>
#include <string.h>
#include <stdio.h>

int main() {
    printf("Hello");

    return 0;
}

void sortStringsArray(char **stringsArray, int stringsNumber) {
    int i, j;

    for(i = 0; i < stringsNumber - 1; i++) {
        for(j = i + 1; j < stringsNumber; j++) {
            if (strcmp(stringsArray[i], stringsArray[j]) > 0) {
                char *tmp;
                tmp = stringsArray[i];
                stringsArray[i] = stringsArray[j];
                stringsArray[j] = tmp;
            }
        }
    }
}