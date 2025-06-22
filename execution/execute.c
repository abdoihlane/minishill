/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:16:53 by salhali           #+#    #+#             */
/*   Updated: 2025/06/22 17:16:57 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_cmds(c_cmd *clist, t_shell *shell)
{
    int in_fd = 0;
    int pipe_fd[2];
    pid_t pid;

    while (clist)
    {
        if (clist->next != NULL)
            pipe(pipe_fd);

        pid = fork();
        if (pid == 0)
        {
            if (in_fd != 0)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (clist->next)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            setup_redirections(clist);
            if (is_builtin(clist))
                exit(execute_builtin(clist, shell));

            char *cmd_path = find_path(clist->array[0], shell->env);
            if (!cmd_path)
            {
                perror("execve");
                exit(1);
            }
            execve(cmd_path, clist->array, shell->env);
        }
        else if (pid < 0)
            perror("fork");
        else
        {
            if (in_fd != 0)
                close(in_fd);
            if (clist->next)
                close(pipe_fd[1]);

            in_fd = pipe_fd[0];
            waitpid(pid, NULL, 0);
        }
        clist = clist->next;
    }
}

