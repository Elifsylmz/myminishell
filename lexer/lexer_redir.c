/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:50 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:05:49 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*redir_token(char *value, t_token_type type, int *i, int step)
{
	char	*str;
	t_token	*tok;

	str = ft_strdup(value);
	if (!str)
		return (NULL);
	tok = new_token(str, type, Q_NONE);
	if (!tok)
	{
		free(str);
		return (NULL);
	}
	*i += step;
	return (tok);
}

t_token	*handle_redirect(char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
		return (redir_token("<<", T_HEREDOC, i, 2));
	if (str[*i] == '<')
		return (redir_token("<", T_REDIRECT_IN, i, 1));
	if (str[*i] == '>' && str[*i + 1] == '>')
		return (redir_token(">>", T_APPEND, i, 2));
	if (str[*i] == '>')
		return (redir_token(">", T_REDIRECT_OUT, i, 1));
	return (NULL);
}

int	is_fd_redir(char *str, int i)
{
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}

static int	get_fd_number(char *str, int *i)
{
	int	fd;

	fd = 0;
	while (ft_isdigit(str[*i]))
	{
		fd = fd * 10 + str[*i] - '0';
		(*i)++;
	}
	return (fd);
}

t_token	*handle_fd_redirect(char *str, int *i)
{
	t_token	*tok;
	int		fd;

	fd = get_fd_number(str, i);
	tok = handle_redirect(str, i);
	if (!tok)
		return (NULL);
	tok->redir_fd = fd;
	return (tok);
}
