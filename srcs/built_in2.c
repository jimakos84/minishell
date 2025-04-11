#include "../includes/shell.h"

void    remove_env_node(t_env *env, char *key)
{
    char    *env_key;
    t_env   *temp;

    if (!env || !key)
        return ;
    env_key = env->name;
    if (ft_strncmp(env_key, key, ft_strlen(key)) == 0)
        

}
void    builtin_unset(t_shell *mini, char *unset)
{
    t_initenv   env;

    env = *mini->initenv;

    printf("%s\n", extract_env_value(&env, "TERM"));
    if (!unset)
        return ;
    if (!mini->initenv->env || !extract_env_value(mini->initenv, unset))
        return ;
    else

}