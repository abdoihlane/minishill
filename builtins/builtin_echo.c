/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:21:22 by salhali           #+#    #+#             */
/*   Updated: 2025/06/01 16:44:00 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_echo(c_cmd *cmd)
{
    int i = 1;
    int n_option = 0;

    if (!cmd || !cmd->array)
        return (0);

    while (cmd->array[i] && ft_strcmp_echo(cmd->array[i]) == 0)
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

    if (!n_option)
        ft_putchar_fd('\n', 1);

    return (0);
}
int ft_strcmp_echo(const char *s)
{
    int i = 0;

    if (s[0] != '-')
        return (1);

    i = 1;
    while (s[i] == 'n')
        i++;

    if (s[i] != '\0')
        return (1);

    return (0);
}
