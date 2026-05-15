#include "lexer.h"

t_token	*lexer(char *prompt)
{
	int		i;
	t_token	*list;

	i = 0;
	list = NULL;
	while (prompt[i])
	{
		if (!handle_token(prompt, &i, &list))
			return (NULL);
	}
	return (list);
}