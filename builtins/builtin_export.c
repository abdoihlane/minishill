/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/05/25 18:07:00 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_export(c_cmd *cmd, t_shell *shell)
{
    int i;
    char *equal_sign;
    char *name;
    char *value;

    if (!cmd->array || !cmd->array[1])
        return (builtin_env(shell));

    i = 1;
    while (cmd->array[i])
    {
        equal_sign = ft_strchr(cmd->array[i], '=');
        if (equal_sign)
        {
            // Split name=value
            *equal_sign = '\0';
            name = cmd->array[i];
            value = equal_sign + 1;
            update_env_variable(shell, name, value);
            *equal_sign = '='; // Restore original string
        }
        else
        {
            // Just export the variable (set to empty if not exists)
            if (!get_env_value(shell->env, cmd->array[i]))
                update_env_variable(shell, cmd->array[i], "");
        }
        i++;
    }

    return (0);
}
