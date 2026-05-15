/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:04 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:19:30 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	get_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	*i = 0;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	is_overflow(char *str, int i, int sign)
{
	char	*limit;
	int		len;

	while (str[i] == '0')
		i++;
	len = ft_strlen(str + i);
	if (len < 19)
		return (0);
	if (len > 19)
		return (1);
	if (sign == -1)
		limit = "9223372036854775808";
	else
		limit = "9223372036854775807";
	if (ft_strncmp(str + i, limit, 19) > 0)
		return (1);
	return (0);
}

int	is_numeric_ll(char *str)
{
	int	i;
	int	sign;

	if (!str || !str[0])
		return (0);
	sign = get_sign(str, &i);
	if (!str[i])
		return (0);
	if (is_overflow(str, i, sign))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_code(char *str)
{
	int	i;
	int	sign;
	int	code;

	sign = get_sign(str, &i);
	code = 0;
	while (str[i])
	{
		code = (code * 10 + str[i] - '0') % 256;
		i++;
	}
	if (sign == -1)
		code = (256 - code) % 256;
	return (code);
}
