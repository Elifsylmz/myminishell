#include "builtins.h"

int	builtin_env(t_shell *shell, char **argv)
{
	t_env	*env;

	(void)argv;
	env = shell->env;
	while (env)
	{
		if (env->has_value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}