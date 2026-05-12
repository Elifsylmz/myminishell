#include "builtins.h"

static int	is_valid_identifier(char *s)
{
	int	i;

	if (!s)
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	builtin_unset(t_shell *shell, char **argv)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
			env_unset(&shell->env, argv[i]);
		else
		{
			unset_error(argv[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}