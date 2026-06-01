/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:38 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/06/01 17:30:17 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	is_quoted_delimiter(t_segment *segments)
{
	while (segments)
	{
		if (segments->quote != Q_NONE)
			return (1);
		segments = segments->next;
	}
	return (0);
}

static int	write_heredoc_line(t_shell *shell, int fd, char *line, int expand)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_str(shell, line);
		if (!expanded)
			return (1);
		ft_putstr_fd(expanded, fd);
		free(expanded);
	}
	else
		ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	return (0);
}

static int	read_heredoc_loop(t_shell *shell, t_ast *node, int fd, int expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, node->file,
				ft_strlen(node->file) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (write_heredoc_line(shell, fd, line, expand) != 0)
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

void	run_heredoc_child(t_shell *shell, t_ast *node, char *filename)
{
	int	fd;
	int	expand;
	int	code;

	set_heredoc_signals();
	expand = !is_quoted_delimiter(node->file_segments);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		free(filename);
		child_cleanup(shell);
		exit(1);
	}
	code = read_heredoc_loop(shell, node, fd, expand);
	close(fd);
	free(filename);
	child_cleanup(shell);
	exit(code);
}
