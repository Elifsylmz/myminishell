#include "builtins.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	exit_code(char *str)
{
	int	i;
	int	sign;
	int	code;

	i = 0;
	sign = 1;
	code = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		code = (code * 10 + str[i] - '0') % 256;
		i++;
	}
	if (sign == -1)
		code = (256 - code) % 256;
	return (code);
}

int	builtin_exit(t_shell *shell, char **argv)
{
	ft_putstr_fd("exit\n", 1);
	if (!argv[1])
		exit(shell->last_exit_code);
	if (!is_numeric(argv[1]))
		exit(2);
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit(exit_code(argv[1]));
}