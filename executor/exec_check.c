#include "executor.h"
#include <sys/stat.h>

static int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

static int	check_direct_path(char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		print_cmd_error(cmd, "No such file or directory");
		return (127);
	}
	if (is_directory(cmd))
	{
		print_cmd_error(cmd, "Is a directory");
		return (126);
	}
	if (access(cmd, X_OK) != 0)
	{
		print_cmd_error(cmd, "Permission denied");
		return (126);
	}
	return (0);
}

int	check_cmd_before_exec(t_ast *cmd)
{
	if (ft_strchr(cmd->argv[0], '/'))
		return (check_direct_path(cmd->argv[0]));
	return (0);
}