/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:52:54 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:20:19 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*join_home_path(char *home, char *arg)
{
	if (!home)
		return (NULL);
	if (arg[1] == '\0')
		return (ft_strdup(home));
	return (ft_strjoin(home, arg + 1));
}

static char	*get_oldpwd_path(t_shell *shell)
{
	char	*path;

	path = env_get(shell->env, "OLDPWD");
	if (path)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	return (path);
}

char	*get_cd_path(t_shell *shell, char **argv, int *need_free)
{
	*need_free = 0;
	if (!argv[1])
		return (env_get(shell->env, "HOME"));
	if (ft_strncmp(argv[1], "-", 2) == 0)
		return (get_oldpwd_path(shell));
	if (argv[1][0] == '~' && (argv[1][1] == '\0' || argv[1][1] == '/'))
	{
		*need_free = 1;
		return (join_home_path(env_get(shell->env, "HOME"), argv[1]));
	}
	return (argv[1]);
}

void	print_cd_path_error(char **argv)
{
	if (argv[1] && ft_strncmp(argv[1], "-", 2) == 0)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	else
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
}

void	update_pwd_values(t_shell *shell, char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (oldpwd)
		env_set(&shell->env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(&shell->env, "PWD", cwd);
}
