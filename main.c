/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/06/19 18:55:50 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_input(char *delimiter)
{
	char	*line = NULL;
	size_t	len = 0;
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

		// delete newline for comparison
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (strcmp(line, delimiter) == 0)
			break;

		write(fd, line, strlen(line));
		write(fd, "\n", 1);
	}
	free(line);
	close(fd);
}

void setup_redirections(c_cmd *cmd)
{
    r_list *tmp = cmd->file;

    while (tmp)
    {
        if (tmp->inout == 1) // <
        {
            int fd = open(tmp->content, O_RDONLY);
            if (fd < 0)
                perror("open");
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (tmp->inout == 0) // >
        {
            int fd = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                perror("open");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (tmp->inout == 2) // >>
        {
            int fd = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
                perror("open");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (tmp->inout == 4)
        {
            heredoc_input(tmp->content); // write input f ".heredoc_tmp"
            int fd = open(".heredoc_tmp", O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        tmp = tmp->next;
    }
}

void    execute_cmds(c_cmd *clist, t_shell *shell)
{
    int in_fd = 0;
    int pipe_fd[2];
    pid_t pid;

    while (clist)
    {
        if (clist->next != NULL)
            pipe(pipe_fd);

        pid = fork();
        if (pid == 0) // CHILD
        {
            if (in_fd != 0)
            {
                dup2(in_fd, 0);
                close(in_fd);
            }

            if (clist->next)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], 1);
                close(pipe_fd[1]);
            }

            setup_redirections(clist); // for < > >> <<

            if (is_builtin(clist))
                exit(execute_builtin(clist, shell));
            else
                execve(clist->cmd, clist->array, shell->env); // or shell->envv

            perror("execve");
            exit(1);
        }
        else if (pid < 0)
        {
            perror("fork");
        }
        else // PARENT
        {
            if (in_fd != 0)
                close(in_fd);
            if (clist->next)
                close(pipe_fd[1]);

            in_fd = pipe_fd[0];

            waitpid(pid, NULL, 0); // tsanna child
        }
        clist = clist->next;
    }
}

int main(int argc, char **argv, char **envp)
{
     (void)argc;
     (void)argv;
     char *input_user;
     c_cmd *clist = NULL;
     w_list *wlist = NULL;
     T_list *token = NULL;
     pars_T *pars = NULL;
     t_shell    shell;

     shell.env = dup_envp(envp);
     shell.last_exit_status = 0;
     shell.envv = NULL;
     build_env_list(&shell); // ydir conversion mn env[] ➜ linked list
     while (1)
     {
        input_user = readline("\001\033[38;2;255;105;180m\002➜  minishell \001\033[0m\002");
        if (!input_user)
            return 0;
        else
        {
            if(HardcodeChecks(input_user) == 0)
            {
                    printf("syntax error\n");
                        continue;
            }
            call_all(input_user,&wlist);
            token = typesee(&wlist);
            splitit(token,&clist);
            add_history(input_user);
            execute_cmds(clist, &shell);
            // print_cmd_list(clist);
            free_wlist(&wlist);
            free_Plist(&pars);
            wlist = NULL;
            free(input_user);
            rl_on_new_line(); // Regenerate the prompt on a newline
            rl_replace_line("", 0); // Clear the previous text
        }
     }
     return 0;
}
