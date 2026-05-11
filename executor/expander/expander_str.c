#include "expander.h"

static char *expand_var(t_shell *shell, char *str, int *i)
{
    int     start;
    char    *key;
    char    *value;

    if (str[*i] == '?')
    {
        (*i)++;
        return (ft_itoa(shell->last_exit_code));
    }
    start = *i;
    if (!str[*i] || (!ft_isalnum(str[*i]) && str[*i] != '_'))
        return (ft_strdup("$"));
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;
    key = ft_substr(str, start, *i - start);
    value = env_get(shell->env, key);
    free(key);
    if (!value)
        return (ft_strdup(""));
    return (ft_strdup(value));
}

char *expand_str(t_shell *shell, char *str)
{
    char    *result;
    char    *tmp;
    char    *part;
    int     i;
    int     start;

    result = ft_strdup("");
    i = 0;
    while (str[i])
    {
        start = i;
        while (str[i] && str[i] != '$')
            i++;
        if (i > start)
        {
            part = ft_substr(str, start, i - start);
            tmp = ft_strjoin(result, part);
            free(result);
            free(part);
            result = tmp;
        }
        if (str[i] == '$')
        {
            i++;
            // Eğer string sonunda bir $ kaldıysa onu ekle
            if (!str[i])
                part = ft_strdup("$");
            else
                part = expand_var(shell, str, &i);
            tmp = ft_strjoin(result, part);
            free(result);
            free(part);
            result = tmp;
        }
    }
    return (result);
}