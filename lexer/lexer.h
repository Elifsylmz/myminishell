/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:05:07 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:05:18 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef enum e_quote_type
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote_type;

typedef struct s_segment
{
	char				*value;
	t_quote_type		quote;
	struct s_segment	*next;
}	t_segment;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote;
	t_segment		*segments;
	int				redir_fd;
	struct s_token	*next;
}	t_token;

t_token		*lexer(char *prompt);
int			handle_token(char *prompt, int *i, t_token **list);

t_token		*handle_redirect(char *str, int *i);
t_token		*handle_fd_redirect(char *str, int *i);
int			is_fd_redir(char *str, int i);

t_segment	*new_segment(char *value, t_quote_type quote);
void		add_segment(t_segment **list, t_segment *seg);
void		free_segments(t_segment *list);
char		*segments_to_value(t_segment *segs);
t_segment	*extract_word(char *str, int *i);

t_token		*new_token(char *value, t_token_type type, t_quote_type quote);
void		add_token(t_token **list, t_token *newtkn);
void		free_tokens(t_token *list);

#endif