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

static void	execve_or_exit(t_shell *shell, t_ast *cmd, t_exec_data *data)
{
	int	err;

	execve(data->cmd_path, cmd->argv, data->envp);
	err = errno;
	print_cmd_error(cmd->argv[0], strerror(err));
	free(data->cmd_path);
	free_array(data->paths);
	free_array(data->envp);
	child_cleanup(shell);
	exit(execve_exit_code(err));
}

void	exec_cmd(t_ast *node, t_shell *shell)
{
	t_ast		*cmd;
	t_exec_data	data;

	data.cmd_path = NULL;
	data.envp = NULL;
	data.paths = NULL;
	prepare_cmd(node, shell, &cmd);
	data.cmd_path = resolve_cmd_path(shell, cmd, &data.envp, &data.paths);
	if (!data.cmd_path)
	{
		free_array(data.paths);
		free_array(data.envp);
		command_not_found(cmd->argv[0], shell);
	}
	execve_or_exit(shell, cmd, &data);
}
