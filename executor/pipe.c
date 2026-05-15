#include "executor.h"

static void	close_pipe_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	run_left_pipe_child(t_ast *node, t_shell *shell, int fd[2])
{
	int	code;

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

static void	run_right_pipe_child(t_ast *node, t_shell *shell, int fd[2])
{
	int	code;

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

static void	wait_pipe_children(t_shell *shell, pid_t left_pid, pid_t right_pid)
{
	int	status;

	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	update_exit_status(shell, status);
}

void	exec_pipe(t_ast *node, t_shell *shell)
{
	int		fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(fd) == -1)
		return (perror("pipe"));
	left_pid = fork();
	if (left_pid == 0)
		run_left_pipe_child(node, shell, fd);
	right_pid = fork();
	if (right_pid == 0)
		run_right_pipe_child(node, shell, fd);
	close_pipe_fds(fd);
	wait_pipe_children(shell, left_pid, right_pid);
}