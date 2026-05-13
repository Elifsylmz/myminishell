#include "lexer.h"

t_segment   *new_segment(char *value, t_quote_type quote)
{
    t_segment   *seg;

    seg = malloc(sizeof(t_segment));
    seg->value = value;
    seg->quote = quote;
    seg->next = NULL;
    return (seg);
}

void    add_segment(t_segment **list, t_segment *seg)
{
    t_segment   *tmp;

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

void    free_segments(t_segment *list)
{
    t_segment   *tmp;

    while (list)
    {
        tmp = list->next;
        free(list->value);
        free(list);
        list = tmp;
    }
}

t_token	*new_token(char *value, t_token_type type, t_quote_type quote)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = value;
	tok->type = type;
	tok->quote = quote;
	tok->segments = NULL;
	tok->redir_fd = -1;
	tok->next = NULL;
	return (tok);
}

void    add_token(t_token **list, t_token *newtkn)
{
    t_token *tmp;

    if (!*list)
    {
        *list = newtkn;
        return ;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = newtkn;
}

void    free_tokens(t_token *list)
{
    t_token *tmp;

    while (list)
    {
        tmp = list->next;
        if (list->value)
            free(list->value);
        if (list->segments)
            free_segments(list->segments);
        free(list);
        list = tmp;
    }
}