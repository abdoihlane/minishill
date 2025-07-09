/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:20:16 by salhali           #+#    #+#             */
/*   Updated: 2025/07/09 18:36:33 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
