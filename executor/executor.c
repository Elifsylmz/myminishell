#include "executor.h"

static void	update_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_code = 128 + WTERMSIG(status);
}

void	child_cleanup(t_shell *shell)
{
	free_tokens(shell->lex);
	free_ast(shell->ast);
	env_free(&shell->env);
	free(shell);
}

static void	exec_pipe(t_ast *node, t_shell *shell)
{
	int		fd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;
	int		code;

	if (pipe(fd) == -1)
		return (perror("pipe"));
	left_pid = fork();
	if (left_pid == 0)
	{
		set_child_signals();
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		shell->ast = node->left;
		execute(shell);
		code = shell->last_exit_code;
		shell->ast = node;
		child_cleanup(shell);
		exit(code);
	}
	right_pid = fork();
	if (right_pid == 0)
	{
		set_child_signals();
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		shell->ast = node->right;
		execute(shell);
		code = shell->last_exit_code;
		shell->ast = node;
		child_cleanup(shell);
		exit(code);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	update_exit_status(shell, status);
}

static void	execute_builtin(t_shell *shell, t_ast *cmd)
{
	int	saved_std[2];

	saved_std[0] = dup(STDIN_FILENO);
	saved_std[1] = dup(STDOUT_FILENO);
	if (apply_redirections(shell->ast) == 0)
		shell->last_exit_code = run_builtin(shell, cmd->argv);
	else
		shell->last_exit_code = 1;
	dup2(saved_std[0], STDIN_FILENO);
	dup2(saved_std[1], STDOUT_FILENO);
	close(saved_std[0]);
	close(saved_std[1]);
}

static void	execute_external(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		set_child_signals();
		exec_cmd(shell->ast, shell);
	}
	else
	{
		waitpid(pid, &status, 0);
		update_exit_status(shell, status);
	}
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