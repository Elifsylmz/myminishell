/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:26 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:16:55 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <errno.h>
#include <string.h>

t_ast	*get_cmd(t_ast *node)
{
	while (node && node->type == NODE_REDIR)
		node = node->left;
	return (node);
}

static void	prepare_cmd(t_ast *node, t_shell *shell, t_ast **cmd)
{
	int	code;

	if (apply_redirections(node) != 0)
	{
		child_cleanup(shell);
		exit(1);
	}
	*cmd = get_cmd(node);
	if (!*cmd || !(*cmd)->argv[0])
	{
		child_cleanup(shell);
		exit(0);
	}
	code = check_cmd_before_exec(*cmd);
	if (code)
	{
		child_cleanup(shell);
		exit(code);
	}
}

static char	*resolve_cmd_path(t_shell *shell, t_ast *cmd, char ***envp,
		char ***paths)
{
	*envp = env_to_array(shell->env);
	*paths = find_path(*envp);
	return (find_cmd_path(*paths, cmd->argv[0]));
}

static void	execve_or_exit(char *cmd_path, t_ast *cmd, char **envp,
		char **paths, t_shell *shell)
{
	int	err;

	execve(cmd_path, cmd->argv, envp);
	err = errno;
	print_cmd_error(cmd->argv[0], strerror(err));
	free(cmd_path);
	free_array(paths);
	free_array(envp);
	child_cleanup(shell);
	exit(execve_exit_code(err));
}

void	exec_cmd(t_ast *node, t_shell *shell)
{
	char	**paths;
	char	*cmd_path;
	char	**envp;
	t_ast	*cmd;

	paths = NULL;
	envp = NULL;
	prepare_cmd(node, shell, &cmd);
	cmd_path = resolve_cmd_path(shell, cmd, &envp, &paths);
	if (!cmd_path)
	{
		free_array(paths);
		free_array(envp);
		command_not_found(cmd->argv[0], shell);
	}
	execve_or_exit(cmd_path, cmd, envp, paths, shell);
}
