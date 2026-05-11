#include "executor.h"
#include "builtins/builtins.h"
#include "expander/expander.h"

static int	apply_redirections(t_ast *node)
{
	int		fd;
	pid_t	pid;
	int		status;
	char	*line;

	if (!node || node->type != NODE_REDIR)
		return (0);
	if (apply_redirections(node->left) != 0)
		return (1);
	if (node->redir_type == T_REDIRECT_IN)
	{
		fd = open(node->file, O_RDONLY);
		if (fd < 0)
		{
			perror(node->file);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (node->redir_type == T_REDIRECT_OUT)
	{
		fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(node->file);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (node->redir_type == T_APPEND)
	{
		fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(node->file);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (node->redir_type == T_HEREDOC)
	{
		pid = fork();
		if (pid == 0)
		{
			set_heredoc_signals();
			fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(".heredoc_tmp");
				exit(1);
			}
			while (1)
			{
				line = readline("> ");
				if (!line)
					break ;
				if (ft_strncmp(line, node->file, ft_strlen(node->file)
						+ 1) == 0)
				{
					free(line);
					break ;
				}
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
				free(line);
			}
			close(fd);
			exit(0);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (1);
		if (WIFSIGNALED(status))
		{
			write(1, "\n", 1);
			return (1);
		}
		fd = open(".heredoc_tmp", O_RDONLY);
		if (fd >= 0)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
			unlink(".heredoc_tmp");
		}
	}
	return (0);
}