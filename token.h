#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

const int MAX_NAME_SIZE = 30;

struct Tokens
{
    int *tokenType  = NULL;
    int *tokenValue = NULL;
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
bool getFunc (const char *str, int *p, struct Tokens *tokens, int *numberTokens);
void getNum (const char *str, int *p, struct Tokens *tokens, int *numberTokens);
bool getOperation (const char *str, int *p, struct Tokens *tokens, int *numberTokens);
bool getVariable (const char *str, int *p, struct Tokens *tokens, int *numberTokens);
bool tokenDump (struct Tokens *tokens, int numberTokens);
Tokens *makeTokens (const char *str);

#endif