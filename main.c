#include "executor/executor.h"
#include "minishell.h"
#include "parser/ast.h"
#include <readline/history.h>
#include <readline/readline.h>

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

static int	build_ast(t_shell *shell, char *input)
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

static void	process_input(t_shell *shell, char *input)
{
	int	heredoc_counter;

	if (is_blank_input(input))
	{
		free(input);
		return ;
	}
	add_history(input);
	if (build_ast(shell, input) != 0)
	{
		clean_iteration(shell, input);
		return ;
	}
	heredoc_counter = 0;
	if (process_heredocs(shell, shell->ast, &heredoc_counter) != 0)
	{
		shell->last_exit_code = 130;
		start_interactive_signals();
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
		if (g_signal != 0)
		{
			shell->last_exit_code = 128 + g_signal;
			g_signal = 0;
		}
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		process_input(shell, input);
	}
	env_free(&shell->env);
	free(shell);
	return (0);
}