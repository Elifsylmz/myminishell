/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:17 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:18:30 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*expand_var(t_shell *shell, char *str, int *i)
{
	int		start;
	char	*key;
	char	*value;

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->last_exit_code));
	}
	start = *i;
	if (!str[*i] || (!ft_isalnum(str[*i]) && str[*i] != '_'))
		return (ft_strdup("$"));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	if (!key)
		return (NULL);
	value = env_get(shell->env, key);
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static int	append_part(char **result, char *part)
{
	char	*tmp;

	if (!part)
		return (0);
	tmp = ft_strjoin(*result, part);
	free(part);
	if (!tmp)
		return (0);
	free(*result);
	*result = tmp;
	return (1);
}

static int	append_literal(char **result, char *str, int *i)
{
	int		start;
	char	*part;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	if (*i == start)
		return (1);
	part = ft_substr(str, start, *i - start);
	return (append_part(result, part));
}

static int	append_expansion(t_shell *shell, char **result, char *str, int *i)
{
	char	*part;

	if (str[*i] != '$')
		return (1);
	(*i)++;
	if (!str[*i])
		part = ft_strdup("$");
	else
		part = expand_var(shell, str, i);
	return (append_part(result, part));
}

char	*expand_str(t_shell *shell, char *str)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (!append_literal(&result, str, &i))
			return (free(result), NULL);
		if (!append_expansion(shell, &result, str, &i))
			return (free(result), NULL);
	}
	return (result);
}
