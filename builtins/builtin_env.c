/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:18:24 by salhali           #+#    #+#             */
/*   Updated: 2025/06/05 18:37:07 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_env(c_cmd *cmd, t_shell *shell)
{
    t_env *tmp;

    tmp = shell->envv;
    if(cmd->array[1] != NULL)
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd("No such file or directory\n", 2);
        return(1);
    }
    while (tmp)
    {
        if (tmp->value) // matprintich les vars li ma fihach '='
        {
            printf("%s=%s\n", tmp->key, tmp->value);
        }
        tmp = tmp->next;
    }
    return (0);
}
