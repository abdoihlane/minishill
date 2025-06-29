/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/06/28 16:49:10 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int builtin_export(c_cmd *cmd, t_shell *shell)
// {
//     int i = 1;

//     if (!cmd->array[1])
//     {
//         print_env_sorted(shell->envv); // print sorted
//         return 0;
//     }
//     while (cmd->array[i])
//     {
//         char *equal = ft_strchr(cmd->array[i], '=');
//         if (equal)
//         {
//             *equal = '\0';
//             char *key = cmd->array[i];
//             char *value = equal + 1;
//             update_env_list(shell, key, value);
//             *equal = '=';
//         }
//         else
//         {
//             if (!get_env_value_ll(shell->envv, cmd->array[i]))
//                 update_env_list(shell, cmd->array[i], "");
//         }
//         i++;
//     }
//     return 0;
// }
// int builtin_export(c_cmd *cmd, t_shell *shell)
// {
//     int i = 1;

//     if (!cmd->array[1])
//     {
//         print_env_sorted(shell->envv); // print sorted
//         return 0;
//     }
//     // printf("before run spam\n");
//     // while (cmd->array[1] != NULL)
//     // {
//     //     char    *str = cmd->array[1];
//     //     char    *result = ft_strchr(str, '=');
//     //     if(result)
//     //     {
//     //         *result = '\0';
//     //         update_env_list(shell, str, result);
//     //         *result = '=';

//     //     }
//     // }
//     if (cmd->array[1] && cmd->qflag == 1 && cmd->array[1][0] == '\0')
//     {
//         ft_putstr_fd("bash: ", 2);
//         ft_putstr_fd("export: ", 2);
//         ft_putstr_fd("No such file or directory\n", 2);
//         return(1);
//     }
//     while (cmd->array[i])
//     {
//         char *arg = cmd->array[i];
//         char *eq = ft_strchr(arg, '=');
//         if (eq)
//         {
//             *eq = '\0';
//             update_env_list(shell, arg, eq + 1); // khdmt key + value
//             *eq = '=';
//         }
//         else
//             update_env_list(shell, arg, NULL);
//         i++;
//     }
//     return 0;
// }


int is_valid_var(const char *str)
{
    int i = 1;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return 0;
        i++;
	}
	return 1;
}

void print_env_sorted(t_env *envv)
{
	t_env *copy = NULL;
	t_env *tmp = envv;

	// Copy list
	while (tmp)
	{
		t_env *node = malloc(sizeof(t_env));
		node->key = ft_strdup(tmp->key);
		node->value = tmp->value ? ft_strdup(tmp->value) : NULL;
		node->next = copy;
		copy = node;
		tmp = tmp->next;
	}

	// Sort copy by key (bubble sort for simplicity)
	int swapped;
	t_env *ptr;
	do {
		swapped = 0;
		ptr = copy;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				// Swap contents
				char *tmp_key = ptr->key;
				char *tmp_val = ptr->value;
				ptr->key = ptr->next->key;
				ptr->value = ptr->next->value;
				ptr->next->key = tmp_key;
				ptr->next->value = tmp_val;
				swapped = 1;
			}
			ptr = ptr->next;
		}
	} while (swapped);

	// Print
	ptr = copy;
	while (ptr)
	{
		if (ptr->value)
			printf("declare -x %s=\"%s\"\n", ptr->key, ptr->value);
		else
			printf("declare -x %s\n", ptr->key);
		ptr = ptr->next;
	}

	// Free copy
	while (copy)
	{
		t_env *next = copy->next;
		free(copy->key);
		free(copy->value);
		free(copy);
		copy = next;
	}
}

// int builtin_export(c_cmd *cmd, t_shell *shell)
// {
//     int i = 1;
// 	if (!cmd->array[1])
// 	{
// 		print_env_sorted(shell->envv);
// 		return 0;
// 	}

// 	while (cmd->array[i])
// 	{
// 		char *arg = cmd->array[i];
// 		char *eq = ft_strchr(arg, '=');

// 		if (!is_valid_var(arg))
// 		{
// 			printf("minishell: export: `%s`: not a valid identifier\n", arg);
// 			shell->last_exit_status = 1;
// 			continue;
// 		}

// 		if (eq)
// 		{
// 			*eq = '\0';
// 			update_env_variable(shell, arg, eq + 1);
// 			*eq = '=';
// 		}
// 		else
// 			update_env_variable(shell, arg, "");
//         i++;
// 	}
// 	return 0;
// }


int builtin_export(c_cmd *cmd, t_shell *shell)
{
    int i = 1;

    // export with no args: print all sorted env
    if (!cmd->array[1])
    {
        t_env *tmp = shell->envv;
        while (tmp)
        {
            if (tmp->value)
                printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
            else
                printf("declare -x %s\n", tmp->key);
            tmp = tmp->next;
        }
        return 0;
    }

    // export with assignments
    while (cmd->array[i])
    {
        char *arg = cmd->array[i];
        char *equal = ft_strchr(arg, '=');
        if (equal)
        {
            *equal = '\0';
            char *key = arg;
            char *value = equal + 1;

            // update existing or create new
            t_env *node = shell->envv;
            int found = 0;
            while (node)
            {
                if (ft_strcmp(node->key, key) == 0)
                {
                    free(node->value);
                    node->value = ft_strdup(value);
                    found = 1;
                    break;
                }
                node = node->next;
            }

            if (!found)
            {
                t_env *new = malloc(sizeof(t_env));
                new->key = ft_strdup(key);
                new->value = ft_strdup(value);
                new->next = shell->envv;
                shell->envv = new;
            }

            *equal = '=';
        }
        else
        {
            // just declare a var with no value (export var)
            // check if already exists
            t_env *node = shell->envv;
            int exists = 0;
            while (node)
            {
                if (ft_strcmp(node->key, arg) == 0)
                {
                    exists = 1;
                    break;
                }
                node = node->next;
            }
            if (!exists)
            {
                t_env *new = malloc(sizeof(t_env));
                new->key = ft_strdup(arg);
                new->value = NULL;
                new->next = shell->envv;
                shell->envv = new;
            }
        }

        i++;
    }

    return 0;
}
