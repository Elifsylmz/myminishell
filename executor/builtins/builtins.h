#ifndef BUILTINS_H
# define BUILTINS_H

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

# include "../../types.h"
# include "../../minishell.h"
# include <stdio.h>
# include <limits.h>


int		is_builtin(char *cmd);
int		run_builtin(t_shell *shell, char **argv);

int		builtin_cd(t_shell *shell, char **argv);
int		builtin_echo(t_shell *shell, char **argv);
int		builtin_env(t_shell *shell, char **argv);
int		builtin_export(t_shell *shell, char **argv);
int		builtin_unset(t_shell *shell, char **argv);
int		builtin_exit(t_shell *shell, char **argv);
int		builtin_pwd(t_shell *shell, char **argv);
int		print_export(t_env *env);

char	*get_cd_path(t_shell *shell, char **argv, int *need_free);
void	print_cd_path_error(char **argv);
void	update_pwd_values(t_shell *shell, char *oldpwd);
int		is_numeric_ll(char *str);
int		exit_code(char *str);

#endif