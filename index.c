#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MIN_LETTERS_IN_STRING 0
#define MAX_LETTERS_IN_STRING 100
#define MIN_NUMBER_OF_STRINGS 0
#define MAX_NUMBER_OF_STRINGS 100

int main() {
    short int lettersInString = 0;
    short int numberOfStrings = 0;
    char isManualInputValue = 0;
    bool isManualInput;

    printf("If You want to put Your custom strings type 'c' and if You want strings be auto-generated type 'a':\n");
    do {
        isManualInputValue = getchar();
        fflush(stdin);

        if(isManualInputValue != 'c' && isManualInputValue != 'a') {
            printf("Invalid input. Please type the value 'c' or 'a'.\n");
            continue;
        }

        if(isManualInputValue == 'c') {
            isManualInput = true;
        } else {
            isManualInput = false;
        }
    } while (isManualInputValue != 'c' && isManualInputValue != 'a');

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

    printf("Type the number of strings:\n");
    do {
        if (scanf("%hd", &numberOfStrings) != 1) {
            printf("Invalid input. Please enter an integer value.\n");
            fflush(stdin);
            continue;
        }
        fflush(stdin);

        if (numberOfStrings <= MIN_NUMBER_OF_STRINGS || numberOfStrings > MAX_NUMBER_OF_STRINGS) {
            printf("Invalid input for the number of strings. Please enter value greater and not equal to %d and less or equal to %d.\n",
                   MIN_NUMBER_OF_STRINGS, MAX_NUMBER_OF_STRINGS);
        }
    } while (numberOfStrings <= MIN_NUMBER_OF_STRINGS || numberOfStrings > MAX_NUMBER_OF_STRINGS);

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