#ifndef ENV_H
# define ENV_H

# include "../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				has_value;
	struct s_env	*next;
}					t_env;

t_env	*env_init(char **envp);
char	*env_get(t_env *env, char *key);
void	env_set(t_env **env, char *key, char *value);
void	env_export_key(t_env **env, char *key);
void	env_unset(t_env **env, char *key);
char	**env_to_array(t_env *env);
void	env_free(t_env **env);

t_env	*env_new_node(char *key, char *value, int has_value);
void	env_append_node(t_env **env, t_env *node);

#endif