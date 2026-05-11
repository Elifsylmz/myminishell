#include "ast.h"

static t_ast    *parse_redirections(t_ast *cmd, t_token **tokens)
{
    t_ast   *redir;

    while (*tokens && ((*tokens)->type == T_REDIRECT_IN
            || (*tokens)->type == T_REDIRECT_OUT
            || (*tokens)->type == T_APPEND
            || (*tokens)->type == T_HEREDOC))
    {
        redir = new_node(NODE_REDIR);
        redir->redir_type = (*tokens)->type;
        *tokens = (*tokens)->next;
        if (!*tokens || (*tokens)->type != T_WORD)
            return (NULL);
        redir->file = ft_strdup((*tokens)->value);
        *tokens = (*tokens)->next;
        redir->left = cmd;
        cmd = redir;
    }
    return (cmd);
}

static t_ast    *parse_command(t_token **tokens)
{
    t_ast       *cmd;
    char        **argv;
    t_segment   **arg_segments;
    int         i;

    cmd = new_node(NODE_CMD);
    if (!cmd)
        return (NULL);
    argv = malloc(sizeof(char *) * 1024);
    arg_segments = malloc(sizeof(t_segment *) * 1024);
    if (!argv || !arg_segments)
        return (NULL);
    i = 0;
    while (*tokens && (*tokens)->type == T_WORD)
    {
        argv[i] = ft_strdup((*tokens)->value);
        arg_segments[i] = (*tokens)->segments;
        i++;
        *tokens = (*tokens)->next;
    }
    argv[i] = NULL;
    arg_segments[i] = NULL;
    cmd->argv = argv;
    cmd->arg_segments = arg_segments;
    cmd = parse_redirections(cmd, tokens);
    return (cmd);
}

t_ast   *parse_pipeline(t_token **tokens)
{
    t_ast   *left;
    t_ast   *node;

    left = parse_command(tokens);
    if (!left)
        return (NULL);
    while (*tokens && (*tokens)->type == T_PIPE)
    {
        *tokens = (*tokens)->next;
        node = new_node(NODE_PIPE);
        if (!node)
            return (NULL);
        node->left = left;
        node->right = parse_command(tokens);
        left = node;
    }
    return (left);
}