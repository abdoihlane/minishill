/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:45:22 by salhali           #+#    #+#             */
/*   Updated: 2025/05/27 18:05:38 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes dyalk
void update_env_variable(t_shell *shell, const char *name, const char *value);
char *create_env_string(const char *name, const char *value);
int count_env_vars(char **env);

// Struct dyal shell li kat3tamd 3liha
typedef struct s_shell
{
    char **env;
} t_shell;

// Helpers (dirhom f file .c / .h dyalk)
char *create_env_string(const char *name, const char *value)
{
    char *str;
    int len = strlen(name) + strlen(value) + 2; // +1 for =, +1 for \0
    str = malloc(len);
    if (!str)
        return NULL;
    sprintf(str, "%s=%s", name, value);
    return str;
}

int count_env_vars(char **env)
{
    int i = 0;
    while (env && env[i])
        i++;
    return i;
}

void update_env_variable(t_shell *shell, const char *name, const char *value)
{
    int i = 0;
    int name_len = strlen(name);
    char **new_env;
    int env_count;

    while (shell->env && shell->env[i])
    {
        if (strncmp(shell->env[i], name, name_len) == 0 && shell->env[i][name_len] == '=')
        {
            free(shell->env[i]);
            shell->env[i] = create_env_string(name, value);
            return;
        }
        i++;
    }

    env_count = count_env_vars(shell->env);
    new_env = malloc((env_count + 2) * sizeof(char *));
    if (!new_env)
        return;

    i = 0;
    while (i < env_count)
    {
        new_env[i] = shell->env[i];
        i++;
    }
    new_env[i] = create_env_string(name, value);
    new_env[i + 1] = NULL;

    free(shell->env);
    shell->env = new_env;
}

void print_env(char **env)
{
    int i = 0;
    while (env && env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

