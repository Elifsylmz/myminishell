#include "ast.h"

void    free_ast(t_ast *node)
{
    int i;

    if (!node)
        return ;
    free_ast(node->left);
    free_ast(node->right);
    if (node->argv)
    {
        i = 0;
        while (node->argv[i])
            free(node->argv[i++]);
        free(node->argv);
    }
    free(node->arg_segments);
    free(node->file);
    free(node);
}

t_ast   *new_node(t_node_type type)
{
    t_ast   *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = type;
    node->argv = NULL;
    node->arg_segments = NULL;
    node->file = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}