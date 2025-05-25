/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:33 by salhali           #+#    #+#             */
/*   Updated: 2025/05/25 12:19:39 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_pwd(void)
{
    char cwd[1024];

    if (getcwd(cwd, 1024) == NULL)
    {
        ft_putstr_fd("pwd: error retrieving current directory\n", 2);
        return (1);
    }

    ft_putstr_fd(cwd, 1);
    ft_putchar_fd('\n', 1);

    return (0);
}

