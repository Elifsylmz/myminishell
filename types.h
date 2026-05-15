/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:00:39 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:00:39 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_ast	t_ast;

typedef struct s_shell
{
	t_token	*lex;
	t_env	*env;
	t_ast	*ast;
	int		last_exit_code;
}			t_shell;

#endif