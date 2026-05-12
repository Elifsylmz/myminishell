#include "minishell.h"
#include "parser/ast.h"
#include "executor/executor.h"
#include <readline/history.h>
#include <readline/readline.h>

const char	*get_token_type(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	else if (type == T_PIPE)
		return ("PIPE");
	else if (type == T_REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (type == T_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (type == T_APPEND)
		return ("APPEND");
	else if (type == T_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

const char	*get_quote_type(t_quote_type quote)
{
	if (quote == Q_SINGLE)
		return ("Q_SINGLE");
	else if (quote == Q_DOUBLE)
		return ("Q_DOUBLE");
	return ("Q_NONE");
}

void	print_tokens(t_token *list)
{
	while (list)
	{
		if (list->type == T_WORD)
		{
			if (list->quote != Q_NONE)
				printf("[WORD: %s, %s]\n", list->value,
					get_quote_type(list->quote));
			else
				printf("[WORD: %s]\n", list->value);
		}
		else
			printf("[%s]\n", get_token_type(list->type));
		list = list->next;
	}
}

void	print_ast(t_ast *node, int depth)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < depth)
	{
		printf(" ");
		i++;
	}
	if (node->type == NODE_CMD)
	{
		printf("CMD: ");
		i = 0;
		while (node->argv && node->argv[i])
		{
			printf("%s ", node->argv[i]);
			i++;
		}
		printf("\n");
	}
	else if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_REDIR)
		printf("REDIR (%d) -> %s\n", node->redir_type, node->file);
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

static int	is_blank_input(char *input)
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

static void	init_shell(t_shell *shell, char **envp)
{
	shell->lex = NULL;
	shell->ast = NULL;
	shell->last_exit_code = 0;
	shell->env = env_init(envp);
}

static void	clean_iteration(t_shell *shell, char *input)
{
	free_ast(shell->ast);
	free_tokens(shell->lex);
	shell->ast = NULL;
	shell->lex = NULL;
	free(input);
}

static void	process_input(t_shell *shell, char *input)
{
	t_token	*tmp;

	if (is_blank_input(input))
	{
		free(input);
		return ;
	}
	add_history(input);
	shell->lex = lexer(input);
	if (!shell->lex)
	{
		shell->last_exit_code = 2;
		clean_iteration(shell, input);
		return ;
	}
	tmp = shell->lex;
	shell->ast = parse_pipeline(&tmp);
	if (!shell->ast)
	{
		shell->last_exit_code = 2;
		clean_iteration(shell, input);
		return ;
	}
	start_execution_signals();
	execute(shell);
	start_interactive_signals();
	clean_iteration(shell, input);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	init_shell(shell, envp);
	start_interactive_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		process_input(shell, input);
	}
	env_free(&shell->env);
	free(shell);
	return (0);
}