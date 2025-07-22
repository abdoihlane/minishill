/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/07/22 19:56:51 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_input(char *delimiter, r_list *head)
{
	char	*line = NULL;
    char    *expanded = NULL;
	size_t	len = 0;
    signal(SIGINT, sigint_heredoc);

	int		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc open");
		return;
	}

	while (1)
	{
		write(1, "> ", 2);
		ssize_t nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);      //  free line
			line = NULL;     //  reset line bach ma n3awdch nfreeeha
			break;
		}
		expanded = expand_variables(line);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	head->content = ft_strdup(".heredoc_tmp");
	head->inout = 0; //  set inout to 4 for heredoc
	if (line)               //  free ghir ila mazal line ma tfreeatch
		free(line);
	close(fd);
}

t_env *convert_envp_to_envlist(char **envp)
{
	t_env *head = NULL;
	t_env *last = NULL;
    int i = 0;
	while (envp[i])
	{
		char *equal = ft_strchr(envp[i], '=');
		if (!equal)
			continue;

		t_env *node = malloc(sizeof(t_env));
		if (!node)
			return NULL;

		*equal = '\0'; // temporarily break key=value
		node->key = ft_strdup(envp[i]);
		node->value = ft_strdup(equal + 1);
		*equal = '=';  // restore original string

		node->next = NULL;
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
        i++;
	}
	return head;
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
        // if (clist != NULL && is_builtin(clist) != '\0' && clist->next == NULL && clist->file == NULL)
		// {
		// 	printf("is here !!\n");
        //     execute_builtin(clist, &shell);
		// }
        // else
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
