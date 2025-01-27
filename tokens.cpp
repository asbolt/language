#include "h_files/tokens.h"

Tokens *dispetcher (const char *programFile)
{
    FILE *file = fopen (programFile, "r");
    if (file == NULL)
        return NULL;

    fseek (file, 0, SEEK_END);
    int fileSize = ftell (file);
    fseek (file, 0, SEEK_SET);

    char *buffer = (char *)calloc (fileSize, sizeof(char));
    if (buffer == NULL)
        return NULL;

    fread (buffer, sizeof(char), fileSize, file);
    fclose (file);

    Tokens *tokens = (Tokens *)calloc (1, sizeof(Tokens));
    if (tokens == NULL)
        return NULL;

    tokens->type = (int *)calloc (fileSize, sizeof(int));
    if (tokens->type == NULL)
        return NULL;

    tokens->value = (int *)calloc (fileSize, sizeof(int));
    if (tokens->value == NULL)
        return NULL;

    Names *newNames = (Names *)calloc (1, sizeof(Names));
    if (newNames == NULL)
        return NULL;

    for (int i = 0; i < MAX_NAME_AMOUNT; i++)
    {
        newNames->names[i].name = (char *)calloc (MAX_NAME_SIZE, sizeof(char));
        if (newNames->names[i].name == NULL)
            return NULL;
    }

    makeTokens (fileSize, buffer, tokens, newNames);

    free (buffer);
    tokens->newNames = newNames;
    return tokens;
}

bool makeTokens (int fileSize, char *buffer, Tokens *tokens, Names *newNames)
{
    int position = 0;
    while (position < fileSize)
    {
        if (buffer[position] == ' ' || buffer[position] == '\n')
            position++;
        else if (isdigit (buffer[position]) != 0)
            getNumber (&position, buffer, tokens);
        else if (getFuncWithNoArg (&position, buffer, tokens) == false)
            getName (&position, buffer, tokens, newNames);
    }

    return true;
}

bool getNumber (int *position, char *buffer, Tokens *tokens)
{
    int value = 0;
    while (isdigit (buffer[*position]) != 0)
    {
        value = value*10 + buffer[*position] - '0';
        (*position)++;
    }

    tokens->type[tokens->numberTokens] = NUMBER;
    tokens->value[tokens->numberTokens] = value;
    (tokens->numberTokens)++;

    return true;
}

bool getFuncWithNoArg (int *position, char *buffer, Tokens *tokens)
{
    int number = sizeof(functionsWithNoArg) / sizeof(Function);

    for (int i = 0; i < number; i++)
    {
        if (strncmp (buffer + *position, functionsWithNoArg[i].functionName, functionsWithNoArg[i].size) == 0)
        {
            tokens->type[tokens->numberTokens] = FUNCTION_WITH_NO_ARG;
            tokens->value[tokens->numberTokens] = functionsWithNoArg[i].value;
            (tokens->numberTokens)++;
            (*position) += functionsWithNoArg[i].size;
            return true;
        }
    }

    return getFuncWithOneArg (position, buffer, tokens);
}

bool getFuncWithOneArg (int *position, char *buffer, Tokens *tokens)
{
    int number = sizeof(functionsWithOneArg) / sizeof(Function);

    for (int i = 0; i < number; i++)
    {
        if (strncmp (buffer + *position, functionsWithOneArg[i].functionName, functionsWithOneArg[i].size) == 0)
        {
            tokens->type[tokens->numberTokens] = FUNCTION_WITH_ONE_ARG;
            tokens->value[tokens->numberTokens] = functionsWithOneArg[i].value;
            (tokens->numberTokens)++;
            (*position) += functionsWithOneArg[i].size;
            return true;
        }
    }

    return getFuncWithTwoArg (position, buffer, tokens);
}

bool getFuncWithTwoArg (int *position, char *buffer, Tokens *tokens)
{
    int number = sizeof(functionsWithTwoArg) / sizeof(Function);

    for (int i = 0; i < number; i++)
    {
        if (strncmp (buffer + *position, functionsWithTwoArg[i].functionName, functionsWithTwoArg[i].size) == 0)
        {
            tokens->type[tokens->numberTokens] = FUNCTION_WITH_TWO_ARG;
            tokens->value[tokens->numberTokens] = functionsWithTwoArg[i].value;
            (tokens->numberTokens)++;
            (*position) += functionsWithTwoArg[i].size;
            return true;
        }
    }

    return false;
}

bool getName (int *position, char *buffer, Tokens *tokens, Names *newNames)
{
    for (int i = 0; i < newNames->nameNumber; i++)
    {
        if (strncmp (buffer + *position, newNames->names[i].name, newNames->names[i].size) == 0)
        {
            tokens->type[tokens->numberTokens] = NAME;
            tokens->value[tokens->numberTokens] = newNames->names[i].number;
            (tokens->numberTokens)++;
            (*position) += newNames->names[i].size;
            return true;
        }
    }

    return getNewName (position, buffer, tokens, newNames);
}

bool getNewName (int *position, char *buffer, Tokens *tokens, Names *newNames)
{
    int currentSize = 0;
    int currentPosition = *position;

    while (buffer[*position] != ' ')
    {
        currentSize++;
        (*position)++;
    }

    strncpy (newNames->names[newNames->nameNumber].name, buffer + currentPosition, currentSize);
    newNames->names[newNames->nameNumber].size = currentSize;
    newNames->names[newNames->nameNumber].number = newNames->nameNumber;
    tokens->type[tokens->numberTokens] = NAME;
    tokens->value[tokens->numberTokens] = newNames->names[newNames->nameNumber].number;
    (tokens->numberTokens)++;
    (newNames->nameNumber)++;

    return true;
}

void tokenDump (Tokens *tokens)
{
    printf ("  type       value\n");
    for (int i = 0; tokens->type[i] != EMPTY; i++)
    {
        printf ("%d %d %10d\n", i, tokens->type[i], tokens->value[i]);
    }
}