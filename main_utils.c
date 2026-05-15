/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:54:43 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:02:04 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank_input(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->lex = NULL;
	shell->ast = NULL;
	shell->last_exit_code = 0;
	shell->env = env_init(envp);
}

void	clean_iteration(t_shell *shell, char *input)
{
	free_ast(shell->ast);
	free_tokens(shell->lex);
	shell->ast = NULL;
	shell->lex = NULL;
	free(input);
}

int	build_ast(t_shell *shell, char *input)
{
	t_token	*cursor;

	shell->lex = lexer(input);
	if (!shell->lex)
	{
		shell->last_exit_code = 2;
		return (1);
	}
	cursor = shell->lex;
	shell->ast = parse_pipeline(&cursor);
	if (!shell->ast)
	{
		shell->last_exit_code = 2;
		return (1);
	}
	return (0);
}
