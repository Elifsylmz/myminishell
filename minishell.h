#ifndef MINISHELL_H
# define MINISHELL_H


# include "lexer/lexer.h"
# include "libft/libft.h"
# include "env/env.h"
# include "parser/ast.h"

extern int	g_signal;

typedef struct s_shell
{
	t_token	*lex;
	t_env	*env;
	t_ast	*ast;
	int		last_exit_code;
}	t_shell;

void	start_interactive_signals(void);
void	start_execution_signals(void);
void	set_child_signals(void);
void	set_heredoc_signals(void);

#endif
