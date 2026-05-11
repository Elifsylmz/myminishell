#include "builtins.h"

int	builtin_exit(t_shell *shell, char **argv)
{
	int code;

	printf("exit\n");
	if (argv[1])
		code = ft_atoi(argv[1]);
	else
		code = shell->last_exit_code;
	exit(code);
}