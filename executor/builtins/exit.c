#include "builtins.h"

static void	clean_exit(t_shell *shell, int code)
{
	free_tokens(shell->lex);
	free_ast(shell->ast);
	env_free(&shell->env);
	free(shell);
	exit(code);
}

static int	get_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	*i = 0;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	is_overflow(char *str, int i, int sign)
{
	char	*limit;
	int		len;

	while (str[i] == '0')
		i++;
	len = ft_strlen(str + i);
	if (len < 19)
		return (0);
	if (len > 19)
		return (1);
	if (sign == -1)
		limit = "9223372036854775808";
	else
		limit = "9223372036854775807";
	if (ft_strncmp(str + i, limit, 19) > 0)
		return (1);
	return (0);
}

static int	is_numeric_ll(char *str)
{
	int	i;
	int	sign;

	if (!str || !str[0])
		return (0);
	sign = get_sign(str, &i);
	if (!str[i])
		return (0);
	if (is_overflow(str, i, sign))
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

	sign = get_sign(str, &i);
	code = 0;
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