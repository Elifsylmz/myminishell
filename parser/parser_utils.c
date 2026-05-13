#include "ast.h"
#include <unistd.h>

static void	remove_heredoc_file(t_ast *node)
{
	if (node->type != NODE_REDIR)
		return ;
	if (node->redir_type != T_HEREDOC)
		return ;
	if (!node->file)
		return ;
	if (ft_strncmp(node->file, ".heredoc_tmp_", 13) == 0)
		unlink(node->file);
}

static void	free_arg_segments(t_segment **arg_segments)
{
	int	i;

	if (!arg_segments)
		return ;
	i = 0;
	while (arg_segments[i])
	{
		free_segments(arg_segments[i]);
		i++;
	}
	free(arg_segments);
}

t_segment	*dup_segments(t_segment *src)
{
	t_segment	*new_list;
	t_segment	*new_seg;
	char		*value;

	new_list = NULL;
	while (src)
	{
		value = ft_strdup(src->value);
		if (!value)
			return (free_segments(new_list), NULL);
		new_seg = new_segment(value, src->quote);
		if (!new_seg)
		{
			free(value);
			free_segments(new_list);
			return (NULL);
		}
		add_segment(&new_list, new_seg);
		src = src->next;
	}
	return (new_list);
}

void	free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			free(node->argv[i]);
			i++;
		}
		free(node->argv);
	}
	free_arg_segments(node->arg_segments);
	free_segments(node->file_segments);
	remove_heredoc_file(node);
	free(node->file);
	free(node);
}

t_ast	*new_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->argv = NULL;
	node->arg_segments = NULL;
	node->redir_type = 0;
	node->file = NULL;
	node->file_segments = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}