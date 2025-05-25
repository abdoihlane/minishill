/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:18:47 by salhali           #+#    #+#             */
/*   Updated: 2025/05/25 12:18:49 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_exit(c_cmd *cmd)
{
    int exit_code;

    exit_code = 0;

    // If argument provided, use it as exit code
    if (cmd->array && cmd->array[1])
    {
        exit_code = ft_atoi(cmd->array[1]);
        // Check if it's a valid number (basic check)
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

