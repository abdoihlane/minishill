/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:18:24 by salhali           #+#    #+#             */
/*   Updated: 2025/05/26 19:28:38 by salah            ###   ########.fr       */
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

