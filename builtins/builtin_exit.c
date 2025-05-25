/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:18:47 by salhali           #+#    #+#             */
/*   Updated: 2025/05/25 21:32:53 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_exit(c_cmd *cmd)
{
    int exit_code;

    exit_code = 0;

    if (cmd->array && cmd->array[1])
    {
        exit_code = ft_atoi(cmd->array[1]);
        if (!ft_isdigit(cmd->array[1][0]) && cmd->array[1][0] != '-' && cmd->array[1][0] != '+')
        {
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(cmd->array[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            exit_code = 2;
        }
    }

    ft_putstr_fd("exit\n", 1);
    exit(exit_code);
    return (0); // Never reached
}

