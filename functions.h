#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void sortStringArray(char **stringsArray, int stringsNumber)
{
    for (int i = 0; i < stringsNumber - 1; i++)
    {
        for (int j = i + 1; j < stringsNumber; j++)
        {
            if (strcmp(stringsArray[i], stringsArray[j]) > 0)
            {
                char *tmp = stringsArray[i];

                stringsArray[i] = stringsArray[j];
                stringsArray[j] = tmp;
            }
        }
    }
}

int getRandomNumber(int rangeMin, int rangeMax)
{
    return rangeMin + rand() % (rangeMax - rangeMin + 1);
}

int getRandomSymbol()
{
    return getRandomNumber(SPACE_SYMBOL_CODE, TILDA_SYMBOL_CODE);
}

bool getAndValidateIsManualInput()
{
    char isManualInputValue = 0;
    bool isManualInput = false;

    printf("If you want to input custom strings type 'c', for auto-generated type 'a':\n");

    do
    {
        isManualInputValue = getchar();
        fflush(stdin);

        if (isManualInputValue != 'c' && isManualInputValue != 'a')
        {
            printf("Invalid input. Please type 'c' or 'a'.\n");

            continue;
        }

        isManualInput = isManualInputValue == 'c';
    } while (isManualInputValue != 'c' && isManualInputValue != 'a');

    return isManualInput;
}

int getAndValidateSymbolsInString()
{
    int symbolsInStringNumber = 0;

    printf("Type the number of letters in one string greater thar %d and less or equal to %d:\n",
           MIN_SYMBOLS_IN_STRING, MAX_SYMBOLS_IN_STRING);

    do
    {
        if (scanf("%d", &symbolsInStringNumber) != 1)
        {
            printf("Invalid input. Please enter an integer value.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (symbolsInStringNumber <= MIN_SYMBOLS_IN_STRING || symbolsInStringNumber > MAX_SYMBOLS_IN_STRING)
        {
            printf("Please enter a value > %d and <= %d.\n", MIN_SYMBOLS_IN_STRING, MAX_SYMBOLS_IN_STRING);
        }
    } while (symbolsInStringNumber <= MIN_SYMBOLS_IN_STRING || symbolsInStringNumber > MAX_SYMBOLS_IN_STRING);

    return symbolsInStringNumber;
}

int getAndValidateStringsNumber()
{
    int stringsNumber = 0;

    printf("Type the number of strings greater thar %d and less or equal to %d:\n",
           MIN_NUMBER_OF_STRINGS, MAX_NUMBER_OF_STRINGS);

    do
    {
        if (scanf("%d", &stringsNumber) != 1)
        {
            printf("Invalid input. Please enter an integer value.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (stringsNumber <= MIN_NUMBER_OF_STRINGS || stringsNumber > MAX_NUMBER_OF_STRINGS)
        {
            printf("Please enter a value > %d and <= %d.\n", MIN_NUMBER_OF_STRINGS, MAX_NUMBER_OF_STRINGS);
        }
    } while (stringsNumber <= MIN_NUMBER_OF_STRINGS || stringsNumber > MAX_NUMBER_OF_STRINGS);

    return stringsNumber;
}

void printResults(int stringsNumber, char **strings)
{
    printf("\nYour array:\n");
    for (int i = 0; i < stringsNumber; i++)
    {
        printf("%d -> %s\n", i + 1, strings[i]);
    }

    sortStringArray(strings, stringsNumber);

    printf("\nSorted strings:\n");
    for (int i = 0; i < stringsNumber; i++)
    {
        printf("%d -> %s\n", i + 1, strings[i]);
    }
}

void freeMemory(int stringsNumber, char **strings)
{
    for (int i = 0; i < stringsNumber; i++)
    {
        free(strings[i]);
    }
    free(strings);
}

void getStringsByKeyboard(int stringsNumber, char **strings, int symbolsInStringNumber)
{
    printf("Enter strings:\n");
    for (int i = 0; i < stringsNumber; i++)
    {
        printf("String %d: ", i + 1);

        if (fgets(strings[i], symbolsInStringNumber + 1, stdin) == NULL || strings[i][0] == '\n')
        {
            fflush(stdin);
            printf("Error: Input cannot be empty. Please enter a non-empty string.\n");
            i--;

            continue;
        }
        fflush(stdin);

        strings[i][strcspn(strings[i], "\n")] = '\0';
    }
}

void getGeneratedSymbols(int stringsNumber, char **strings, int symbolsInStringNumber)
{
    srand(time(NULL));

    for (int i = 0; i < stringsNumber; i++)
    {
        int currentSymbolIndex = 0;

        do
        {
            int randomSymbol = getRandomSymbol();

            strings[i][currentSymbolIndex] = randomSymbol;
            currentSymbolIndex++;
        } while (currentSymbolIndex < symbolsInStringNumber);

        strings[i][currentSymbolIndex] = '\0';
    }
}

void getStrings(bool isManualInput, int stringsNumber, char **strings, int symbolsInStringNumber)
{
    if (isManualInput)
    {
        getStringsByKeyboard(stringsNumber, strings, symbolsInStringNumber);
    }
    else
    {
        getGeneratedSymbols(stringsNumber, strings, symbolsInStringNumber);
    }
}

char **allocateStringArray(int stringsNumber)
{
    char **strings = malloc(stringsNumber * sizeof(char *));
    if (strings == NULL)
    {
        printf("Memory allocation failed!\n");
        printf("Type any key to close the program\n");
        getchar();

        return NULL;
    }
    return strings;
}

char **allocateMemoryForStrings(int stringsNumber, int symbolsInStringNumber)
{
    char **strings = allocateStringArray(stringsNumber);

    if (strings == NULL)
    {
        return 0;
    }

    for (int i = 0; i < stringsNumber; i++)
    {
        strings[i] = (char *)malloc((symbolsInStringNumber + 1) * sizeof(char));

        if (strings[i] == NULL)
        {
            printf("Memory allocation failed for string %d!\n", i + 1);

            freeMemory(stringsNumber, strings);

            printf("Type any key to close the program\n");
            getchar();

            return NULL;
        }
    }

    return strings;
}

#endif // FUNCTIONS_H
