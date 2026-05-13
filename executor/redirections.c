#include "executor.h"

static int	open_heredoc_file(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror(".heredoc_tmp");
	return (fd);
}

static int	write_heredoc(char *limiter)
{
	char	*line;
	int		fd;

	fd = open_heredoc_file();
	if (fd < 0)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	return (0);
}

static int	open_heredoc(char *limiter)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		set_heredoc_signals();
		exit(write_heredoc(limiter));
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		unlink(".heredoc_tmp");
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 1);
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (-1);
	fd = open(".heredoc_tmp", O_RDONLY);
	unlink(".heredoc_tmp");
	return (fd);
}

static int	apply_input_redir(t_ast *node)
{
	int	fd;

	if (node->redir_type == T_HEREDOC)
		fd = open_heredoc(node->file);
	else
		fd = open(node->file, O_RDONLY);
	if (fd < 0)
	{
		if (node->redir_type != T_HEREDOC)
			perror(node->file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	apply_output_redir(t_ast *node)
{
	int	fd;

	if (node->redir_type == T_REDIRECT_OUT)
		fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(node->file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_ast *node)
{
	if (!node || node->type != NODE_REDIR)
		return (0);
	if (apply_redirections(node->left) != 0)
		return (1);
	if (node->redir_type == T_REDIRECT_IN || node->redir_type == T_HEREDOC)
		return (apply_input_redir(node));
	return (apply_output_redir(node));
}