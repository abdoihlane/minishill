/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/05/28 16:13:43 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_export(c_cmd *cmd, t_shell *shell)
{
    // int i;
    // char *equal_sign;
    // char *name;
    // char *value;
    (void)cmd;
    char **test;


    // shell->env_copy = dup_envp(shell->env);
    
    // if (!cmd->array || !cmd->array[1])
    // {
    //     // need to sort (bubble sort ); from a z 
    //     print_env(shell->env_copy);
    // }
    test = function_split_env(shell);
    if(test == NULL)
        printf("ra salina \n");
    // i = 1;
    // while (cmd->array[i] != NULL)
    // {
    //     //check wach kayna =
    //     equal_sign = ft_strchr(cmd->array[i], '=');
    //     // if(equal_sign == NULL)
    //     //     printf("spaaam9999 equal_sign == NULL\n");
    //     // if(equal_sign == NULL)
    //     //     return(0);
    //      if (equal_sign != NULL)
    //     {
    //         //ah kayna so : andir split VAR=ARG {VAR}, {ARG}, {NULL}
    //         *equal_sign = '\0';
    //         name = cmd->array[i];
    //         value = equal_sign + 1;
    //                     *equal_sign = '='; // Restore original string

    //         update_env_variable(shell, name, value);
    //         // update_env_variable(shell, name, value);
    //     }
    //     else
    //     {
    //         // export a="" 
    //         if (get_env_value(shell->env_copy, cmd->array[i]) == NULL)
    //             update_env_variable(shell, cmd->array[i], "");
    //     }
    //     i++;
    // }

    return (0);
}
