#include "lexer.h"

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\t');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

t_segment	*extract_word(char *str, int *i)
{
	t_segment	*segs;
	char		*part;
	char		q;
	int			start;

	segs = NULL;
	while (str[*i] && !is_special(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			q = str[*i];
			(*i)++;
			start = *i;
			while (str[*i] && str[*i] != q)
				(*i)++;
			if (str[*i] != q)
			{
				free_segments(segs);
				return (NULL);
			}
			part = ft_substr(str, start, *i - start);
			if (q == '\'')
				add_segment(&segs, new_segment(part, Q_SINGLE));
			else
				add_segment(&segs, new_segment(part, Q_DOUBLE));
			(*i)++;
		}
		else
		{
			start = *i;
			while (str[*i] && !is_special(str[*i])
				&& str[*i] != '\'' && str[*i] != '"')
				(*i)++;
			part = ft_substr(str, start, *i - start);
			add_segment(&segs, new_segment(part, Q_NONE));
		}
	}
	return (segs);
}

char	*segments_to_value(t_segment *segs)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	while (segs)
	{
		tmp = ft_strjoin(result, segs->value);
		free(result);
		result = tmp;
		segs = segs->next;
	}
	return (result);
}