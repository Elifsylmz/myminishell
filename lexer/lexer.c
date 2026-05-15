/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:54:11 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:05:00 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer(char *prompt)
{
	int			i;
	t_token		*list;

	i = 0;
	list = NULL;
	while (prompt[i])
	{
		if (!handle_token(prompt, &i, &list))
			return (NULL);
	}
	return (list);
}
