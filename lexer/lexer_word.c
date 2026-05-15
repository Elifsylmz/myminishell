/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:54:09 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:06:45 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\t');
}

static t_segment	*extract_quoted_part(char *str, int *i)
{
	t_segment	*seg;
	char		*part;
	char		q;
	int			start;

	q = str[*i];
	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != q)
		(*i)++;
	if (str[*i] != q)
		return (NULL);
	part = ft_substr(str, start, *i - start);
	if (!part)
		return (NULL);
	if (q == '\'')
		seg = new_segment(part, Q_SINGLE);
	else
		seg = new_segment(part, Q_DOUBLE);
	if (!seg)
		return (free(part), NULL);
	(*i)++;
	return (seg);
}

static t_segment	*extract_plain_part(char *str, int *i)
{
	t_segment	*seg;
	char		*part;
	int			start;

	start = *i;
	while (str[*i] && !is_special(str[*i]) && str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	part = ft_substr(str, start, *i - start);
	if (!part)
		return (NULL);
	seg = new_segment(part, Q_NONE);
	if (!seg)
		return (free(part), NULL);
	return (seg);
}

t_segment	*extract_word(char *str, int *i)
{
	t_segment	*segs;
	t_segment	*new_seg;

	segs = NULL;
	while (str[*i] && !is_special(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '"')
			new_seg = extract_quoted_part(str, i);
		else
			new_seg = extract_plain_part(str, i);
		if (!new_seg)
		{
			free_segments(segs);
			return (NULL);
		}
		add_segment(&segs, new_seg);
	}
	return (segs);
}

char	*segments_to_value(t_segment *segs)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (segs)
	{
		tmp = ft_strjoin(result, segs->value);
		free(result);
		if (!tmp)
			return (NULL);
		result = tmp;
		segs = segs->next;
	}
	return (result);
}
