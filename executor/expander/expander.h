#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../types.h"
# include "../../minishell.h"
# include "../../lexer/lexer.h"
# include "../../parser/ast.h"
# include <stdlib.h>
# include <unistd.h>

void	expand_ast(t_shell *shell, t_ast *cmd);

#endif