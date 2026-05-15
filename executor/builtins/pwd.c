/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:12 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:25:07 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_pwd(t_shell *shell, char **argv)
{
	char	cwd[1024];

	(void)shell;
	(void)argv;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: pwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
