#ifndef AST_H
# define AST_H

# include "../lexer/lexer.h"
# include "../libft/libft.h"
# include <stdlib.h>
#include <unistd.h>

typedef enum e_node_type
{
    NODE_CMD,
    NODE_PIPE,
    NODE_REDIR
}                   t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	char			**argv;
	t_segment		**arg_segments;
	t_token_type	redir_type;
	int				redir_fd;
	char			*file;
	t_segment		*file_segments;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

t_ast   *parse_pipeline(t_token **tokens);
void    free_ast(t_ast *node);
t_ast   *new_node(t_node_type type);
t_segment   *dup_segments(t_segment *src);

#endif