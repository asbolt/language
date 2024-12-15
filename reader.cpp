#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

const int MAX_NAME_SIZE = 30;

struct Tokens
{
    int *tokenType  = NULL;
    int *tokenValue = NULL;
    int *leftArg    = NULL;
    int *rightArg   = NULL;
};

enum TokenTypes 
{
    NUMBER            = 4,
    VARIABLE          = 5,
    FUNC_WITH_NO_ARG  = 1,
    FUNC_WITH_ONE_ARG = 2,
    FUNC_WITH_TWO_ARG = 3,
    OPERATION         = 6,
    EMPTY             = 0
};

struct Function 
{
    const char *name     = NULL;
    int tokenType        = EMPTY;
    int tokenValue       = EMPTY;
    int size             = 0;
};

struct Variable
{
    const char *name = NULL;
    int tokenType    = VARIABLE;
    int tokenValue   = EMPTY;
    int size         = 0;
};

const Function keyWords[] = {{"break", FUNC_WITH_ONE_ARG, 1, 5},
                             {"continue", FUNC_WITH_NO_ARG, 2, 8},
                             {"sqrt", FUNC_WITH_ONE_ARG, 1, 4},
                             {"return", FUNC_WITH_TWO_ARG, 2, 6},
                             {"if", FUNC_WITH_TWO_ARG, 1, 2},
                             {"while", FUNC_WITH_TWO_ARG, 2, 5},
                             {"printf", FUNC_WITH_ONE_ARG, 3, 6},
                             {"scanf", FUNC_WITH_ONE_ARG, 4, 5},
                             {";", FUNC_WITH_NO_ARG, 7, 1}};

const Function operations[] = {{"+", OPERATION, 1, 1},
                               {"-", OPERATION, 2, 1},
                               {"*", OPERATION, 3, 1},
                               {"/", OPERATION, 4, 1},
                               {"=", OPERATION, 5, 1},
                               {"!=", OPERATION, 6, 2},
                               {"==", OPERATION, 7, 2},
                               {">", OPERATION, 8, 1},
                               {"<", OPERATION, 9, 1},
                               {">=", OPERATION, 10, 2},
                               {"<=", OPERATION, 10, 2},
                               {"(", FUNC_WITH_NO_ARG, 3, 1},
                               {")", FUNC_WITH_NO_ARG, 4, 1},
                               {"{", FUNC_WITH_NO_ARG, 5, 1},
                               {"}", FUNC_WITH_NO_ARG, 6, 1}};
     

void token (const char *str, int *p, struct Tokens *tokens, int *numberTokens);
int getFunc (const char *str, int *p, struct Tokens *tokens, int *numberTokens);
void getNum (const char *str, int *p, struct Tokens *tokens, int *numberTokens);
int getOperation (const char *str, int *p, struct Tokens *tokens, int *numberTokens);
int getVariable (const char *str, int *p, struct Tokens *tokens, int *numberTokens);
int tokenDump (struct Tokens *tokens, int numberTokens);

int main ()
{
    Tokens *tokens = (Tokens *)calloc (1, sizeof(Tokens));
    if (tokens == 0)
        return 1;

    tokens->tokenType = (int *)calloc (40, sizeof(int));
    tokens->tokenValue = (int *)calloc(40, sizeof(char));
    
    int numberTokens = 0;
    int p = 0;

    token ("yy if + ypp;", &p, tokens, &numberTokens);
    tokenDump (tokens, numberTokens);

    return 0;
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

int getFunc (const char *str, int *p, struct Tokens *tokens, int *numberTokens)
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
            return 0;
        }
    }

    getVariable (str, p, tokens, numberTokens);
    return 1;

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

int getOperation (const char *str, int *p, struct Tokens *tokens, int *numberTokens)
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

    return 1;
}

int getVariable (const char *str, int *p, struct Tokens *tokens, int *numberTokens)
{
    tokens->tokenType[*numberTokens] = VARIABLE;
    tokens->tokenValue[*numberTokens] = *p;
    (*numberTokens)++;

    while (isalpha(str[*p]) != 0)
        (*p)++;

    return 0;
}

int tokenDump (struct Tokens *tokens, int numberTokens)
{
    printf ("         type      value\n");
    for (int i = 0; i < numberTokens; i++)
    {
        printf ("%2d %10d %10d\n", i, tokens->tokenType[i], tokens->tokenValue[i]);
    }

    return 0;
}