#include "../h_files/rekursivnaya_eblya_materi.h"

Node *nodeCtor (int type, int value, Node *left, Node *right)
{
    Node *node = (Node *)calloc (1, sizeof(Node));
    if (node == NULL)
        return NULL;

    node->type = type;
    node->value = value;
    node->right = right;
    node->left = left;

    return node;
}

Node *GetEnd (Tokens *tokens, int *p)
{
    Node *node1 = GetFuncWithOneArg (tokens, p);
    if (tokens->type[*p] == FUNCTION_WITH_TWO_ARG && tokens->value[*p] == SEMICOLON)
        (*p)++;

    Node *node2 = NULL;
    while (*p < tokens->numberTokens)
    {
        node2 = GetFuncWithOneArg (tokens, p);
        if (tokens->type[*p] == FUNCTION_WITH_TWO_ARG && tokens->value[*p] == SEMICOLON)
            (*p)++;
        node1 = nodeCtor (FUNCTION_WITH_TWO_ARG, SEMICOLON, node1, node2);
    }

    return node1;
}

Node *GetFuncWithOneArg (Tokens *tokens, int *p)
{
    if (tokens->type[*p] == FUNCTION_WITH_ONE_ARG && tokens->value[*p] > 0)
    {
        int currentP = *p;
        (*p)++;
        Node *arg1 = NULL;
        Node *arg2 = NULL;

        if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == PARENTHESIS_L)
        {
            (*p)++;
            arg1 = GetVariable (tokens, p);
            if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == PARENTHESIS_R)
                (*p)++;
        }

        return nodeCtor (FUNCTION_WITH_ONE_ARG, tokens->value[currentP], arg1, NULL);
    } else {
        Node *node = GetHuiBlyatNeZnay (tokens, p);
        if (node == NULL)
            return GetFuncWithTwoArg (tokens, p);
        else
            return node;
    }
}

Node *GetFuncWithTwoArg (Tokens *tokens, int *p)
{
    if (tokens->type[*p] == FUNCTION_WITH_TWO_ARG && tokens->value[*p] > 5)
    {
        int currentP = *p;
        (*p)++;
        Node *arg1 = NULL;
        Node *arg2 = NULL;

        if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == PARENTHESIS_L)
        {
            (*p)++;
            arg1 = GetCompare (tokens, p);
            if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == PARENTHESIS_R)
                (*p)++;
        }

        if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == BRACE_L)
        {
            (*p)++;
            arg2 = GetFuncWithOneArg (tokens, p);
            if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == BRACE_R)
                (*p)++;
        }

        return nodeCtor (FUNCTION_WITH_TWO_ARG, tokens->value[currentP], arg1, arg2);
    } else 
        return GetCompare (tokens, p);
}

Node *GetCompare (Tokens *tokens, int *p)
{
    return GetEquality (tokens, p);
}

Node *GetEquality (Tokens *tokens, int *p)
{
    if (tokens->type[*p] == NAME)
    {
        Node *arg1 = nodeCtor (NAME, tokens->value[*p], NULL, NULL);
        (*p)++;
        if (tokens->type[*p] == FUNCTION_WITH_TWO_ARG && tokens->value[*p] == EQUAL)
        {
            (*p)++;
            Node *arg2 = GetSum (tokens, p);
            return nodeCtor (FUNCTION_WITH_TWO_ARG, EQUAL, arg1, arg2);
        } else
            return arg1;
    } else
        return GetSum (tokens, p);
}

Node *GetSum (Tokens *tokens, int *p)
{
    Node *arg1 = GetMul (tokens, p);

    while (tokens->type[*p] == FUNCTION_WITH_TWO_ARG && (tokens->value[*p] == SUM || tokens->value[*p] == SUB))
    {
        if (tokens->type[*p] == FUNCTION_WITH_TWO_ARG && tokens->value[*p] == SUM)
        {
            (*p)++;
            Node *arg2 = GetBranches (tokens, p);
            arg1 = nodeCtor (FUNCTION_WITH_TWO_ARG, SUM, arg1, arg2);
        } else if (tokens->type[*p] == FUNCTION_WITH_TWO_ARG && tokens->value[*p] == SUB)
        {
            (*p)++;
            Node *arg2 = GetBranches (tokens, p);
            arg1 = nodeCtor (FUNCTION_WITH_TWO_ARG, SUB, arg1, arg2);
        }
    }

    return arg1;
}

Node *GetMul (Tokens *tokens, int *p)
{
    Node *arg1 = GetBranches (tokens, p);

    while (tokens->type[*p] == FUNCTION_WITH_TWO_ARG && (tokens->value[*p] == MUL || tokens->value[*p] == DIV))
    {
        if (tokens->type[*p] == FUNCTION_WITH_TWO_ARG && tokens->value[*p] == MUL)
        {
            (*p)++;
            Node *arg2 = GetBranches (tokens, p);
            arg1 = nodeCtor (FUNCTION_WITH_TWO_ARG, MUL, arg1, arg2);
        } else if (tokens->type[*p] == FUNCTION_WITH_TWO_ARG && tokens->value[*p] == DIV)
        {
            (*p)++;
            Node *arg2 = GetBranches (tokens, p);
            arg1 = nodeCtor (FUNCTION_WITH_TWO_ARG, DIV, arg1, arg2);
        }
    }

    return arg1;
}

Node *GetBranches (Tokens *tokens, int *p)
{
    if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == PARENTHESIS_L)
    {
        (*p)++;
        Node *arg = GetSum (tokens, p);
        if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == PARENTHESIS_R)
        {
            (*p)++;
            return arg;
        } else 
            return NULL;
    } else if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == BRACE_L)
    {
        (*p)++;
        Node *arg = GetSum (tokens, p);
        if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == BRACE_L)
        {
            (*p)++;
            return arg;
        } else 
            return NULL;
    } else
        return GetVariable (tokens, p);
}

Node *GetVariable (Tokens *tokens, int *p)
{
    int value = 0;
    if (tokens->type[*p] == NAME)
    {
        value = tokens->value[*p];
        (*p)++;
        return nodeCtor (NAME, value, NULL, NULL);
    } else
        return GetNumber (tokens, p);
}

Node *GetNumber (Tokens *tokens, int *p)
{
    int value = 0;
    if (tokens->type[*p] == NUMBER)
    {
        value = tokens->value[*p];
        (*p)++;
    }

    return nodeCtor (NUMBER, value, NULL, NULL);
}

Node *GetHuiBlyatNeZnay (Tokens *tokens, int *p)
{
    if (tokens->value[*p] == -1)
    {
        if (tokens->type[*p] == FUNCTION_WITH_ONE_ARG)
        {
            (*p)++;
            Node *name = NULL;
            if (tokens->type[*p] == NAME)
            {
                tokens->newNames->names[tokens->value[*p]].type = VARIABLE;
                name = nodeCtor (VARIABLE, tokens->value[*p], NULL, NULL);
                (*p)++;
            }
            return nodeCtor (FUNCTION_WITH_ONE_ARG, INT_V, name, NULL);
        } else if (tokens->type[*p] == FUNCTION_WITH_TWO_ARG)
        {
            (*p)++;
            Node *name = NULL;
            if (tokens->type[*p] == NAME)
            {
                tokens->newNames->names[tokens->value[*p]].type = FUNCTION;
                name = nodeCtor (FUNCTION, tokens->value[*p], NULL, NULL);
                (*p)++;
            }

            Node *arg = NULL;
            if (tokens->type[*p] == FUNCTION_WITH_NO_ARG && tokens->value[*p] == PARENTHESIS_L)
            {
                (*p)++;
                arg = nodeCtor (VARIABLE, tokens->value[*p], NULL, NULL);
                (*p) += 2;
            }

            return nodeCtor (FUNCTION_WITH_TWO_ARG, INT_F, name, arg);
        } 
        return NULL;
    } else 
        return NULL;
}