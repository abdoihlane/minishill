/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:20:16 by salhali           #+#    #+#             */
/*   Updated: 2025/07/23 19:04:31 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_from_string(char *env_str, char *equal_pos)
{
	t_env	*new;

	*equal_pos = '\0';
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(env_str);
	new->value = ft_strdup(equal_pos + 1);
	new->next = NULL;
	*equal_pos = '=';
	return (new);
}

void build_env_list(t_shell *shell, char **envp)
{
	t_env	*new;
	t_env	*last;
	char	*equal;
	int		i;

	last = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			new = create_env_from_string(envp[i], equal);
			if (!new)
				return ;
			if (!shell->envv)
				shell->envv = new;
			else
				last->next = new;
			last = new;
		}
		i++;
	}
}

void update_env_variable(t_shell *shell, const char *name, const char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = shell->envv;
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
	new = malloc(sizeof(t_env));
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
	int	i = 0;
	while (tmp)
	{
		envp[i] = ft_strjoin_triple(tmp->key, "=", tmp->value);
		tmp = tmp->next;
		i++;
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
