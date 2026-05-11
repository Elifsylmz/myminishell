#include "env.h"

static void	fill_env_array(char **arr, t_env *env)
{
	char	*tmp_str;
	int		i;

	i = 0;
	while (env)
	{
		tmp_str = ft_strjoin(env->key, "=");
		arr[i] = ft_strjoin(tmp_str, env->value);
		free(tmp_str);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
}

char	**env_to_array(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	fill_env_array(arr, env);
	return (arr);
}

void	env_free(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}