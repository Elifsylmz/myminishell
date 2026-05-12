#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../types.h"
# include "../libft/libft.h"
# include "../parser/ast.h"
# include "../env/env.h"
# include "../minishell.h"
# include "builtins/builtins.h"
# include "expander/expander.h"
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>

char    **find_path(char **envp);
char    *find_cmd_path(char **paths, char *cmd);
void    execute(t_shell *shell);
int     apply_redirections(t_ast *node);
t_ast   *get_cmd(t_ast *node);
void    exec_cmd(t_ast *node, t_shell *shell);

#endif