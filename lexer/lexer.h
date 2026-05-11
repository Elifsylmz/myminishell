#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC
}					t_token_type;

typedef enum e_quote_type
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}					t_quote_type;

typedef struct s_segment
{
	char				*value;
	t_quote_type		quote;
	struct s_segment	*next;
}					t_segment;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote;
	t_segment		*segments;
	struct s_token	*next;
}					t_token;

t_token		*lexer(char *prompt);

t_segment	*new_segment(char *value, t_quote_type quote);
void		add_segment(t_segment **list, t_segment *seg);
void		free_segments(t_segment *list);

//t_token		*new_token(char *value, t_token_type type, t_quote_type quote);
//void		add_token(t_token **list, t_token *newtkn);

t_segment	*extract_word(char *str, int *i);
char		*segments_to_value(t_segment *segs);
int			is_special(char c);
int			is_whitespace(char c);
t_segment	*extract_word(char *str, int *i);


//void		free_tokens(t_token *list);

#endif