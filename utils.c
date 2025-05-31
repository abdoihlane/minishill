/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:03:48 by salhali           #+#    #+#             */
/*   Updated: 2025/05/31 15:20:07 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(char **env, const char *name)
{
    int i;
    int name_len;

    if (env == NULL || name == NULL)
        return (NULL);

    name_len = ft_strlen(name);
    i = 0;

    while (env[i] != NULL)
    {
        if (ft_strncmp(env[i], name, name_len) == 0 && ft_strchr(env[i], '=') != NULL)
            return (env[i] + name_len + 1);
        i++;
    }
    printf("%d\n", i);
    return (NULL);
}


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

    int k = 0;
    while (shell->env[k])
        printf("-|-%s\n",shell->env[k++]);
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

c_cmd   *create_test_cmd(char *cmd_name, char **args)
{
    c_cmd *cmd;
    int count;
    int i;

    cmd = malloc(sizeof(c_cmd));
    if (!cmd)
        return NULL;

    cmd->index = 0;
    cmd->cmd = ft_strdup(cmd_name);

    count = 0;
    while (args && args[count])
        count++;

    // Copy arguments
    cmd->array = malloc(sizeof(char *) * (count + 1));
    if (!cmd->array)
    {
        free(cmd);
        return NULL;
    }
    i = 0;
    while (i < count)
    {
        cmd->array[i] = ft_strdup(args[i]);
        i++;
    }
    cmd->array[count] = NULL;
    cmd->file = NULL;
    cmd->next = NULL;
    return cmd;
}

//  Function dyal duplication dyal envp
char **dup_envp(char **envp)
{
    int i = 0;
    int count = 0;
    char **new_env;

    while (envp[count])
        count++;

    new_env = malloc(sizeof(char *) * (count + 1));
    if (!new_env)
        return NULL;

    while (i < count)
    {
        new_env[i] = strdup(envp[i]);
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
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



void print_env(char **env)
{
    int i = 0;
    while (env && env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

void add_env_node(t_env **head, t_env *new)
{
    if (!*head)
    {
        *head = new;
        return;
    }
    t_env *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

// This function builds the linked list from envp
void build_env_list(t_shell *shell)
{
    int i = 0;
    char *equal_sign;
    t_env *new_node;
    
    while (shell->env[i])
    {
        equal_sign = ft_strchr(shell->env[i], '=');
        if (equal_sign)
        {
            // Split key and value
            *equal_sign = '\0';
            shell->envv->key = shell->env[i];
            shell->envv->value = equal_sign + 1;

            // Create and add new env node
            new_node = create_env_node(shell->envv->key, shell->envv->value);
            add_env_node(&(shell->env), new_node);
            *equal_sign = '=';
        }
        i++;
    }
}
t_env *create_env_node(char *key, char *value)
{
    t_env *new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = strdup(key);
    new->value = strdup(value);
    new->next = NULL;
    return (new);
}
