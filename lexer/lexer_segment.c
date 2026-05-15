/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:52 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:06:04 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_segment	*new_segment(char *value, t_quote_type quote)
{
	t_segment	*seg;

	seg = malloc(sizeof(t_segment));
	if (!seg)
		return (NULL);
	seg->value = value;
	seg->quote = quote;
	seg->next = NULL;
	return (seg);
}

void	add_segment(t_segment **list, t_segment *seg)
{
	t_segment	*tmp;

	if (!seg)
		return ;
	if (!*list)
	{
		*list = seg;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = seg;
}

void	free_segments(t_segment *list)
{
	t_segment	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}
