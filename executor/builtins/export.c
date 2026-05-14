#include "builtins.h"

static int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
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

static char	*get_export_key(char *arg, char *eq)
{
	if (eq)
		return (ft_substr(arg, 0, eq - arg));
	return (ft_strdup(arg));
}

static int	export_arg(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	key = get_export_key(arg, eq);
	if (!key)
		return (1);
	if (!is_valid_identifier(key))
	{
		export_error(arg);
		free(key);
		return (1);
	}
	if (eq)
		env_set(&shell->env, key, eq + 1);
	else
		env_export_key(&shell->env, key);
	free(key);
	return (0);
}

int	builtin_export(t_shell *shell, char **argv)
{
	int	i;
	int	status;

	if (!argv[1])
		return (print_export(shell->env));
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (export_arg(shell, argv[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}