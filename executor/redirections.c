#include "executor.h"

static int	apply_input_redirection(t_ast *node)
{
	int	fd;

	fd = open(node->file, O_RDONLY);
	if (fd < 0)
	{
		perror(node->file);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	apply_output_redirection(t_ast *node)
{
	int	fd;

	if (node->redir_type == T_REDIRECT_OUT)
		fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(node->file);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
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
		return (apply_input_redirection(node));
	return (apply_output_redirection(node));
}