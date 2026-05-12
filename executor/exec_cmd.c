#include "executor.h"

t_ast    *get_cmd(t_ast *node)
{
    while (node && node->type == NODE_REDIR)
        node = node->left;
    return (node);
}

void exec_cmd(t_ast *node, t_shell *shell)
{
    char    **paths;
    char    *cmd_path;
    char    **envp;
    t_ast   *cmd;

    if (apply_redirections(node) != 0)
        exit(1);
    cmd = get_cmd(node);
    if (!cmd || !cmd->argv[0])
        exit(0);
    expand_ast(shell, cmd);
    envp = env_to_array(shell->env);
    paths = find_path(envp);
    cmd_path = find_cmd_path(paths, cmd->argv[0]);
    if (!cmd_path)
    {
        ft_putstr_fd("minishell: command not found\n", 2);
        exit(127);
    }
    execve(cmd_path, cmd->argv, envp);
    perror("execve");
    exit(1);
}