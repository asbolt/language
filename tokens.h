#ifndef TOKENS_H_
#define TOKENS_H_

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

#define NAMES_FILE "namefile.txt"

const int MAX_NAME_SIZE = 30;
const int MAX_NAME_AMOUNT = 10; 

enum TOKEN_TYPES 
{
    NUMBER                = 1,
    VARIABLE              = 2,
    FUNCTION              = 6,
    FUNCTION_WITH_NO_ARG  = 3,
    FUNCTION_WITH_ONE_ARG = 4,
    FUNCTION_WITH_TWO_ARG = 5,
    NAME                  = 7,
    EMPTY                 = 0
};

struct Function 
{
    const char *functionName = NULL;
    int functionType         = 0;
    int value                = 0;
    int size                 = 0;
};

const Function functionsWithNoArg [] =  {{";",                FUNCTION_WITH_NO_ARG,  1, 1},
                                   {"(",                FUNCTION_WITH_NO_ARG,  2, 1},
                                   {")",                FUNCTION_WITH_NO_ARG,  3, 1},
                                   {"{",                FUNCTION_WITH_NO_ARG,  4, 1},
                                   {"}",                FUNCTION_WITH_NO_ARG,  5, 1}};

const Function functionsWithOneArg [] = {{"vernut",           FUNCTION_WITH_ONE_ARG, 1, 6},
                                   {"napechatatStroky", FUNCTION_WITH_ONE_ARG, 2, 16},
                                   {"napechatatChislo", FUNCTION_WITH_ONE_ARG, 3, 16},
                                   {"vvesti",           FUNCTION_WITH_ONE_ARG, 4, 6},
                                   {"cvdrcrn",          FUNCTION_WITH_ONE_ARG, 5, 7},
                                   {"celoeP",           FUNCTION_WITH_ONE_ARG, 6, 6}};

const Function functionsWithTwoArg [] = {{"+",                FUNCTION_WITH_TWO_ARG, 1, 1},
                                   {"-",                FUNCTION_WITH_TWO_ARG, 2, 1},
                                   {"*",                FUNCTION_WITH_TWO_ARG, 3, 1},
                                   {"/",                FUNCTION_WITH_TWO_ARG, 4, 1},
                                   {"=",                FUNCTION_WITH_TWO_ARG, 5, 1},
                                   {"celoeF",           FUNCTION_WITH_TWO_ARG, 6, 6},
                                   {"poka",             FUNCTION_WITH_TWO_ARG, 7, 4},
                                   {"esli",             FUNCTION_WITH_TWO_ARG, 8, 4}};

struct Name
{
    char *name = NULL;
    int number = 0;
    int size   = 0; 
};

struct Names
{
    Name names [MAX_NAME_AMOUNT] = {};
    int nameNumber               = 0;
};

struct Tokens
{
    int *type        = NULL;
    int *value       = NULL;
    int numberTokens = 0;
};

Tokens *dispetcher (const char *programFile);
bool makeTokens (int fileSize, char *buffer, Tokens *tokens, Names *newNames);
bool getNumber (int *position, char *buffer, Tokens *tokens);
bool getFuncWithNoArg (int *position, char *buffer, Tokens *tokens);
bool getFuncWithOneArg (int *position, char *buffer, Tokens *tokens);
bool getFuncWithTwoArg (int *position, char *buffer, Tokens *tokens);
bool getName (int *position, char *buffer, Tokens *tokens, Names *newNames);
bool getNewName (int *position, char *buffer, Tokens *tokens, Names *neNames);
void tokenDump (Tokens *tokens);

#endif