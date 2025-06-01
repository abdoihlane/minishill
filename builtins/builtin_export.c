/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/06/01 18:37:39 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_export(c_cmd *cmd, t_shell *shell)
{
    int i = 1;
    if (!cmd->array[1])
    {
        print_env_sorted(shell->envv); // print sorted
        return 0;
    }
    while (cmd->array[i])
    {
        char *equal = ft_strchr(cmd->array[i], '=');
        if (equal)
        {
            *equal = '\0';
            char *key = cmd->array[i];
            char *value = equal + 1;
            update_env_list(shell, key, value);
            *equal = '=';
        }
        else
        {
            if (!get_env_value_ll(shell->envv, cmd->array[i]))
                update_env_list(shell, cmd->array[i], "");
        }
        i++;
    }
    return 0;
}
