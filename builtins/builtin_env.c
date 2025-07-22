/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:18:24 by salhali           #+#    #+#             */
/*   Updated: 2025/07/22 22:18:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_cmd_array(c_cmd *cmd)
{
    int i = 0;
    if (cmd == NULL || cmd->array == NULL)
    {
        printf("Command array is NULL\n");
        return;
    }
    while (cmd->array[i])
    {
        printf("cmd->array[%d] = %s\n", i, cmd->array[i]);
        i++;
    }
}

int builtin_env(c_cmd *cmd, t_shell *shell)
{
    t_env *tmp = shell->envv;
    print_cmd_array(cmd);
    printf("%d\n", cmd->qflag);
    // (void)cmd; // cmd is not used in this function, but we keep it for consistency
    if(cmd->array[1] && cmd->array[1][0] != '\0' && cmd->qflag == 1)
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd("too many arguments\n", 2);
        return(1);
    }
    
    while (tmp)
    {
        if (tmp->value)
        {
            printf("%s=%s\n", tmp->key, tmp->value);
        }
        tmp = tmp->next;
    }
    return 0;
}
