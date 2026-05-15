/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:52:52 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:25:28 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strncmp(cmd, "cd", 3) == 0 || ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "env", 4) == 0 || ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0 || ft_strncmp(cmd, "exit", 5) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0);
}

int	run_builtin(t_shell *shell, char **argv)
{
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (builtin_cd(shell, argv));
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (builtin_echo(shell, argv));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (builtin_env(shell, argv));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (builtin_export(shell, argv));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (builtin_unset(shell, argv));
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (builtin_exit(shell, argv));
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (builtin_pwd(shell, argv));
	return (127);
}
