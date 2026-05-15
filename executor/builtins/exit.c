#include "builtins.h"

static void	clean_exit(t_shell *shell, int code)
{
	free_tokens(shell->lex);
	free_ast(shell->ast);
	env_free(&shell->env);
	free(shell);
	exit(code);
}

int	builtin_exit(t_shell *shell, char **argv)
{
	ft_putstr_fd("exit\n", 1);
	if (!argv[1])
		clean_exit(shell, shell->last_exit_code);
	if (!is_numeric_ll(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_exit(shell, 2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	clean_exit(shell, exit_code(argv[1]));
	return (0);
}