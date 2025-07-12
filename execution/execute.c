// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execute.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/22 17:16:53 by salhali           #+#    #+#             */
// /*   Updated: 2025/07/01 19:18:27 by salhali          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"

char **filter_empty_args(c_cmd *cmd)
{
    char **filtered;
    int count = 0;
    int i = 0;
    int j;

    if (cmd->qflag == 0 || cmd->array == NULL)
        return cmd->array;

    while (cmd->array[i])
    {
        if (ft_strlen(cmd->array[i]) > 0)
            count++;
        i++;
    }
    filtered = malloc(sizeof(char *) * (count + 1));
    if (!filtered)
        return cmd->array;

    j = 0;
    i = 0;
    while (cmd->array[i])
    {
        if (ft_strlen(cmd->array[i]) > 0)
        {
            filtered[j] = cmd->array[i];
            j++;
        }
        i++;
    }
    filtered[j] = NULL;
    return filtered;
}

void execute_cmds(c_cmd *clist, t_shell *shell)
{
    int in_fd = 0;
    int pipe_fd[2];
    pid_t pids[100];
    int i = 0;
    char *cmd_path;
    char **filtered_args;
    char **envp = generate_envp_from_envlist(shell);


    while (clist)
    {
        if (clist->next)
            pipe(pipe_fd);

        pids[i] = fork();
        if (pids[i] == 0)
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

                // c_cmd *tmp = clist;
        // while (tmp)
        // {
        //     printf("Command  %s\n", tmp->array[0]);
        //     tmp = tmp->next;
        // }
            setup_redirections(clist);
            if (is_builtin(clist))
                exit(execute_builtin(clist, shell));

            cmd_path = find_path(clist->array[0], envp);
            if (!cmd_path)
                exit(127);

            filtered_args = filter_empty_args(clist);
            int i = 0;
            while (filtered_args[i])
            {
                printf("Argument %d: %s\n", i, filtered_args[i]);
                i++;
            }
            execve(cmd_path, filtered_args, envp);
            exit(127);
        }

        if (in_fd != 0)
            close(in_fd);
        if (clist->next)
        {
            close(pipe_fd[1]);
            in_fd = pipe_fd[0];
        }
        clist = clist->next;
        i++;
    }

    int j = 0;
    while (j < i)
    {
        waitpid(pids[j], NULL, 0);
        j++;
    }
    ft_free_2d_array(envp);
}
