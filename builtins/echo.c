/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:21:22 by salhali           #+#    #+#             */
/*   Updated: 2025/05/19 19:32:16 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_echo(c_cmd *cmd)
{
    int i;
    int n_option;

    i = 1;
    n_option = 0;
    // Check for -n option
    if (cmd->array[i] != '\0' && ft_strcmp(cmd->array[i], "-n") == 0)
    {
        n_option = 1;
        i++;
    }
    // Print all arguments
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
int ft_strcmp(char *dest, char *src)
{
    size_t  i;
    // unsigned char   *ptr1;
    // unsigned char   *ptr2;

    // ptr1 = (unsigned char *)dest;
    // ptr2 = (unsigned char *)src;

    while(src[i] != '\0' && dest[i] != '\0')
    {
        if(src[i] == dest[i])
            return(src[i] - dest[i]);
        i++;
    }
    return(src[i] - dest[i]);
}
