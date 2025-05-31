/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/05/31 15:17:46 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int builtin_export(c_cmd *cmd, t_shell *shell)
// {
//     // int i;
//     // char *equal_sign;
//     // char *name;
//     // char *value;
//     (void)cmd;
//     char **test;

//     // shell->env_copy = dup_envp(shell->env);
    
//     // if (!cmd->array || !cmd->array[1])
//     // {
//     //     // need to sort (bubble sort ); from a z 
//     //     print_env(shell->env_copy);
//     // }
//     test = function_split_env(shell);
//     if(test == NULL)
//         printf("ra salina \n");
//     // i = 1;
//     // while (cmd->array[i] != NULL)
//     // {
//     //     //check wach kayna =
//     //     equal_sign = ft_strchr(cmd->array[i], '=');
//     //     // if(equal_sign == NULL)
//     //     //     printf("spaaam9999 equal_sign == NULL\n");
//     //     // if(equal_sign == NULL)
//     //     //     return(0);
//     //      if (equal_sign != NULL)
//     //     {
//     //         //ah kayna so : andir split VAR=ARG {VAR}, {ARG}, {NULL}
//     //         *equal_sign = '\0';
//     //         name = cmd->array[i];
//     //         value = equal_sign + 1;
//     //                     *equal_sign = '='; // Restore original string

//     //         update_env_variable(shell, name, value);
//     //         // update_env_variable(shell, name, value);
//     //     }
//     //     else
//     //     {
//     //         // export a="" 
//     //         if (get_env_value(shell->env_copy, cmd->array[i]) == NULL)
//     //             update_env_variable(shell, cmd->array[i], "");
//     //     }
//     //     i++;
//     // }

//     return (0);
// }


int builtin_export(c_cmd *cmd, t_shell *shell)
{
    char *arg;
    char *equal_sign;
    int i = 1;
    if (!cmd->array[1])
    {
        // If no args: print sorted env list
        print_env(shell->env);
        return 0;
    }
    while (cmd->array[i])
    {
        arg = cmd->array[i];
        equal_sign = ft_strchr(arg, '=');
        if (equal_sign)
        {
            // VAR=VALUE case
            *equal_sign = '\0';
            shell->envv->key = arg;
            shell->envv->value = equal_sign + 1;
            update_env_variable(shell, shell->envv->key, shell->envv->value);
            *equal_sign = '='; // restore
        }
        else
        {
            // VAR only ➜ add with empty string if not exist
            if (!get_env_value(shell->env, arg))
                update_env_variable(shell, arg, "");
        }
        i++;
    }
    return 0;
}
// void update_env_variable(t_shell *shell, char *key, char *value)
// {
//     t_env *tmp = shell->env_list;
//     while (tmp)
//     {
//         if (ft_strcmp(tmp->key, key) == 0)
//         {
//             // key kayna ➜ update
//             free(tmp->value);
//             tmp->value = strdup(value);
//             return;
//         }
//         tmp = tmp->next;
//     }
//     // key ma kaynach ➜ add
//     t_env *new_node = create_env_node(key, value);
//     add_env_node(&(shell->env_list), new_node);
// }
