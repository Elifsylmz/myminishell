#include "builtins.h"

static int	is_valid_identifier(char *s)
{
	int	i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[++i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
	}
	return (1);
}

static void	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	builtin_export(t_shell *shell, char **argv)
{
	char	*eq;
	char	*key;
	int		i;

	if (!argv[1])
		return (builtin_env(shell, argv));
	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
			key = ft_substr(argv[i], 0, eq - argv[i]);
		else
			key = ft_strdup(argv[i]);
		if (is_valid_identifier(key))
			env_set(&shell->env, key, eq ? (eq + 1) : "");
		else
		{
			export_error(argv[i]);
			shell->last_exit_code = 1;
		}
		free(key);
		i++;
	}
	return (shell->last_exit_code);
}