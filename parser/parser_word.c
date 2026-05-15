#include "parser.h"

static int	count_words_until_pipe(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->type == T_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_ast	*init_cmd_node(t_token *tokens)
{
	t_ast	*cmd;
	int		words;

	words = count_words_until_pipe(tokens);
	cmd = new_node(NODE_CMD);
	if (!cmd)
		return (NULL);
	cmd->argv = ft_calloc(words + 1, sizeof(char *));
	cmd->arg_segments = ft_calloc(words + 1, sizeof(t_segment *));
	if (!cmd->argv || !cmd->arg_segments)
		return (free_ast(cmd), NULL);
	return (cmd);
}

int	add_word(t_ast *cmd, t_token **tokens, int *i)
{
	cmd->argv[*i] = ft_strdup((*tokens)->value);
	cmd->arg_segments[*i] = dup_segments((*tokens)->segments);
	if (!cmd->argv[*i] || !cmd->arg_segments[*i])
		return (0);
	(*i)++;
	*tokens = (*tokens)->next;
	return (1);
}