#include "parser.h"

static int	default_redir_fd(t_token_type type)
{
	if (type == T_REDIRECT_IN || type == T_HEREDOC)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

int	is_redir(t_token_type type)
{
	return (type == T_REDIRECT_IN || type == T_REDIRECT_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

static int	set_redir_file(t_ast *redir, t_token **tokens)
{
	if (!*tokens || (*tokens)->type != T_WORD)
	{
		ft_putstr_fd("minishell: syntax error near redirection\n", 2);
		return (0);
	}
	redir->file = ft_strdup((*tokens)->value);
	redir->file_segments = dup_segments((*tokens)->segments);
	if (!redir->file || !redir->file_segments)
		return (0);
	*tokens = (*tokens)->next;
	return (1);
}

t_ast	*add_redir(t_ast *root, t_token **tokens)
{
	t_ast	*redir;

	redir = new_node(NODE_REDIR);
	if (!redir)
		return (NULL);
	redir->redir_type = (*tokens)->type;
	redir->redir_fd = (*tokens)->redir_fd;
	if (redir->redir_fd == -1)
		redir->redir_fd = default_redir_fd(redir->redir_type);
	*tokens = (*tokens)->next;
	if (!set_redir_file(redir, tokens))
	{
		free_ast(redir);
		return (NULL);
	}
	redir->left = root;
	return (redir);
}