/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:52:56 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:23:21 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*path;
	char	*oldpwd;
	int		need_free;

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	oldpwd = env_get(shell->env, "PWD");
	path = get_cd_path(shell, argv, &need_free);
	if (!path)
		return (print_cd_path_error(argv), (1));
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		if (need_free)
			free(path);
		return (1);
	}
	if (need_free)
		free(path);
	update_pwd_values(shell, oldpwd);
	return (0);
}
