


#include "minishell.h"

char  *fex_export(char  *string)
{
  if(string == NULL)
    return(NULL);

}

    // while (cmd->array[i])
    // {
    //     char *arg = cmd->array[i];
    //     char *eq = ft_strchr(arg, '=');
    //     if (eq)
    //     {
    //         *eq = '\0';
    //         update_env_list(shell, arg, eq + 1); // khdmt key + value
    //         *eq = '=';
    //     }
    //     else
    //         update_env_list(shell, arg, NULL);
    //     i++;
    // }