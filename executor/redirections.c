#include "executor.h"

int  apply_redirections(t_ast *node)
{
    int     fd;
    pid_t   pid;
    int     status;
    char    *line;

    if (!node || node->type != NODE_REDIR)
        return (0);
    if (apply_redirections(node->left) != 0)
        return (1);
    if (node->redir_type == T_REDIRECT_IN || node->redir_type == T_HEREDOC)
    {
        if (node->redir_type == T_HEREDOC)
        {
            pid = fork();
            if (pid == 0)
            {
                set_heredoc_signals();
                fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                while (1)
                {
                    line = readline("> ");
                    if (!line || ft_strncmp(line, node->file, ft_strlen(node->file) + 1) == 0)
                    {
                        free(line);
                        break ;
                    }
                    write(fd, line, ft_strlen(line));
                    write(fd, "\n", 1);
                    free(line);
                }
                close(fd);
                exit(0);
            }
            waitpid(pid, &status, 0);
            fd = open(".heredoc_tmp", O_RDONLY);
        }
        else
            fd = open(node->file, O_RDONLY);
        
        if (fd < 0) return (perror(node->file), 1);
        dup2(fd, STDIN_FILENO);
        close(fd);
        if (node->redir_type == T_HEREDOC) unlink(".heredoc_tmp");
    }
    else
    {
        if (node->redir_type == T_REDIRECT_OUT)
            fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0) return (perror(node->file), 1);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    return (0);
}