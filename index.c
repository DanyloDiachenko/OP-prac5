#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MIN_SYMBOLS_IN_STRING 0
#define MAX_SYMBOLS_IN_STRING 1000000
#define MIN_NUMBER_OF_STRINGS 0
#define MAX_NUMBER_OF_STRINGS 1000000

void sortStringsArray(char **stringsArray, int stringsNumber) {
    for (int i = 0; i < stringsNumber - 1; i++) {
        for (int j = i + 1; j < stringsNumber; j++) {
            if (strcmp(stringsArray[i], stringsArray[j]) > 0) {
                char *tmp = stringsArray[i];
                stringsArray[i] = stringsArray[j];
                stringsArray[j] = tmp;
            }
        }
    }
}

int getRandomNumber(unsigned short int rangeMin, unsigned short int rangeMax) {
    return rangeMin + rand() % (rangeMax - rangeMin + 1);
}

int main() {
    unsigned short int symbolsInStringNumber = 0;
    unsigned short int stringsNumber = 0;
    char isManualInputValue = 0;
    bool isManualInput;

    setlocale(LC_ALL, "");

    printf("If you want to input custom strings type 'c', for auto-generated type 'a':\n");
    do {
        isManualInputValue = getchar();
        fflush(stdin);

        if (isManualInputValue != 'c' && isManualInputValue != 'a') {
            printf("Invalid input. Please type 'c' or 'a'.\n");
            continue;
        }

        isManualInput = isManualInputValue == 'c';
    } while (isManualInputValue != 'c' && isManualInputValue != 'a');

    printf("Type the number of letters in one string:\n");
    do {
        if (scanf("%hd", &symbolsInStringNumber) != 1) {
            printf("Invalid input. Please enter an integer value.\n");
            fflush(stdin);
            continue;
        }
        fflush(stdin);

        if (symbolsInStringNumber <= MIN_SYMBOLS_IN_STRING || symbolsInStringNumber > MAX_SYMBOLS_IN_STRING) {
            printf("Please enter a value > %d and <= %d.\n", MIN_SYMBOLS_IN_STRING, MAX_SYMBOLS_IN_STRING);
        }
    } while (symbolsInStringNumber <= MIN_SYMBOLS_IN_STRING || symbolsInStringNumber > MAX_SYMBOLS_IN_STRING);

    printf("Type the number of strings:\n");
    do {
        if (scanf("%hd", &stringsNumber) != 1) {
            printf("Invalid input. Please enter an integer value.\n");
            fflush(stdin);
            continue;
        }
        fflush(stdin);

        if (stringsNumber <= MIN_NUMBER_OF_STRINGS || stringsNumber > MAX_NUMBER_OF_STRINGS) {
            printf("Please enter a value > %d and <= %d.\n", MIN_NUMBER_OF_STRINGS, MAX_NUMBER_OF_STRINGS);
        }
    } while (stringsNumber <= MIN_NUMBER_OF_STRINGS || stringsNumber > MAX_NUMBER_OF_STRINGS);

    char **str = malloc(stringsNumber * sizeof(char *));
    if (str == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < stringsNumber; i++) {
        str[i] = (char *)malloc((symbolsInStringNumber + 1) * sizeof(char));
        if (str[i] == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
    }

    if (isManualInput) {
        printf("Enter strings:\n");
        for (int i = 0; i < stringsNumber; i++) {
            printf("String %d: ", i + 1);

            if (fgets(str[i], symbolsInStringNumber + 1, stdin) == NULL || str[i][0] == '\n') {
                fflush(stdin);
                printf("Error: Input cannot be empty. Please enter a non-empty string.\n");
                i--;
                continue;
            }
            fflush(stdin);

            str[i][strcspn(str[i], "\n")] = '\0';
        }
    } else {
        unsigned short int randomSymbol = 0;
        unsigned currentTimeInSeconds = time(NULL);
        srand(currentTimeInSeconds);

        for (int i = 0; i < stringsNumber; i++) {
            unsigned short int currentSymbolIndex = 0;

            do {
                randomSymbol = getRandomNumber(65, 122);

                if ((randomSymbol > 64 && randomSymbol < 91) || (randomSymbol > 96 && randomSymbol < 123)) {
                    str[i][currentSymbolIndex] = randomSymbol;
                    currentSymbolIndex++;
                }
            } while (currentSymbolIndex < symbolsInStringNumber);
            str[i][currentSymbolIndex] = '\0';
        }
    }

    printf("\nYour array:\n");
    for (int i = 0; i < stringsNumber; i++) {
        printf("%d -> %s\n", i + 1, str[i]);
    }

    char **stringPtrs = malloc(stringsNumber * sizeof(char *));
    if (stringPtrs == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < stringsNumber; i++) {
        stringPtrs[i] = str[i];
    }

    sortStringsArray(stringPtrs, stringsNumber);

    printf("\nSorted strings:\n");
    for (int i = 0; i < stringsNumber; i++) {
        printf("%d -> %s\n", i + 1, stringPtrs[i]);
    }

    for (int i = 0; i < stringsNumber; i++) {
        free(str[i]);
    }
    free(str);
    free(stringPtrs);

    return 0;
}
