#include "executor/executor.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	update_signal_status(t_shell *shell)
{
	if (g_signal != 0)
	{
		shell->last_exit_code = 128 + g_signal;
		g_signal = 0;
	}
}

static int	handle_heredocs(t_shell *shell, char *input)
{
	int	heredoc_counter;

	heredoc_counter = 0;
	if (process_heredocs(shell, shell->ast, &heredoc_counter) != 0)
	{
		shell->last_exit_code = 130;
		start_interactive_signals();
		clean_iteration(shell, input);
		return (1);
	}
	return (0);
}

static void	run_command_line(t_shell *shell, char *input)
{
	add_history(input);
	if (build_ast(shell, input) != 0)
	{
		clean_iteration(shell, input);
		return ;
	}
	if (handle_heredocs(shell, input) != 0)
		return ;
	start_execution_signals();
	execute(shell);
	start_interactive_signals();
	clean_iteration(shell, input);
}

static int	read_input(t_shell *shell)
{
	char	*input;

	input = readline("minishell$ ");
	update_signal_status(shell);
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		return (0);
	}
	if (is_blank_input(input))
	{
		free(input);
		return (1);
	}
	run_command_line(shell, input);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	init_shell(shell, envp);
	start_interactive_signals();
	while (read_input(shell))
		;
	env_free(&shell->env);
	free(shell);
	return (0);
}