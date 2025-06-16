/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/06/16 09:51:11 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int builtin_export(c_cmd *cmd, t_shell *shell)
// {
//     int i = 1;

//     if (!cmd->array[1])
//     {
//         print_env_sorted(shell->envv); // print sorted
//         return 0;
//     }
//     while (cmd->array[i])
//     {
//         char *equal = ft_strchr(cmd->array[i], '=');
//         if (equal)
//         {
//             *equal = '\0';
//             char *key = cmd->array[i];
//             char *value = equal + 1;
//             update_env_list(shell, key, value);
//             *equal = '=';
//         }
//         else
//         {
//             if (!get_env_value_ll(shell->envv, cmd->array[i]))
//                 update_env_list(shell, cmd->array[i], "");
//         }
//         i++;
//     }
//     return 0;
// }
int builtin_export(c_cmd *cmd, t_shell *shell)
{
    int i = 1;

    if (!cmd->array[1])
    {
        print_env_sorted(shell->envv); // print sorted
        return 0;
    }
    // printf("before run spam\n");
    while (cmd->array[1] != NULL)
    {
        char    *str = cmd->array[1];
        char    *result = ft_strchr(str, '=');
        if(result)
        {
            *result = '\0';
            update_env_list(shell, str, result);
            *result = '=';

        }
    }
    if (cmd->array[1] && cmd->qflag == 1 && cmd->array[1][0] == '\0')
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd("export: ", 2);
        ft_putstr_fd("No such file or directory\n", 2);
        return(1);
    }
    while (cmd->array[i])
    {
        char *arg = cmd->array[i];
        char *eq = ft_strchr(arg, '=');
        if (eq)
        {
            *eq = '\0';
            update_env_list(shell, arg, eq + 1); // khdmt key + value
            *eq = '=';
        }
        else
            update_env_list(shell, arg, NULL);
        i++;
    }
    return 0;
}
