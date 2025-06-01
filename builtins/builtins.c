/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:09:02 by salhali           #+#    #+#             */
/*   Updated: 2025/06/01 18:06:50 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(c_cmd *command)
{
    char *cmd =  command->cmd;
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "echo") == 0 || // echo ist Done
        ft_strcmp(cmd, "cd") == 0 || // cd its Done
        ft_strcmp(cmd, "pwd") == 0 || // pwd its Done
        ft_strcmp(cmd, "export") == 0 || // export
        ft_strcmp(cmd, "unset") == 0 || //
        ft_strcmp(cmd, "env") == 0 || // its Done
        ft_strcmp(cmd, "exit") == 0) // its Done
        return (1);
    return (0);
}


int execute_builtin(c_cmd *cmd, t_shell *shell)
{
    if (ft_strcmp(cmd->cmd, "echo") == 0)
        return (builtin_echo(cmd));
    else if (ft_strcmp(cmd->cmd, "cd") == 0)
        return (builtin_cd(cmd, shell));
    else if (ft_strcmp(cmd->cmd, "pwd") == 0)
        return (builtin_pwd());
    else if (ft_strcmp(cmd->cmd, "export") == 0)
        return (builtin_export(cmd, shell));
    else if (ft_strcmp(cmd->cmd, "unset") == 0)
        return (builtin_unset(cmd, shell));
    else if (ft_strcmp(cmd->cmd, "env") == 0)
        return (builtin_env(shell));
    else if (ft_strcmp(cmd->cmd, "exit") == 0)
        builtin_exit(cmd, shell);
    return (1); // Error
}
