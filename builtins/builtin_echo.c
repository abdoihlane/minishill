/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:21:22 by salhali           #+#    #+#             */
/*   Updated: 2025/05/25 18:36:07 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_echo(c_cmd *cmd)
{
    int i;
    int n_option;

    i = 1;
    n_option = 0;
    // printf("array fih : %s\n", cmd->array[0]);
    if (cmd->array && cmd->array[i] && ft_strcmp(cmd->array[i], "-n") == 0)
    {
        n_option = 1;
        i++;
    }
    while (cmd->array[i])
    {
        ft_putstr_fd(cmd->array[i], 1);
        if (cmd->array[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    // Print newline if -n option not present
    if (!n_option)
        ft_putchar_fd('\n', 1);
    
    return (0);
}
