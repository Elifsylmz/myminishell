/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:03:22 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 22:03:22 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"

int		is_redir(t_token_type type);
int		add_word(t_ast *cmd, t_token **tokens, int *i);
t_ast	*add_redir(t_ast *root, t_token **tokens);
t_ast	*init_cmd_node(t_token *tokens);

#endif