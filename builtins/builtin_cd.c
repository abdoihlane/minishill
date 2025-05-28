/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:45:22 by salhali           #+#    #+#             */
/*   Updated: 2025/05/28 20:46:10 by salhali          ###   ########.fr       */
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


    // if (cmd->array[1] == NULL)
    //     path = get_env_value(shell->env, "HOME"); // ou hta ila makan walo nsift lhome 
    // else if (ft_strcmp(cmd->array[1], "~") == 0)
    //     path = get_env_value(shell->env, "HOME"); // ila kan cd  ~ nsiftk lhome nichan 
    // else
    path = cmd->array[1]; // 3tini hadak path ndik lih
    if (path == NULL)
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

// int builtin_cd(c_cmd *cmd, t_shell *shell)
// {
//     char *path;
//     char current_dir[1024];

//     printf("DEBUG: cd function called its Dne\n");

//     if (getcwd(current_dir, sizeof(current_dir)) == NULL)
//     {
//         printf("DEBUG: getcwd failed\n");
//         return (1);
//     }
//     if (!cmd->array || !cmd->array[1])
//     {
//         printf("DEBUG: no arguments, going to HOME\n");
//         path = get_env_value(shell->env, "HOME");
//     }
//     else
//     {
//         printf("DEBUG: argument = %s\n", cmd->array[1]);
//         path = cmd->array[1];
//     }

//     if (!path)
//     {
//         printf("DEBUG: path is NULL\n");
//         ft_putstr_fd("cd: HOME not set\n", 2);
//         return (1);
//     }

//     if (chdir(path) == -1)
//     {
//         printf("DEBUG: chdir failed\n");
//         perror("cd");
//         return (1);
//     }
//     update_env_variable(shell, "OLDPWD", current_dir);
//     if (getcwd(current_dir, sizeof(current_dir)) != NULL)
//         pdate_env_variable(shell, "PWD", current_dir);
//     return (0);
// }
