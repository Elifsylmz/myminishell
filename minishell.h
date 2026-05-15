#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "types.h"

# include "lexer/lexer.h"
# include "libft/libft.h"
# include "env/env.h"
# include "parser/ast.h"
# include <signal.h>

extern volatile sig_atomic_t	g_signal;

void	start_interactive_signals(void);
void	start_execution_signals(void);
void	set_child_signals(void);
void	set_heredoc_signals(void);

int		is_blank_input(char *input);
void	init_shell(t_shell *shell, char **envp);
void	clean_iteration(t_shell *shell, char *input);
int		build_ast(t_shell *shell, char *input);

#endif
