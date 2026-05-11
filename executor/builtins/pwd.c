#include "builtins.h"

int	builtin_pwd(t_shell *shell, char **argv)
{
	char    cwd[1024];

	(void)shell;
	(void)argv;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: pwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}