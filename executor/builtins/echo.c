#include "builtins.h"

int	builtin_echo(t_shell *shell, char **argv)
{
	int i;
	int newline;

	(void)shell;
	newline = 1;
	i = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}