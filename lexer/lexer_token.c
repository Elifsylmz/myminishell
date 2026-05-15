/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:54:05 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:06:16 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(char *value, t_token_type type, t_quote_type quote)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = value;
	tok->type = type;
	tok->quote = quote;
	tok->segments = NULL;
	tok->redir_fd = -1;
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **list, t_token *newtkn)
{
	t_token	*tmp;

	if (!newtkn)
		return ;
	if (!*list)
	{
		*list = newtkn;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newtkn;
}

void	free_tokens(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free_segments(list->segments);
		free(list);
		list = tmp;
	}
}
