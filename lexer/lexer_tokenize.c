/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:54:07 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:06:25 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

static int	add_pipe_token(t_token **list, int *i)
{
	t_token	*tok;
	char	*value;

	value = ft_strdup("|");
	if (!value)
		return (0);
	tok = new_token(value, T_PIPE, Q_NONE);
	if (!tok)
	{
		free(value);
		return (0);
	}
	add_token(list, tok);
	(*i)++;
	return (1);
}

static int	add_redir_token(char *prompt, int *i, t_token **list)
{
	t_token	*tok;

	if (is_fd_redir(prompt, *i))
		tok = handle_fd_redirect(prompt, i);
	else
		tok = handle_redirect(prompt, i);
	if (!tok)
	{
		free_tokens(*list);
		return (0);
	}
	add_token(list, tok);
	return (1);
}

static int	add_word_token(char *prompt, int *i, t_token **list)
{
	t_token		*tok;
	t_segment	*segs;
	char		*value;

	segs = extract_word(prompt, i);
	if (!segs)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		free_tokens(*list);
		return (0);
	}
	value = segments_to_value(segs);
	if (!value)
		return (free_segments(segs), free_tokens(*list), 0);
	tok = new_token(value, T_WORD, Q_NONE);
	if (!tok)
		return (free(value), free_segments(segs), free_tokens(*list), 0);
	tok->segments = segs;
	add_token(list, tok);
	return (1);
}

int	handle_token(char *prompt, int *i, t_token **list)
{
	if (is_whitespace(prompt[*i]))
	{
		(*i)++;
		return (1);
	}
	if (prompt[*i] == '|')
		return (add_pipe_token(list, i));
	if (prompt[*i] == '<' || prompt[*i] == '>' || is_fd_redir(prompt, *i))
		return (add_redir_token(prompt, i, list));
	return (add_word_token(prompt, i, list));
}
