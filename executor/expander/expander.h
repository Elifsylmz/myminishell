#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../minishell.h"
# include <stdlib.h>
# include <unistd.h>

void	expand_ast(t_shell *shell, t_ast *cmd);
void	expand_redirections(t_shell *shell, t_ast *node);
char	*expand_str(t_shell *shell, char *str);
char	*expand_segments(t_shell *shell, t_segment *segs);

#endif