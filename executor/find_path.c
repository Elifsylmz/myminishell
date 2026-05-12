#include "executor.h"

char    **find_path(char **envp)
{
    int     i;

    i = 0;
    while (envp && envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (ft_split(envp[i] + 5, ':'));
        i++;
    }
    return (NULL);
}

char    *find_cmd_path(char **paths, char *cmd)
{
    int     i;
    char    *tmp;
    char    *full_path;

    if (!cmd) return (NULL);
    if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
        return (ft_strdup(cmd));
    if (!paths) return (NULL);
    i = -1;
    while (paths[++i])
    {
        tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
    }
    return (NULL);
}