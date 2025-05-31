/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:21:22 by salhali           #+#    #+#             */
/*   Updated: 2025/05/31 19:12:50 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int builtin_echo(c_cmd *cmd)
// {
//     int i;
//     int n_option;

//     i = 1;
//     n_option = 0;
//     // printf("array fih : %s\n", cmd->array[0]);
//     if (cmd->array && cmd->array[i] && ft_strcmp_echo(cmd->array[i], "-n") == 0)
//     {
//         n_option = 1;
//         i++;
//     }
//     while (cmd->array[i])
//     {
//         ft_putstr_fd(cmd->array[i], 1);
//         if (cmd->array[i + 1])
//             ft_putchar_fd(' ', 1);
//         i++;
//     }
//     if (!n_option)
//         ft_putchar_fd('\n', 1);
    
//     return (0);
// }

// int    ft_strcmp_echo(char *s1, const char *s2)
// {
//     int i;

//     i = 0;
//     while(s1[i])
//     {
//         if(s1[i] == s2[i])
//             return(0);
//         i++;
//     }
//     return(1);
// }

#include "../minishell.h"

int builtin_echo(c_cmd *cmd)
{
    int i;
    int n_option;

    i = 1;
    n_option = 0;
    
    // Handle multiple -n flags (like bash does)
    while (cmd->array && cmd->array[i] && ft_strcmp_echo(cmd->array[i], "-n") == 0)
    {
        n_option = 1;
        i++;
    }
    
    // Print arguments with spaces between them
    while (cmd->array[i])
    {
        ft_putstr_fd(cmd->array[i], 1);
        if (cmd->array[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    
    // Add newline unless -n option was used
    if (!n_option)
        ft_putchar_fd('\n', 1);
    
    return (0);
}

// Fixed string comparison function
int ft_strcmp_echo(char *s1, const char *s2)
{
    int i;

    if (!s1 || !s2)
        return (1);
    
    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (1);
        i++;
    }
    
    // Both strings must end at the same time for exact match
    if (s1[i] == '\0' && s2[i] == '\0')
        return (0);
    
    return (1);
}