#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../minishell.h"
# include <stdlib.h>
# include <unistd.h>

void    expand_ast(t_shell *shell, t_ast *cmd);
char    *expand_str(t_shell *shell, char *str); // Dışarıya açıldı

#endif