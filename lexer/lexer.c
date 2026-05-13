#include "lexer.h"

static t_token	*handle_redirect(char *str, int *i)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			*i += 2;
			return (new_token(ft_strdup("<<"), T_HEREDOC, Q_NONE));
		}
		(*i)++;
		return (new_token(ft_strdup("<"), T_REDIRECT_IN, Q_NONE));
	}
	if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			*i += 2;
			return (new_token(ft_strdup(">>"), T_APPEND, Q_NONE));
		}
		(*i)++;
		return (new_token(ft_strdup(">"), T_REDIRECT_OUT, Q_NONE));
	}
	return (NULL);
}

static int	is_fd_redir(char *str, int i)
{
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}

static int	get_fd_number(char *str, int *i)
{
	int	fd;

	fd = 0;
	while (ft_isdigit(str[*i]))
	{
		fd = fd * 10 + str[*i] - '0';
		(*i)++;
	}
	return (fd);
}

static t_token	*handle_fd_redirect(char *str, int *i)
{
	t_token	*tok;
	int		fd;

	fd = get_fd_number(str, i);
	tok = handle_redirect(str, i);
	if (!tok)
		return (NULL);
	tok->redir_fd = fd;
	return (tok);
}

t_token	*lexer(char *prompt)
{
	int			i;
	t_token		*list;
	t_token		*tok;
	t_segment	*segs;

	i = 0;
	list = NULL;
	while (prompt[i])
	{
		if (is_whitespace(prompt[i]))
		{
			i++;
			continue ;
		}
		if (prompt[i] == '|')
		{
			add_token(&list, new_token(ft_strdup("|"), T_PIPE, Q_NONE));
			i++;
		}
		else if (is_fd_redir(prompt, i))
		{
			tok = handle_fd_redirect(prompt, &i);
			add_token(&list, tok);
		}
		else if (prompt[i] == '<' || prompt[i] == '>')
		{
			tok = handle_redirect(prompt, &i);
			add_token(&list, tok);
		}
		else
		{
			segs = extract_word(prompt, &i);
			if (!segs)
			{
				ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
				free_tokens(list);
				return (NULL);
			}
			tok = new_token(segments_to_value(segs), T_WORD, Q_NONE);
			tok->segments = segs;
			add_token(&list, tok);
		}
	}
	return (list);
}