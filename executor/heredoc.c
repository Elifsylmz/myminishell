#include "executor.h"

static void	run_heredoc_child(t_ast *node, char *filename)
{
	int		fd;
	char	*line;

	set_heredoc_signals();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, node->file,
				ft_strlen(node->file) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	exit(0);
}

static int	wait_heredoc(pid_t pid, char *filename)
{
	int	status;

	start_execution_signals();
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		unlink(filename);
		free(filename);
		return (1);
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 1);
		unlink(filename);
		free(filename);
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(filename);
		free(filename);
		return (1);
	}
	return (0);
}

static char	*make_heredoc_name(int *counter)
{
	char	*num_str;
	char	*filename;

	num_str = ft_itoa(*counter);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin(".heredoc_tmp_", num_str);
	free(num_str);
	if (!filename)
		return (NULL);
	(*counter)++;
	return (filename);
}

static int	handle_heredoc_node(t_ast *node, int *counter)
{
	pid_t	pid;
	char	*filename;

	filename = make_heredoc_name(counter);
	if (!filename)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(filename);
		return (1);
	}
	if (pid == 0)
		run_heredoc_child(node, filename);
	if (wait_heredoc(pid, filename) != 0)
		return (1);
	free(node->file);
	node->file = filename;
	return (0);
}

int	process_heredocs(t_ast *node, int *counter)
{
	if (!node)
		return (0);
	if (process_heredocs(node->left, counter) != 0)
		return (1);
	if (process_heredocs(node->right, counter) != 0)
		return (1);
	if (node->type == NODE_REDIR && node->redir_type == T_HEREDOC)
		return (handle_heredoc_node(node, counter));
	return (0);
}