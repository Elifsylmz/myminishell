#include "ast.h"


static int	is_redir(t_token_type type)
{
	return (type == T_REDIRECT_IN || type == T_REDIRECT_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

static int	count_words_until_pipe(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->type == T_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static int	add_word(t_ast *cmd, t_token **tokens, int *i)
{
	cmd->argv[*i] = ft_strdup((*tokens)->value);
	cmd->arg_segments[*i] = dup_segments((*tokens)->segments);
	if (!cmd->argv[*i] || !cmd->arg_segments[*i])
		return (0);
	(*i)++;
	*tokens = (*tokens)->next;
	return (1);
}

static t_ast	*add_redir(t_ast *root, t_token **tokens)
{
	t_ast	*redir;

	redir = new_node(NODE_REDIR);
	if (!redir)
		return (NULL);
	redir->redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != T_WORD)
	{
		ft_putstr_fd("minishell: syntax error near redirection\n", 2);
		free(redir);
		return (NULL);
	}
	redir->file = ft_strdup((*tokens)->value);
	redir->file_segments = dup_segments((*tokens)->segments);
	if (!redir->file || !redir->file_segments)
	{
		free_ast(redir);
		return (NULL);
	}
	*tokens = (*tokens)->next;
	redir->left = root;
	return (redir);
}

static t_ast	*parse_command(t_token **tokens)
{
	t_ast	*cmd;
	t_ast	*root;
	int		i;
	int		words;

	words = count_words_until_pipe(*tokens);
	cmd = new_node(NODE_CMD);
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *) * (words + 1));
	cmd->arg_segments = malloc(sizeof(t_segment *) * (words + 1));
	if (!cmd->argv || !cmd->arg_segments)
		return (free_ast(cmd), NULL);
	i = 0;
	root = cmd;
	while (*tokens && (*tokens)->type != T_PIPE)
	{
		if ((*tokens)->type == T_WORD)
		{
			if (!add_word(cmd, tokens, &i))
				return (free_ast(root), NULL);
		}
		else if (is_redir((*tokens)->type))
		{
			root = add_redir(root, tokens);
			if (!root)
				return (free_ast(cmd), NULL);
		}
		else
			return (free_ast(root), NULL);
	}
	cmd->argv[i] = NULL;
	cmd->arg_segments[i] = NULL;
	return (root);
}

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*node;

	if (!tokens || !*tokens || (*tokens)->type == T_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near pipe\n", 2);
		return (NULL);
	}
	left = parse_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == T_PIPE)
	{
		*tokens = (*tokens)->next;
		if (!*tokens || (*tokens)->type == T_PIPE)
		{
			ft_putstr_fd("minishell: syntax error near pipe\n", 2);
			return (free_ast(left), NULL);
		}
		node = new_node(NODE_PIPE);
		if (!node)
			return (free_ast(left), NULL);
		node->left = left;
		node->right = parse_command(tokens);
		if (!node->right)
			return (free_ast(node), NULL);
		left = node;
	}
	return (left);
}