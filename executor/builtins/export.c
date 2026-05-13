#include "builtins.h"

static int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static char	*get_key(char *arg)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		return (ft_substr(arg, 0, eq - arg));
	return (ft_strdup(arg));
}

static void	set_export_value(t_shell *shell, char *arg, char *key)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		env_set(&shell->env, key, eq + 1);
	else
		env_set(&shell->env, key, "");
}

int	builtin_export(t_shell *shell, char **argv)
{
	char	*key;
	int		i;
	int		status;

	if (!argv[1])
		return (builtin_env(shell, argv));
	i = 1;
	status = 0;
	while (argv[i])
	{
		key = get_key(argv[i]);
		if (!key)
			return (1);
		if (is_valid_identifier(key))
			set_export_value(shell, argv[i], key);
		else
		{
			export_error(argv[i]);
			status = 1;
		}
		free(key);
		i++;
	}
	return (status);
}