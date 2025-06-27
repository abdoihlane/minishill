/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/06/27 17:15:48 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	heredoc_input(char *delimiter)
// {
// 	char	*line = NULL;
// 	size_t	len = 0;
// 	int		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		perror("heredoc open");
// 		return;
// 	}

// 	while (1)
// 	{
// 		write(1, "> ", 2);
// 		ssize_t nread = getline(&line, &len, stdin);
// 		if (nread == -1)
// 			break;

// 		// delete newline for comparison
// 		if (line[nread - 1] == '\n')
// 			line[nread - 1] = '\0';

// 		if (strcmp(line, delimiter) == 0)
// 			break;

// 		write(fd, line, strlen(line));
// 		write(fd, "\n", 1);
// 	}
// 	free(line);
// 	close(fd);
// }

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *input_user;
    c_cmd *clist = NULL;
    w_list *wlist = NULL;
    T_list *token = NULL;
    pars_T *pars = NULL;
    t_shell shell;

    shell.env = dup_envp(envp);
    shell.last_exit_status = 0;
    shell.envv = NULL;
    build_env_list(&shell);

    while (1)
    {
        input_user = readline("\001\033[38;2;255;105;180m\002➜  minishell \001\033[0m\002");
        if (!input_user)
            return 0;

        if (HardcodeChecks(input_user) == 0)
        {
            printf("syntax error\n");
            continue;
        }

        call_all(input_user, &wlist);
        token = typesee(&wlist);
        splitit(token, &clist);
        add_history(input_user);

        if (clist != NULL && is_builtin(clist) != '\0' && clist->next == NULL)
            execute_builtin(clist, &shell);
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
// ├── main.c              (your current main)
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
            