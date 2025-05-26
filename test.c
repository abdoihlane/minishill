/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:45:22 by salhali           #+#    #+#             */
/*   Updated: 2025/05/26 19:48:11 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_cd(c_cmd *cmd, t_shell *shell)
{
    char *path;
    char *home_value;
    char current_dir[1024];

    // Get current directory SAFELY
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("cd: getcwd");
        return (1);
    }

    // Determine target path - MA KATFREE WALOU HUNA!
    if (!cmd->array || !cmd->array[1])
    {
        // cd without arguments -> go to HOME
        home_value = get_env_value(shell->env, "HOME");
        if (!home_value)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (1);
        }
        path = home_value; // DIRECT POINTER - MA KATFREE!
    }
    else if (ft_strcmp(cmd->array[1], "-") == 0)
    {
        // cd - -> go to OLDPWD
        path = get_env_value(shell->env, "OLDPWD");
        if (!path)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", 2);
            return (1);
        }
        // Print directory (bash behavior)
        ft_putstr_fd(path, 1);
        ft_putstr_fd("\n", 1);
        // path huna pointer direct - MA KATFREE!
    }
    else
    {
        // Regular path from command line
        path = cmd->array[1]; // DIRECT POINTER - MA KATFREE!
    }

    // Try to change directory
    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (1);
    }

    // Update environment variables
    update_env_variable(shell, "OLDPWD", current_dir);

    // Get new directory and update PWD
    if (getcwd(current_dir, sizeof(current_dir)) != NULL)
        update_env_variable(shell, "PWD", current_dir);

    return (0);
}

/* Alternative version ila bghiti tkun extra safe */
int builtin_cd_extra_safe(c_cmd *cmd, t_shell *shell)
{
    char *path = NULL;
    char *home_value = NULL;
    char current_dir[PATH_MAX];
    char new_dir[PATH_MAX];
    int result = 0;

    // Get current directory
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("cd: getcwd");
        return (1);
    }

    // Determine path - COPY kul shi bach ma ndir free 3la wrong pointer
    if (!cmd->array || !cmd->array[1])
    {
        home_value = get_env_value(shell->env, "HOME");
        if (!home_value)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (1);
        }
        path = ft_strdup(home_value); // COPY JADIDA
        if (!path)
            return (1);
    }
    else if (ft_strcmp(cmd->array[1], "-") == 0)
    {
        home_value = get_env_value(shell->env, "OLDPWD");
        if (!home_value)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", 2);
            return (1);
        }
        ft_putstr_fd(home_value, 1);
        ft_putstr_fd("\n", 1);
        path = ft_strdup(home_value); // COPY JADIDA
        if (!path)
            return (1);
    }
    else
    {
        path = ft_strdup(cmd->array[1]); // COPY JADIDA
        if (!path)
            return (1);
    }

    // Change directory
    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        result = 1;
        goto cleanup;
    }

    // Update environment
    update_env_variable(shell, "OLDPWD", current_dir);
    if (getcwd(new_dir, sizeof(new_dir)) != NULL)
        update_env_variable(shell, "PWD", new_dir);

cleanup:
    if (path)
        free(path); // Dabaآمن نfree-h
    return (result);
}

/* DEBUG version bach tshuf fin l mushkila */
int builtin_cd_debug(c_cmd *cmd, t_shell *shell)
{
    char *path;
    char current_dir[PATH_MAX];

    printf("DEBUG: cd function called\n");

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
