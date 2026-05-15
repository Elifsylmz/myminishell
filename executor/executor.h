#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../env/env.h"
# include "../libft/libft.h"
# include "../minishell.h"
# include "../parser/ast.h"
# include "../types.h"
# include "builtins/builtins.h"
# include "expander/expander.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>

char	**find_path(char **envp);
char	*find_cmd_path(char **paths, char *cmd);
void	execute(t_shell *shell);
int		apply_redirections(t_ast *node);
int		process_heredocs(t_shell *shell, t_ast *node, int *counter);
void	run_heredoc_child(t_shell *shell, t_ast *node, char *filename);
t_ast	*get_cmd(t_ast *node);
void	exec_cmd(t_ast *node, t_shell *shell);
void	child_cleanup(t_shell *shell);

void	free_array(char **arr);
void	print_cmd_error(char *cmd, char *msg);
void	command_not_found(char *cmd, t_shell *shell);
int		execve_exit_code(int err);
int		check_cmd_before_exec(t_ast *cmd);

#endif