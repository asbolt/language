#ifndef REKURSIVNAYA_EBLYA_MATERI_
#define REKURSIVNAYA_EBLYA_MATERI_

#include "tokens.h"

enum NUMBER_FUNCTIONS
{
    SEMICOLON     = 0,
    PARENTHESIS_L = 2,
    PARENTHESIS_R = 3,
    BRACE_L       = 4,
    BRACE_R       = 5,
    RETURN        = 1,
    PRINTF_S      = 2,
    PRINTF_D      = 3,
    SCANF_D       = 4,
    SQRT          = 5,
    INT_V         = -1,
    SUM           = 1,
    SUB           = 2,
    MUL           = 3,
    DIV           = 4,
    EQUAL         = 5,
    INT_F         = -1,
    WHILE         = 7,
    IF            = 8
};

struct Node
{
    int type    = EMPTY;
    int value   = EMPTY;
    Node *left  = NULL;
    Node *right = NULL;
};

Node *GetEnd (Tokens *tokens, int *p);
Node *GetFuncWithNoArg (Tokens *tokens, int *p);
Node *GetFuncWithOneArg (Tokens *tokens, int *p);
Node *GetFuncWithTwoArg (Tokens *tokens, int *p);
Node *GetCompare (Tokens *tokens, int *p);
Node *GetEquality (Tokens *tokens, int *p);
Node *GetSum (Tokens *tokens, int *p);
Node *GetMul (Tokens *tokens, int *p);
Node *GetBranches (Tokens *tokens, int *p);
Node *GetVariable (Tokens *tokens, int *p);
Node *GetNumber (Tokens *tokens, int *p);
int treeDump (Node *node);
Node *GetHuiBlyatNeZnay (Tokens *tokens, int *p);

#endif