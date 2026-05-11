#include "builtins.h"

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*path;
	char	*oldpwd;
	char	cwd[1024];

	oldpwd = env_get(shell->env, "PWD");
	if (!argv[1])
		path = env_get(shell->env, "HOME");
	else if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		path = env_get(shell->env, "OLDPWD");
		if (!path)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return (1);
		}
		printf("%s\n", path);
	}
	else
		path = argv[1];
	if (!path)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (oldpwd)
		env_set(&shell->env, "OLDPWD", oldpwd);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		env_set(&shell->env, "PWD", cwd);
	return (0);
}