#ifndef TYPES_H
# define TYPES_H

/*
** Forward declarations — tam tanım için ilgili modül headerını include et:
**   t_token  → lexer/lexer.h
**   t_env    → env/env.h
**   t_ast    → parser/ast.h
**
** t_shell burada tam tanımlanır çünkü executor, builtins ve expander
** minishell.h'a circular olarak bağlanmadan t_shell'e ihtiyaç duyar.
** Tek çözüm: t_shell'i herkesten önce, bağımsız bir dosyada tutmak.
*/

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