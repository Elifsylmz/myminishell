#include "lexer.h"

t_segment	*new_segment(char *value, t_quote_type quote)
{
	t_segment	*seg;

	seg = malloc(sizeof(t_segment));
	seg->value = value;
	seg->quote = quote;
	seg->next = NULL;
	return (seg);
}

void	add_segment(t_segment **list, t_segment *seg)
{
	t_segment	*tmp;

	if (!*list)
	{
		*list = seg;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = seg;
}

void	free_segments(t_segment *list)
{
	t_segment	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}