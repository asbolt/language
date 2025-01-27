#include "h_files/tokens.h"
#include "h_files/rekursivnaya_eblya_materi.h"

int main ()
{
    Tokens *tokens = dispetcher ("file.txt");
    tokenDump (tokens);
    int p = 0;
    Node *node = GetEnd (tokens, &p);
    treeDump (node);
    return 0;
}