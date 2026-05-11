#include "expander.h"

static char	*expand_segments(t_shell *shell, t_segment *segs)
{
	char	*result;
	char	*tmp;
	char	*part;

	result = ft_strdup("");
	while (segs)
	{
		if (segs->quote == Q_SINGLE)
			part = ft_strdup(segs->value);
		else
			part = expand_str(shell, segs->value);
		tmp = ft_strjoin(result, part);
		free(result);
		free(part);
		result = tmp;
		segs = segs->next;
	}
	return (result);
}

void	expand_ast(t_shell *shell, t_ast *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->argv)
		return ;
	while (cmd->argv[i])
	{
		free(cmd->argv[i]);
		cmd->argv[i] = expand_segments(shell, cmd->arg_segments[i]);
		i++;
	}
}
