/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:35 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:09:15 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <sys/stat.h>

char	**find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

static int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

static int	is_executable(char *path)
{
	if (access(path, F_OK) != 0)
		return (0);
	if (is_directory(path))
		return (0);
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

char	*find_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/') && is_executable(cmd))
		return (ft_strdup(cmd));
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (is_executable(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
