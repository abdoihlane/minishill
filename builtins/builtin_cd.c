/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:45:22 by salhali           #+#    #+#             */
/*   Updated: 2025/06/21 19:43:20 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_cd(c_cmd *cmd, t_shell *shell)
{
    char *path;
    char current_dir[1024];
    // Get the name of the current working directory
    if (getcwd(current_dir, 1024) == NULL)
        return (1);

    int len = 0;
    while(cmd->array[len])
        len++;
    // if (i > 2)
    //     return(ft_putstr_fd("bash: cd: too many arguments\n", 2), 1);
    if (len <= 2)
    {
        // printf("cmd->flags = %d\n", cmd->qflag);
        if (cmd->array[1] == NULL)
            path = get_env_value_ll(shell->envv, "HOME"); // ou hta ila makan walo nsift lhome
        else if (ft_strcmp(cmd->array[1], "~") == 0)
            path = get_env_value_ll(shell->envv, "HOME"); // ila kan cd  ~ nsiftk lhome nichan
        else
            path = cmd->array[1]; // 3tini hadak path ndik lih
        // ila kan cd "" maybadl walo nkhalik f nafs path
        if(cmd->array[1] && cmd->qflag == 1)
            path = getcwd(current_dir, 1024);
        // printf("path = %s\n", path);
        if (path == NULL)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (1);
        }

        if (chdir(path) == -1)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(path, 2);
            ft_putstr_fd("No such file or directory\n", 2);
            return (1);
        }

        // Update PWD and OLDPWD environment variables
        update_env_variable(shell, "OLDPWD", current_dir);
        if (getcwd(current_dir, 1024) != NULL)
            update_env_variable(shell, "PWD", current_dir);
    }
    else
    {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(" too many arguments\n", 2);
            return (1);
    }
    return (0);
}

