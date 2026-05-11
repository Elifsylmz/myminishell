#include "env.h"

t_env   *env_init(char **envp)
{
    t_env   *list;
    char    *eq;
    char    *key;
    char    *val;
    int     i;
 
    list = NULL;
    i = 0;
    while (envp && envp[i])
    {
        eq = ft_strchr(envp[i], '=');
        if (eq)
        {
            key = ft_substr(envp[i], 0, eq - envp[i]);
            val = ft_strdup(eq + 1);
            env_set(&list, key, val);
            free(key);
            free(val);
        }
        i++;
    }
    return (list);
}