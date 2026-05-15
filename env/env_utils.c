/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:52:46 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:45:01 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	count_env_values(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->has_value)
			count++;
		env = env->next;
	}
	return (count);
}

static char	*join_env_value(t_env *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, env->value);
	free(tmp);
	return (result);
}

static void	fill_env_array(char **arr, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->has_value)
		{
			arr[i] = join_env_value(env);
			i++;
		}
		env = env->next;
	}
	arr[i] = NULL;
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	int		count;

	count = count_env_values(env);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	fill_env_array(arr, env);
	return (arr);
}

void	env_free(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}
