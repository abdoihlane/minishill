
#include "minishell.h"

void update_env_list(t_shell *shell, const char *key, const char *value)
{
    t_env *tmp = shell->envv;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return;
        }
        tmp = tmp->next;
    }
    // not exist ➜ create
    t_env *new = create_env_node((char *)key, (char *)value);
    if (!shell->envv)
        shell->envv = new;
    else
    {
        tmp = shell->envv;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}
