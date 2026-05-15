/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:08 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:24:35 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	str_cmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

static int	is_after_prev(char *key, char *prev)
{
	if (!prev)
		return (1);
	if (str_cmp(key, prev) > 0)
		return (1);
	return (0);
}

static t_env	*find_next_env(t_env *env, char *prev)
{
	t_env	*next;

	next = NULL;
	while (env)
	{
		if (is_after_prev(env->key, prev))
		{
			if (!next || str_cmp(env->key, next->key) < 0)
				next = env;
		}
		env = env->next;
	}
	return (next);
}

static void	print_export_value(char *value)
{
	int	i;

	i = 0;
	ft_putstr_fd("=\"", 1);
	while (value && value[i])
	{
		if (value[i] == '"' || value[i] == '\\' || value[i] == '$'
			|| value[i] == '`')
			ft_putchar_fd('\\', 1);
		ft_putchar_fd(value[i], 1);
		i++;
	}
	ft_putstr_fd("\"", 1);
}

int	print_export(t_env *env)
{
	t_env	*next;
	char	*prev;

	prev = NULL;
	while (1)
	{
		next = find_next_env(env, prev);
		if (!next)
			break ;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(next->key, 1);
		if (next->has_value)
			print_export_value(next->value);
		ft_putstr_fd("\n", 1);
		prev = next->key;
	}
	return (0);
}
