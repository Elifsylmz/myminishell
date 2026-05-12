#include "builtins.h"

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*path;
	char	*oldpwd;
	char	cwd[1024];

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	oldpwd = env_get(shell->env, "PWD");
	if (!argv[1])
		path = env_get(shell->env, "HOME");
	else if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		path = env_get(shell->env, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
		printf("%s\n", path);
	}
	else
		path = argv[1];
	if (!path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	if (oldpwd)
		env_set(&shell->env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(&shell->env, "PWD", cwd);
	return (0);
}