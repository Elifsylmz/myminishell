/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:52:39 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:43:26 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*env_init(char **envp)
{
	t_env		*list;
	char		*eq;
	char		*key;
	int			i;

	list = NULL;
	i = 0;
	while (envp && envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			key = ft_substr(envp[i], 0, eq - envp[i]);
			if (key)
			{
				env_set(&list, key, eq + 1);
				free(key);
			}
		}
		i++;
	}
	return (list);
}
