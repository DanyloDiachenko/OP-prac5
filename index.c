#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MIN_SYMBOLS_IN_STRING 1
#define MAX_SYMBOLS_IN_STRING 1000
#define MIN_NUMBER_OF_STRINGS 1
#define MAX_NUMBER_OF_STRINGS 10000
#define SPACE_SYMBOL_CODE 32
#define TILDA_SYMBOL_CODE 126

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

int getRandomNumber(int rangeMin, int rangeMax) {
    return rangeMin + rand() % (rangeMax - rangeMin + 1);
}

int getRandomSymbol() {
    return getRandomNumber(SPACE_SYMBOL_CODE, TILDA_SYMBOL_CODE);
}

int main() {
    int symbolsInStringNumber = 0;
    int stringsNumber = 0;
    char isManualInputValue = 0;
    bool isManualInput = false;

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
        if (scanf("%d", &symbolsInStringNumber) != 1) {
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
        if (scanf("%d", &stringsNumber) != 1) {
            printf("Invalid input. Please enter an integer value.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (stringsNumber <= MIN_NUMBER_OF_STRINGS || stringsNumber > MAX_NUMBER_OF_STRINGS) {
            printf("Please enter a value > %d and <= %d.\n", MIN_NUMBER_OF_STRINGS, MAX_NUMBER_OF_STRINGS);
        }
    } while (stringsNumber <= MIN_NUMBER_OF_STRINGS || stringsNumber > MAX_NUMBER_OF_STRINGS);

    char **strings = malloc(stringsNumber * sizeof(char *));
    if (strings == NULL) {
        printf("Memory allocation failed!\n");
        printf("Type any key to close the program\n");
        getchar();

        return 0;
    }

    for (int i = 0; i < stringsNumber; i++) {
        strings[i] = (char *)malloc((symbolsInStringNumber + 1) * sizeof(char));

        if (strings[i] == NULL) {
            printf("Memory allocation failed!\n");

            for (int j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);

            printf("Type any key to close the program\n");
            getchar();

            return 0;
        }
    }

    if (isManualInput) {
        printf("Enter strings:\n");
        for (int i = 0; i < stringsNumber; i++) {
            printf("String %d: ", i + 1);

            if (fgets(strings[i], symbolsInStringNumber + 1, stdin) == NULL || strings[i][0] == '\n') {
                fflush(stdin);
                printf("Error: Input cannot be empty. Please enter a non-empty string.\n");
                i--;

                continue;
            }
            fflush(stdin);

            strings[i][strcspn(strings[i], "\n")] = '\0';
        }
    } else {
        srand(time(NULL));

        for (int i = 0; i < stringsNumber; i++) {
            int currentSymbolIndex = 0;

            do {
                int randomSymbol = getRandomSymbol();

                strings[i][currentSymbolIndex] = randomSymbol;
                currentSymbolIndex++;
            } while (currentSymbolIndex < symbolsInStringNumber);

            strings[i][currentSymbolIndex] = '\0';
        }
    }

    printf("\nYour array:\n");
    for (int i = 0; i < stringsNumber; i++) {
        printf("%d -> %s\n", i + 1, strings[i]);
    }

    sortStringsArray(strings, stringsNumber);

    printf("\nSorted strings:\n");
    for (int i = 0; i < stringsNumber; i++) {
        printf("%d -> %s\n", i + 1, strings[i]);
    }

    for (int i = 0; i < stringsNumber; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}
