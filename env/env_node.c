/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:52:42 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:44:19 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*env_new_node(char *key, char *value, int has_value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->has_value = has_value;
	node->next = NULL;
	if (!node->key || (value && !node->value))
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}

void	env_append_node(t_env **env, t_env *node)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}
