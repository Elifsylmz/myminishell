#include "executor.h"

static void	exec_pipe(t_ast *node, t_shell *shell)
{
	int		fd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	t_shell	left;
	t_shell	right;
	int		status;

	pipe(fd);
	left = *shell;
	left.ast = node->left;
	right = *shell;
	right.ast = node->right;
	left_pid = fork();
	if (left_pid == 0)
	{
		set_child_signals();
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(&left);
		exit(left.last_exit_code);
	}
	right_pid = fork();
	if (right_pid == 0)
	{
		set_child_signals();
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute(&right);
		exit(right.last_exit_code);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		shell->last_exit_code = 128 + WTERMSIG(status);
	}
}

void	execute(t_shell *shell)
{
	pid_t	pid;
	int		status;
	t_ast	*cmd;
	int		saved_stdin;
	int		saved_stdout;

	if (!shell->ast)
		return ;
	if (shell->ast->type == NODE_PIPE)
	{
		exec_pipe(shell->ast, shell);
		return ;
	}
	cmd = get_cmd(shell->ast);
	if (cmd && cmd->argv[0] && is_builtin(cmd->argv[0]))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (apply_redirections(shell->ast) != 0)
		{
			shell->last_exit_code = 1;
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return ;
		}
		expand_ast(shell, cmd);
		shell->last_exit_code = run_builtin(shell, cmd->argv);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		set_child_signals();
		exec_cmd(shell->ast, shell);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
			shell->last_exit_code = 128 + WTERMSIG(status);
		}
	}
	else
		perror("fork");
}