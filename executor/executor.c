/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:30 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:13:07 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	update_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->last_exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
		else if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
	}
}

void	child_cleanup(t_shell *shell)
{
	free_tokens(shell->lex);
	free_ast(shell->ast);
	env_free(&shell->env);
	free(shell);
}

static void	execute_builtin(t_shell *shell, t_ast *cmd)
{
	int	saved_std[3];

	saved_std[0] = dup(STDIN_FILENO);
	saved_std[1] = dup(STDOUT_FILENO);
	saved_std[2] = dup(STDERR_FILENO);
	if (apply_redirections(shell->ast) == 0)
		shell->last_exit_code = run_builtin(shell, cmd->argv);
	else
		shell->last_exit_code = 1;
	dup2(saved_std[0], STDIN_FILENO);
	dup2(saved_std[1], STDOUT_FILENO);
	dup2(saved_std[2], STDERR_FILENO);
	close(saved_std[0]);
	close(saved_std[1]);
	close(saved_std[2]);
}

static void	execute_external(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		shell->last_exit_code = 1;
		return ;
	}
	if (pid == 0)
	{
		set_child_signals();
		exec_cmd(shell->ast, shell);
	}
	waitpid(pid, &status, 0);
	update_exit_status(shell, status);
}

void	execute(t_shell *shell)
{
	t_ast	*cmd;

	if (!shell->ast)
		return ;
	if (shell->ast->type == NODE_PIPE)
	{
		exec_pipe(shell->ast, shell);
		return ;
	}
	cmd = get_cmd(shell->ast);
	if (cmd)
		expand_ast(shell, cmd);
	expand_redirections(shell, shell->ast);
	if (cmd && cmd->argv[0] && is_builtin(cmd->argv[0]))
	{
		execute_builtin(shell, cmd);
		return ;
	}
	execute_external(shell);
}
