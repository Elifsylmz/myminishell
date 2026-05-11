#include "builtins.h"

int	builtin_env(t_shell *shell, char **argv)
{
	t_env *env;

	(void)argv;
	env = shell->env;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}