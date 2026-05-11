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
		{
			printf("[%s]\n", get_token_type(list->type));
		}
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
			printf("%s", node->argv[i]);
			i++;
		}
		printf ("\n");
	}
	else if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_REDIR)
		printf("REDIR (%d) -> %s\n", node->redir_type, node->file);
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

static void	init_shell(t_shell *shell, char **envp)
{
	shell->lex = NULL;
	shell->ast = NULL;
	shell->last_exit_code = 0;
	shell->env = env_init(envp);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	*shell;
	t_token	*token_head;
	t_token	*tmp;

	(void)ac;
	(void)av;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	init_shell(shell, envp);
	start_interactive_signals();
	while (1)
	{
		shell->lex = NULL;
		shell->ast = NULL;
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		token_head = lexer(input);
		shell->lex = token_head;
		if (token_head)
		{
			tmp = token_head;
			shell->ast = parse_pipeline(&tmp);
		}
		start_execution_signals();
		execute(shell);
		start_interactive_signals();
		free_ast(shell->ast);
		free_tokens(shell->lex);
		shell->ast = NULL;
		shell->lex = NULL;
		free(input);
	}
	free(shell);
	return (0);
}