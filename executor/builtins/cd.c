#include "builtins.h"

static char	*join_home_path(char *home, char *arg)
{
	char	*path;

	if (!home)
		return (NULL);
	if (arg[1] == '\0')
		return (ft_strdup(home));
	path = ft_strjoin(home, arg + 1);
	return (path);
}

static char	*get_cd_path(t_shell *shell, char **argv, int *need_free)
{
	char	*path;

	*need_free = 0;
	if (!argv[1])
		return (env_get(shell->env, "HOME"));
	if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		path = env_get(shell->env, "OLDPWD");
		if (path)
			printf("%s\n", path);
		return (path);
	}
	if (argv[1][0] == '~' && (argv[1][1] == '\0' || argv[1][1] == '/'))
	{
		*need_free = 1;
		return (join_home_path(env_get(shell->env, "HOME"), argv[1]));
	}
	return (argv[1]);
}

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*path;
	char	*oldpwd;
	char	cwd[1024];
	int		need_free;

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	oldpwd = env_get(shell->env, "PWD");
	path = get_cd_path(shell, argv, &need_free);
	if (!path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		if (need_free)
			free(path);
		return (1);
	}
	if (need_free)
		free(path);
	if (oldpwd)
		env_set(&shell->env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(&shell->env, "PWD", cwd);
	return (0);
}