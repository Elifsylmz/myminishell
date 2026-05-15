/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:19 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:18:42 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expand_segments(t_shell *shell, t_segment *segs)
{
	char	*result;
	char	*tmp;
	char	*part;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (segs)
	{
		if (segs->quote == Q_SINGLE)
			part = ft_strdup(segs->value);
		else
			part = expand_str(shell, segs->value);
		if (!part)
			return (free(result), NULL);
		tmp = ft_strjoin(result, part);
		free(result);
		free(part);
		if (!tmp)
			return (NULL);
		result = tmp;
		segs = segs->next;
	}
	return (result);
}

void	expand_ast(t_shell *shell, t_ast *cmd)
{
	int		i;
	char	*expanded;

	i = 0;
	if (!cmd || !cmd->argv)
		return ;
	while (cmd->argv[i])
	{
		expanded = expand_segments(shell, cmd->arg_segments[i]);
		if (!expanded)
			return ;
		free(cmd->argv[i]);
		cmd->argv[i] = expanded;
		i++;
	}
}

void	expand_redirections(t_shell *shell, t_ast *node)
{
	char	*expanded;

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		expand_redirections(shell, node->left);
		expand_redirections(shell, node->right);
		return ;
	}
	if (node->type != NODE_REDIR)
		return ;
	expand_redirections(shell, node->left);
	if (node->redir_type == T_HEREDOC)
		return ;
	expanded = expand_segments(shell, node->file_segments);
	if (!expanded)
		return ;
	free(node->file);
	node->file = expanded;
}
