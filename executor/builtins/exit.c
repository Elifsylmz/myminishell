#include "builtins.h"

int builtin_exit(t_shell *shell, char **argv)
{
    int i = 0;

    if (argv[1])
    {
        while (argv[1][i])
        {
            if (!ft_isdigit(argv[1][i]) && !(i == 0 && (argv[1][i] == '-' || argv[1][i] == '+')))
            {
                fprintf(stderr, "minishell: exit: %s: numeric argument required\n", argv[1]);
                exit(2);
            }
            i++;
        }
    }
    
    int code = argv[1] ? ft_atoi(argv[1]) : shell->last_exit_code;
    printf("exit\n");
    exit(code % 256);
}