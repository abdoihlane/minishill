/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/07/23 19:10:25 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node_from_pair(char *env_str, char *equal_pos)
{
	t_env	*node;

	*equal_pos = '\0';
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(env_str);
	node->value = ft_strdup(equal_pos + 1);
	*equal_pos = '=';
	node->next = NULL;
	return (node);
}

t_env *convert_envp_to_envlist(char **envp)
{
	t_env	*head;
	t_env	*last;
	t_env	*node;
	char	*equal;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (!equal)
		{
			i++;
			continue;
		}
		node = create_env_node_from_pair(envp[i], equal);
		if (!node)
			return (NULL);
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
		i++;
	}
	return (head);
}


int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    t_shell shell;
    c_cmd *clist = NULL;
    w_list *wlist = NULL;
    T_list *token = NULL;
    pars_T *pars = NULL;
    char *input_user;

    shell.envv = convert_envp_to_envlist(envp);
    shell.last_exit_status = 0;

    while (1)
    {
        input_user = readline("\001\033[38;2;255;105;180m\002➜  minishell \001\033[0m\002");
        if (!input_user)
            return 0;
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, SIG_IGN);
        if (HardcodeChecks(input_user) == 0)
        {
            printf("syntax error\n");
            continue;
        }
        call_all(input_user, &wlist);
        token = typesee(&wlist);
        splitit(token, &clist);
            // ...existing code...
        add_history(input_user);
        if (clist != NULL && is_builtin(clist) && clist->next == NULL && clist->file == NULL)
		{
			printf("is here !!\n");
            execute_builtin(clist, &shell);
		}
        else
        	execute_cmds(clist, &shell);
        free_wlist(&wlist);
        free_Plist(&pars);
        wlist = NULL;
        free(input_user);
        rl_on_new_line();
        rl_replace_line("", 0);
    }
    return 0;
}


// minishell/
// ├── main.c               (your current main)
// ├── minishell.h         (your current header)
// ├── execution/
// │   ├── execute.c       (execute_cmds function)
// │   ├── redirections.c  (setup_redirections)
// │   └── path.c          (find_path)
// ├── builtins/
// │   ├── builtin_echo.c
// │   ├── builtin_cd.c
// │   ├── builtin_pwd.c
// │   ├── builtin_export.c
// │   ├── builtin_unset.c
// │   ├── builtin_env.c
// │   └── builtin_exit.c
// ├── parsing/
// │   ├── parser.c        (call_all, typesee, splitit)
// │   ├── tokenizer.c
// │   └── syntax.c        (HardcodeChecks)
// ├── utils/
// │   ├── env_utils.c     (environment functions)
// │   ├── memory.c        (free functions)
// │   └── signals.c       (signal handling)
// └── libft/              (your existing libft)
