#include "token.h"

Tokens *makeTokens (const char *str)
{
    Tokens *tokens = (Tokens *)calloc (1, sizeof(Tokens));
    if (tokens == 0)
        return NULL;

    tokens->tokenType = (int *)calloc (40, sizeof(int));
    if (tokens->tokenType == NULL)
        return NULL;

    tokens->tokenValue = (int *)calloc (40, sizeof(char));
    if (tokens->tokenValue  == NULL)
        return NULL;
    
    int numberTokens = 0;
    int p = 0;

    token (str, &p, tokens, &numberTokens);
    tokenDump (tokens, numberTokens);

    return tokens;
}


void token (const char *str, int *p, struct Tokens *tokens, int *numberTokens)
{
    while (str[*p] != ';')
    {
        if (str[*p] == ' ')
        {
            (*p)++;
        } else if (isalpha (str[*p]) != 0)
        {
            getFunc (str, p, tokens, numberTokens);
        } else if (isdigit(str[*p]) != 0) 
        {
            getNum (str, p, tokens, numberTokens);
        } else
        {
            getOperation (str, p, tokens, numberTokens);
        }
    }

    tokens->tokenType[*numberTokens] = FUNC_WITH_NO_ARG;
    tokens->tokenValue[*numberTokens] = 7;
    (*numberTokens)++;
    (*p)++;
}

bool getFunc (const char *str, int *p, struct Tokens *tokens, int *numberTokens)
{
    int amount = sizeof(keyWords)/sizeof(const Function);

    for (int i = 0; i < amount; i++)
    {
        if (strncmp (str + *p, keyWords[i].name, keyWords[i].size) == 0)
        {
            tokens->tokenType[*numberTokens] = keyWords[i].tokenType;
            tokens->tokenValue[*numberTokens] = keyWords[i].tokenValue;
            *p += keyWords[i].size;
            (*numberTokens)++;
            return true;
        }
    }

    getVariable (str, p, tokens, numberTokens);
    return false;

}


void getNum (const char *str, int *p, struct Tokens *tokens, int *numberTokens)
{
    int result = 0;

    while (isdigit(str[*p]) != 0)
    {
        result = result*10 + str[*p] - '0';
        (*p)++;
    }

    tokens->tokenType[*numberTokens] = NUMBER;
    tokens->tokenValue[*numberTokens] = result;
    (*numberTokens)++;
}

bool getOperation (const char *str, int *p, struct Tokens *tokens, int *numberTokens)
{
    int amount = sizeof(operations)/sizeof(const Function);

    for (int i = 0; i < amount; i++)
    {
        if (strncmp (str + *p, operations[i].name, operations[i].size) == 0)
        {
            tokens->tokenType[*numberTokens] = operations[i].tokenType;
            tokens->tokenValue[*numberTokens] = operations[i].tokenValue;
            *p += operations[i].size;
            (*numberTokens)++;
            return 0;
        }
    }

    return false;
}

bool getVariable (const char *str, int *p, struct Tokens *tokens, int *numberTokens)
{
    tokens->tokenType[*numberTokens] = VARIABLE;
    tokens->tokenValue[*numberTokens] = *p;
    (*numberTokens)++;

    while (isalpha(str[*p]) != 0)
        (*p)++;

    return true;
}

bool tokenDump (struct Tokens *tokens, int numberTokens)
{
    printf ("         type      value\n");
    for (int i = 0; i < numberTokens; i++)
    {
        printf ("%2d %10d %10d\n", i, tokens->tokenType[i], tokens->tokenValue[i]);
    }

    return true;
}