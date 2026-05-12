#include "builtins.h"

int	builtin_unset(t_shell *shell, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		env_unset(&shell->env, argv[i]);
		i++;
	}
	return (0);
}
