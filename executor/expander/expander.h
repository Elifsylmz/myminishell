/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyilmaz <eyilmaz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:53:21 by eyilmaz           #+#    #+#             */
/*   Updated: 2026/05/15 21:53:21 by eyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../minishell.h"
# include <stdlib.h>
# include <unistd.h>

void	expand_ast(t_shell *shell, t_ast *cmd);
void	expand_redirections(t_shell *shell, t_ast *node);
char	*expand_str(t_shell *shell, char *str);
char	*expand_segments(t_shell *shell, t_segment *segs);

#endif