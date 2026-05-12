#include "executor.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

static void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_ast	*get_cmd(t_ast *node)
{
	while (node && node->type == NODE_REDIR)
		node = node->left;
	return (node);
}

static void	print_cmd_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

static int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

static void	check_direct_path(char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		print_cmd_error(cmd, "No such file or directory");
		exit(127);
	}
	if (is_directory(cmd))
	{
		print_cmd_error(cmd, "Is a directory");
		exit(126);
	}
	if (access(cmd, X_OK) != 0)
	{
		print_cmd_error(cmd, "Permission denied");
		exit(126);
	}
}

static void	command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

static int	execve_exit_code(int err)
{
	if (err == EACCES)
		return (126);
	if (err == ENOENT)
		return (127);
	return (126);
}

void	exec_cmd(t_ast *node, t_shell *shell)
{
	char	**paths;
	char	*cmd_path;
	char	**envp;
	t_ast	*cmd;
	int		err;

	if (apply_redirections(node) != 0)
		exit(1);
	cmd = get_cmd(node);
	if (!cmd || !cmd->argv[0])
		exit(0);
	if (ft_strchr(cmd->argv[0], '/'))
		check_direct_path(cmd->argv[0]);
	envp = env_to_array(shell->env);
	paths = find_path(envp);
	cmd_path = find_cmd_path(paths, cmd->argv[0]);
	if (!cmd_path)
	{
		free_array(paths);
		free_array(envp);
		command_not_found(cmd->argv[0]);
	}
	execve(cmd_path, cmd->argv, envp);
	err = errno;
	print_cmd_error(cmd->argv[0], strerror(err));
	free(cmd_path);
	free_array(paths);
	free_array(envp);
	exit(execve_exit_code(err));
}