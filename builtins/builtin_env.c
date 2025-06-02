/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:18:24 by salhali           #+#    #+#             */
/*   Updated: 2025/06/02 15:09:36 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_env(t_shell *shell)
{
    int i;

    i = 0;
    while (shell->env && shell->env[i])
    {
        ft_putstr_fd(shell->env[i], 1);
        ft_putchar_fd('\n', 1);
        i++;
    }
    return (0);
}
