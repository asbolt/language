#include "../h_files/rekursivnaya_eblya_materi.h"

int treeDump (Node *node)
{
    printf ("(%d %d", node->type, node->value);

    if (node->left != NULL)
        treeDump (node->left);
    else
        printf ("(*)");

    if (node->right != NULL)
        treeDump (node->right);
    else 
        printf ("(*)");

    printf (")");

    return 0;
}