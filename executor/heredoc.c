/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:42 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:09:52 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

static int	handle_heredoc_node(t_shell *shell, t_ast *node, int *counter)
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
		run_heredoc_child(shell, node, filename);
	if (wait_heredoc(pid, filename) != 0)
		return (1);
	free(node->file);
	node->file = filename;
	return (0);
}

int	process_heredocs(t_shell *shell, t_ast *node, int *counter)
{
	if (!node)
		return (0);
	if (process_heredocs(shell, node->left, counter) != 0)
		return (1);
	if (process_heredocs(shell, node->right, counter) != 0)
		return (1);
	if (node->type == NODE_REDIR && node->redir_type == T_HEREDOC)
		return (handle_heredoc_node(shell, node, counter));
	return (0);
}
