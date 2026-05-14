#include "builtins.h"

static int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || !s[0])
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

int	builtin_unset(t_shell *shell, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
			env_unset(&shell->env, argv[i]);
		i++;
	}
	return (0);
}