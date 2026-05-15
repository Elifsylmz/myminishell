/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:02 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:24:57 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(t_shell *shell, char **argv)
{
	t_env	*env;

	(void)argv;
	env = shell->env;
	while (env)
	{
		if (env->has_value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}
