/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:45:22 by salhali           #+#    #+#             */
/*   Updated: 2025/05/25 16:29:36 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_cd(c_cmd *cmd, t_shell *shell)
{
    char *path;
    char current_dir[1024];

    // Save current directory for OLDPWD
    if (getcwd(current_dir, 1024) == NULL)
        return (1);

    // If no argument, go to HOME
    if (!cmd->array || !cmd->array[1])
        path = get_env_value(shell->env, "HOME");
    else if (ft_strcmp(cmd->array[1], "~") == 0)
        path = get_env_value(shell->env, "HOME");
    else
        path = cmd->array[1];

    if (!path)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
        return (1);
    }

    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (1);
    }

    // Update PWD and OLDPWD environment variables
    update_env_variable(shell, "OLDPWD", current_dir);
    if (getcwd(current_dir, 1024) != NULL)
        update_env_variable(shell, "PWD", current_dir);

    return (0);
}
