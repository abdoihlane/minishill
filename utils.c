/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:03:48 by salhali           #+#    #+#             */
/*   Updated: 2025/06/01 18:54:24 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *get_env_value(char **env, const char *name)
// {
//     int i;
//     int name_len;

//     if (env == NULL || name == NULL)
//         return (NULL);

//     name_len = ft_strlen(name);
//     i = 0;

//     while (env[i] != NULL)
//     {
//         if (ft_strncmp(env[i], name, name_len) == 0 && ft_strchr(env[i], '=') != NULL)
//             return (env[i] + name_len + 1);
//         i++;
//     }
//     printf("%d\n", i);
//     return (NULL);
// }


int count_env_vars(char **env)
{
    int count;

    count = 0;
    while (env && env[count])
        count++;

    return (count);
}

char *create_env_string(const char *name, const char *value)
{
    char *new_var;
    int name_len;
    int value_len;

    name_len = ft_strlen(name);
    value_len = ft_strlen(value);

    new_var = malloc(name_len + value_len + 2); // +2 for '=' and '\0'
    if (!new_var)
        return (NULL);

    ft_strcpy(new_var, name);
    // ft_strlcat(new_var, "=");
    // ft_strlcat(new_var, value);

    return (new_var);
}

// void    loop
void update_env_variable(t_shell *shell, const char *name, const char *value)
{
    int i;
    int name_len;
    char **new_env;
    int env_count;

    if (!shell || !name || !value)
        return;

    name_len = ft_strlen(name);
    i = 0;

    while (shell->env && shell->env[i])
    {
        if (ft_strncmp(shell->env[i], name, name_len) == 0 && shell->env[i][name_len] == '=')
        {
            free(shell->env[i]);
            shell->env[i] = create_env_string(name, value);
            return;
        }
        i++;
    }
    env_count = count_env_vars(shell->env);
    new_env = malloc((env_count + 2) * sizeof(char *)); // +2 for new var and NULL
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

    if (shell->env)
        free(shell->env);
    shell->env = new_env;
}

void delete_env_variable(t_shell *shell, const char *name)
{
    int i;
    int j;
    int name_len;
    char **new_env;
    int env_count;

    if (!shell || !name || !shell->env)
        return;

    name_len = ft_strlen(name);
    env_count = count_env_vars(shell->env);

    i = 0;
    while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], name, name_len) == 0 &&
            shell->env[i][name_len] == '=')
        {
            new_env = malloc(env_count * sizeof(char *));
            if (!new_env)
                return;

            j = 0;
            for (int k = 0; k < env_count; k++)
            {
                if (k != i)
                    new_env[j++] = shell->env[k];
                else
                    free(shell->env[k]);
            }
            new_env[j] = NULL;

            free(shell->env);
            shell->env = new_env;
            return;
        }
        i++;
    }
}

char    *ft_strcpy(char *dest,const char *src)
{
    int i = 0;

    if(!dest || !src)
        return(printf("check (create_env_string) 64\n "), NULL);
    while(src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return(dest);
}

// char    **function_split_env(t_shell *shell)
// {
//     char **storage = NULL;
//     // t_env *envvvvvvvv = NULL;
//     int i;
//     t_env *key = NULL;

//     i = 0;

//     while(shell->env[i] != NULL)
//     {
//         storage = ft_split(shell->env[i], '=');
//         i++;
//     }
//     int k = 0;
//     while(storage[k] != NULL)
//     {
//         key->key = storage[k];
//         k++;
//     }
//     printf("%d\n", k);
//     return(NULL);

//     // storage[i] = NULL;
//     // return (storage);
// }
// void free_env(char **env)
// {
//     int i = 0;

//     if (!env)
//         return;
//     while (env[i])
//     {
//         free(env[i]);
//         i++;
//     }
//     free(env);
// }


void print_env_sorted(t_env *env)
{
    // Count env
    int len = 0;
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }

    // Build array of keys
    char **keys = malloc(sizeof(char *) * (len + 1));
    tmp = env;

    int i = 0;
    while (i < len)
    {
        keys[i] = strdup(tmp->key);
        tmp = tmp->next;
        i++;
    }
    keys[len] = NULL;

    i = 0;
    while (i < len - 1)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (ft_strcmp(keys[j], keys[j + 1]) > 0)
            {
                char *t = keys[j];
                keys[j] = keys[j + 1];
                keys[j + 1] = t;
            }
        }
        i++;
    }

    i = 0;
    while (i < len)
    {
        char *val = get_env_value_ll(env, keys[i]);
        if (val && val[0] != '\0')
            printf("declare -x %s=\"%s\"\n", keys[i], val);
        else
            printf("declare -x %s\n", keys[i]);
        free(keys[i]);
        i++;
    }
    free(keys);
}
