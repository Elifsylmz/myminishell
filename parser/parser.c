/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:54:33 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:03:00 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_command_token(t_ast **root, t_ast *cmd, t_token **tokens,
		int *i)
{
	t_ast	*tmp;

	if ((*tokens)->type == T_WORD)
	{
		if (!add_word(cmd, tokens, i))
			return (0);
	}
	else if (is_redir((*tokens)->type))
	{
		tmp = add_redir(*root, tokens);
		if (!tmp)
			return (0);
		*root = tmp;
	}
	else
		return (0);
	return (1);
}

static t_ast	*parse_command(t_token **tokens)
{
	t_ast	*cmd;
	t_ast	*root;
	int		i;

	cmd = init_cmd_node(*tokens);
	if (!cmd)
		return (NULL);
	root = cmd;
	i = 0;
	while (*tokens && (*tokens)->type != T_PIPE)
	{
		if (!parse_command_token(&root, cmd, tokens, &i))
			return (free_ast(root), NULL);
	}
	cmd->argv[i] = NULL;
	cmd->arg_segments[i] = NULL;
	return (root);
}

static t_ast	*parse_next_pipe(t_ast *left, t_token **tokens)
{
	t_ast	*node;

	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type == T_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near pipe\n", 2);
		free_ast(left);
		return (NULL);
	}
	node = new_node(NODE_PIPE);
	if (!node)
		return (free_ast(left), NULL);
	node->left = left;
	node->right = parse_command(tokens);
	if (!node->right)
		return (free_ast(node), NULL);
	return (node);
}

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;

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
		left = parse_next_pipe(left, tokens);
		if (!left)
			return (NULL);
	}
	return (left);
}
