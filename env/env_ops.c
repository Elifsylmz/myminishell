#include "env.h"

static int	key_equals(char *a, char *b)
{
	if (!a || !b)
		return (0);
	if (ft_strlen(a) != ft_strlen(b))
		return (0);
	if (ft_strncmp(a, b, ft_strlen(a)) == 0)
		return (1);
	return (0);
}

char	*env_get(t_env *env, char *key)
{
	while (env)
	{
		if (key_equals(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	env_set(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (key_equals(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			tmp->has_value = 1;
			return ;
		}
		tmp = tmp->next;
	}
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->has_value = 1;
	node->next = NULL;
	if (!*env)
		*env = node;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	env_export_key(t_env **env, char *key)
{
	t_env	*node;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (key_equals(tmp->key, key))
			return ;
		tmp = tmp->next;
	}
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->key = ft_strdup(key);
	node->value = NULL;
	node->has_value = 0;
	node->next = NULL;
	if (!*env)
		*env = node;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	env_unset(t_env **env, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (key_equals(cur->key, key))
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}