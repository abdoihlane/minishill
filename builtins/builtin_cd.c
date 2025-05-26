/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:45:22 by salhali           #+#    #+#             */
/*   Updated: 2025/05/26 19:50:28 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int builtin_cd(c_cmd *cmd, t_shell *shell)
// {
//     char *path;
//     char current_dir[1024];

//     // Get the name of the current working directory
//     if (getcwd(current_dir, 1024) == NULL)
//         return (1);

//     if (!cmd->array || !cmd->array[1])
//         path = get_env_value(shell->env, "HOME");

//     else if (ft_strcmp(cmd->array[1], "~") == 0)
//         path = get_env_value(shell->env, "HOME");
//     else
//         path = cmd->array[1];


//     if (!path)
//     {
//         ft_putstr_fd("cd: HOME not set\n", 2);
//         return (1);
//     }

//     if (chdir(path) == -1)
//     {
//         ft_putstr_fd("cd: ", 2);
//         ft_putstr_fd(path, 2);
//         ft_putstr_fd(": No such file or directory\n", 2);
//         return (1);
//     }

//     // Update PWD and OLDPWD environment variables
//     update_env_variable(shell, "OLDPWD", current_dir);
//     if (getcwd(current_dir, 1024) != NULL)
//         update_env_variable(shell, "PWD", current_dir);
//     return (0);
// }

int builtin_cd(c_cmd *cmd, t_shell *shell)
{
    char *path;
    char current_dir[1024];

    printf("DEBUG: cd function called its Dne\n");

    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        printf("DEBUG: getcwd failed\n");
        return (1);
    }
    printf("DEBUG: current_dir = %s\n", current_dir);

    if (!cmd->array || !cmd->array[1])
    {
        printf("DEBUG: no arguments, going to HOME\n");
        path = get_env_value(shell->env, "HOME");
        printf("DEBUG: HOME = %s\n", path ? path : "NULL");
    }
    else
    {
        printf("DEBUG: argument = %s\n", cmd->array[1]);
        path = cmd->array[1];
    }

    if (!path)
    {
        printf("DEBUG: path is NULL\n");
        ft_putstr_fd("cd: HOME not set\n", 2);
        return (1);
    }

    printf("DEBUG: trying chdir to %s\n", path);
    if (chdir(path) == -1)
    {
        printf("DEBUG: chdir failed\n");
        perror("cd");
        return (1);
    }

    printf("DEBUG: chdir succeeded, updating env vars\n");
    update_env_variable(shell, "OLDPWD", current_dir);

    if (getcwd(current_dir, sizeof(current_dir)) != NULL)
    {
        printf("DEBUG: new dir = %s\n", current_dir);
        update_env_variable(shell, "PWD", current_dir);
    }

    printf("DEBUG: cd completed successfully\n");
    return (0);
}
