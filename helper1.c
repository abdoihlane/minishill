/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:20:16 by salhali           #+#    #+#             */
/*   Updated: 2025/06/28 15:58:51 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void build_env_list(t_shell *shell)
// {
//     int i;
//     char    *equal;

//     i = 0;
//     while (shell->env[i])
//     {
//         equal = ft_strchr(shell->env[i], '=');
//         if (equal)
//         {
//             *equal = '\0';
//             char *key = shell->env[i];
//             char *value = equal + 1;
//             update_env_list(shell, key, value);
//             *equal = '=';
//         }
//         i++;
//     }
// }

// void build_env_list(t_shell *shell)
// {
//     int i = 0;
//     char *equal;
//     t_env *new;
//     t_env *last = NULL;

//     while (shell->env[i])
//     {
//         equal = ft_strchr(shell->env[i], '=');
//         if (equal)
//         {
//             *equal = '\0';
//             char *key = shell->env[i];
//             char *value = equal + 1;

//             new = malloc(sizeof(t_env));
//             if (!new)
//                 return;

//             new->key = ft_strdup(key);
//             new->value = ft_strdup(value);
//             new->next = NULL;

//             if (!shell->envv)
//                 shell->envv = new;
//             else
//                 last->next = new;

//             last = new;

//             *equal = '=';
//         }
//         i++;
//     }
// }

// int count_env_vars(char **env)
// {
//     int count;

//     count = 0;
//     while (env && env[count])
//         count++;

//     return (count);
// }

// char *create_env_string(const char *name, const char *value)
// {
//     char *new_var;
//     int name_len;
//     int value_len;

//     name_len = ft_strlen(name);
//     value_len = ft_strlen(value);

//     new_var = malloc(name_len + value_len + 2); // +2 for '=' and '\0'
//     if (!new_var)
//         return (NULL);

//     ft_strcpy(new_var, name);
//     // ft_strlcat(new_var, "=");
//     // ft_strlcat(new_var, value);

//     return (new_var);
// }

// // void    loop
// void update_env_variable(t_shell *shell, const char *name, const char *value)
// {
//     int i;
//     int name_len;
//     char **new_env;
//     int env_count;

//     if (!shell || !name || !value)
//         return;

//     name_len = ft_strlen(name);
//     i = 0;

//     while (shell->env && shell->env[i])
//     {
//         if (ft_strncmp(shell->env[i], name, name_len) == 0 && shell->env[i][name_len] == '=')
//         {
//             free(shell->env[i]);
//             shell->env[i] = create_env_string(name, value);
//             return;
//         }
//         i++;
//     }
//     env_count = count_env_vars(shell->env);
//     new_env = malloc((env_count + 2) * sizeof(char *)); // +2 for new var and NULL
//     if (!new_env)
//         return;

//     i = 0;
//     while (i < env_count)
//     {
//         new_env[i] = shell->env[i];
//         i++;
//     }

//     new_env[i] = create_env_string(name, value);
//     new_env[i + 1] = NULL;

//     if (shell->env)
//         free(shell->env);
//     shell->env = new_env;
// }

// void delete_env_variable(t_shell *shell, const char *name)
// {
//     int i;
//     int j;
//     int name_len;
//     char **new_env;
//     int env_count;

//     if (!shell || !name || !shell->env)
//         return;

//     name_len = ft_strlen(name);
//     env_count = count_env_vars(shell->env);

//     i = 0;
//     while (shell->env[i])
//     {
//         if (ft_strncmp(shell->env[i], name, name_len) == 0 &&
//             shell->env[i][name_len] == '=')
//         {
//             new_env = malloc(env_count * sizeof(char *));
//             if (!new_env)
//                 return;

//             j = 0;
//             int k = 0;
//             while (k < env_count)
//             {
//                 if (k != i)
//                     new_env[j++] = shell->env[k];
//                 else
//                     free(shell->env[k]);
//                 k++;
//             }
//             new_env[j] = NULL;
//             free(shell->env);
//             shell->env = new_env;
//             return;
//         }
//         i++;
//     }
// }


#include "minishell.h"

void build_env_list(t_shell *shell, char **envp)
{
	t_env *new;
	t_env *last = NULL;
	char *equal;

	for (int i = 0; envp[i]; i++)
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			*equal = '\0';
			new = malloc(sizeof(t_env));
			if (!new)
				return;
			new->key = ft_strdup(envp[i]);
			new->value = ft_strdup(equal + 1);
			new->next = NULL;

			if (!shell->envv)
				shell->envv = new;
			else
				last->next = new;
			last = new;
			*equal = '=';
		}
	}
}

void update_env_variable(t_shell *shell, const char *name, const char *value)
{
	t_env *tmp = shell->envv;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return;
		}
		tmp = tmp->next;
	}

	// variable not found → add it
	t_env *new = malloc(sizeof(t_env));
	if (!new)
		return;
	new->key = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = shell->envv;
	shell->envv = new;
}

void delete_env_variable(t_shell *shell, const char *name)
{
	t_env *curr = shell->envv;
	t_env *prev = NULL;

	while (curr)
	{
		if (ft_strcmp(curr->key, name) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->envv = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

char **generate_envp_from_envlist(t_shell *shell)
{
	int count = 0;
	t_env *tmp = shell->envv;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	char **envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return NULL;

	tmp = shell->envv;
	for (int i = 0; tmp; i++)
	{
		envp[i] = ft_strjoin_triple(tmp->key, "=", tmp->value);
		tmp = tmp->next;
	}
	envp[count] = NULL;
	return envp;
}

char *ft_strjoin_triple(char *a, char *b, char *c)
{
	char *tmp = ft_strjoin(a, b);
	char *res = ft_strjoin(tmp, c);
	free(tmp);
	return res;
}
