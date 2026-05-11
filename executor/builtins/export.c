#include "builtins.h"

int	builtin_export(t_shell *shell, char **argv)
{
	char	*eq;
	char	*key;
	char	*value;
	int		i;

	if (!argv[1])
	{
		builtin_env(shell, argv);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
		{
			key = ft_substr(argv[i], 0, eq - argv[i]);
			value = ft_strdup(eq + 1);
			env_set(&shell->env, key, value);
			free(key);
			free(value);
		}
		else
			env_set(&shell->env, argv[i], "");
		i++;
	}
	return (0);
}