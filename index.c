#include "./includes.h"

bool getAndValidateIsManualInput();
int getAndValidateSymbolsInString();
int getAndValidateStringsNumber();
void printResults(int stringsNumber, char **strings);
void freeMemory(int stringsNumber, char **strings);
void getStrings(bool isManualInput, int stringsNumber, char **strings, int symbolsInStringNumber);
char **allocateStringArray(int stringsNumber);
char **allocateMemoryForStrings(int stringsNumber, int symbolsInStringNumber);

int main() {
    printf("Welcome! This program sorts strings.\n");

    setlocale(LC_ALL, "");

    bool isManualInput = getAndValidateIsManualInput();
    int symbolsInStringNumber = getAndValidateSymbolsInString();
    int stringsNumber = getAndValidateStringsNumber();

    char **strings = allocateMemoryForStrings(stringsNumber, symbolsInStringNumber);
    if (strings == NULL) {
        return 0;
    }

    getStrings(isManualInput, stringsNumber, strings, symbolsInStringNumber);

    printResults(stringsNumber, strings);

    freeMemory(stringsNumber, strings);

    return 0;
}
