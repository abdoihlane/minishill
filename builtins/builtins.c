/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:09:02 by salhali           #+#    #+#             */
/*   Updated: 2025/07/22 21:40:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(c_cmd *cmd)
{
    // if (!cmd || !cmd->array || !cmd->array[1])
    // {
    //     printf("is_builtin: cmd or cmd->array is NULL\n");
    //     return 0;
    // }
    if (ft_strcmp(cmd->array[0], "echo") == 0)
        return 1;
    if (ft_strcmp(cmd->array[0], "cd") == 0)
        return 1;
    if (ft_strcmp(cmd->array[0], "pwd") == 0)
        return 1;
    if (ft_strcmp(cmd->array[0], "env") == 0)
        return (1);
    if(ft_strcmp(cmd->array[0], "export") == 0)
        return(1);
    if (ft_strcmp(cmd->array[0], "unset") == 0)
        return 1;
    if (ft_strcmp(cmd->array[0], "exit") == 0)
        return 1;
    return 0;
}

int execute_builtin(c_cmd *cmd, t_shell *shell)
{
    printf("Executing builtin command: %s\n", cmd->cmd);
    if (ft_strcmp("echo", cmd->cmd) == 0)
        return (builtin_echo(cmd));
    else if (ft_strcmp("cd", cmd->cmd) == 0)
        return (builtin_cd(cmd, shell));
    else if (ft_strcmp("pwd", cmd->cmd) == 0)
        return (builtin_pwd());
    else if (ft_strcmp("export", cmd->cmd) == 0)
        return builtin_export(cmd, shell);
    else if (ft_strcmp("unset", cmd->cmd) == 0)
        return (builtin_unset(cmd, shell));
    if (ft_strcmp("env", cmd->cmd) == 0)
        return builtin_env(cmd, shell);
    else if (ft_strcmp("exit", cmd->cmd) == 0)
        builtin_exit(cmd, shell); // if your exit returns int
    return (1); // Error
}
