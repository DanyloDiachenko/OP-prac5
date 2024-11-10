#include <stdio.h>
#include <string.h>

#define MIN_LETTERS_IN_STRING 0
#define MAX_LETTERS_IN_STRING 100

int main() {
    short int lettersInString = 0;

    printf("Type the number of letters in one string:\n");

    do {
        if (scanf("%hd", &lettersInString) != 1) {
            printf("Invalid input. Please enter an integer value.\n");
            fflush(stdin);
            continue;
        }
        fflush(stdin);

        if (lettersInString <= MIN_LETTERS_IN_STRING || lettersInString > MAX_LETTERS_IN_STRING) {
            printf("Invalid input for the number of letters in string. Please enter value greater and not equal to %d and less or equal to %d.\n",
                   MIN_LETTERS_IN_STRING, MAX_LETTERS_IN_STRING);
        }
    } while (lettersInString <= MIN_LETTERS_IN_STRING || lettersInString > MAX_LETTERS_IN_STRING);

    return 0;
}


void sortStringsArray(char **stringsArray, int stringsNumber) {
    for(int i = 0; i < stringsNumber - 1; i++) {
        for(int j = i + 1; j < stringsNumber; j++) {
            if (strcmp(stringsArray[i], stringsArray[j]) > 0) {
                char *tmp = stringsArray[i];
                stringsArray[i] = stringsArray[j];
                stringsArray[j] = tmp;
            }
        }
    }
}