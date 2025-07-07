/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:16:53 by salhali           #+#    #+#             */
/*   Updated: 2025/07/01 19:18:27 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void execute_cmds(c_cmd *clist, t_shell *shell)
// {
//     int in_fd = 0;
//     int pipe_fd[2];
//     pid_t pid;
//     char *cmd_path;
//     char **filtered_args;

//     while (clist)
//     {
//         if (clist->next != NULL)
//             pipe(pipe_fd);

//         pid = fork();
//         if (pid == 0)
//         {
//             if (in_fd != 0)
//             {
//                 dup2(in_fd, STDIN_FILENO);
//                 close(in_fd);
//             }
//             if (clist->next != NULL)
//             {
//                 close(pipe_fd[0]);
//                 dup2(pipe_fd[1], STDOUT_FILENO);
//                 close(pipe_fd[1]);
//             }
//             setup_redirections(clist);
//             if (is_builtin(clist))
//                 exit(execute_builtin(clist, shell));
//             cmd_path = find_path(clist->array[0], shell->copy_envp);
//             if (!cmd_path)
//                 printf("find_path failed !!!!\n");
//             filtered_args = filter_empty_args(clist);
//             execve(cmd_path, filtered_args, shell->copy_envp);

//             if (filtered_args != clist->array)
//                 free(filtered_args);
//             execve(cmd_path, clist->array, shell->copy_envp);
//         }
//         else if (pid < 0)
//             perror("fork");
//         else
//         {
//             if (in_fd != 0)
//                 close(in_fd);
//             if (clist->next)
//                 close(pipe_fd[1]);

//             in_fd = pipe_fd[0];
//             waitpid(pid, NULL, 0);
//         }
//         clist = clist->next;
//     }
// }


// // void execute_cmds(c_cmd *clist, t_shell *shell)
// // {
// //     int in_fd = 0;
// //     int pipe_fd[2];
// //     pid_t *pids;
// //     char *cmd_path;
// //     int cmd_count = 0;
// //     c_cmd *temp = clist;

// //     // Count the number of commands
// //     while (temp)
// //     {
// //         cmd_count++;
// //         temp = temp->next;
// //     }

// //     // Allocate array to store all PIDs
// //     pids = malloc(sizeof(pid_t) * cmd_count);
// //     if (!pids)
// //         return;

// //     int i = 0;
// //     while (clist)
// //     {
// //         // Create pipe only if there's a next command
// //         if (clist->next != NULL)
// //         {
// //             if (pipe(pipe_fd) == -1)
// //             {
// //                 perror("pipe");
// //                 break;
// //             }
// //         }

// //         pids[i] = fork();
// //         if (pids[i] == 0)
// //         {
// //             // Child process

// //             // Set up input redirection
// //             if (in_fd != 0)
// //             {
// //                 dup2(in_fd, STDIN_FILENO);
// //                 close(in_fd);
// //             }

// //             // Set up output redirection
// //             if (clist->next != NULL)
// //             {
// //                 close(pipe_fd[0]); // Close read end
// //                 dup2(pipe_fd[1], STDOUT_FILENO);
// //                 close(pipe_fd[1]); // Close write end
// //             }

// //             // Handle file redirections
// //             // setup_redirections(clist);

// //             // Execute builtin or external command
// //             if (is_builtin(clist))
// //                 exit(execute_builtin(clist, shell));

// //             cmd_path = find_path(clist->array[0], shell->env);
// //             if (!cmd_path)
// //             {
// //                 fprintf(stderr, "%s: command not found\n", clist->array[0]);
// //                 exit(127);
// //             }
// //             execve(cmd_path, clist->array, shell->env);
// //             perror("execve"); // This should never be reached
// //             exit(1);
// //         }
// //         else if (pids[i] < 0)
// //         {
// //             perror("fork");
// //             break;
// //         }
// //         else
// //         {
// //             // Parent process

// //             // Close the previous input fd if it exists
// //             if (in_fd != 0)
// //                 close(in_fd);

// //             // If we created a pipe, close write end and save read end for next iteration
// //             if (clist->next != NULL)
// //             {
// //                 close(pipe_fd[1]); // Close write end
// //                 in_fd = pipe_fd[0]; // Save read end for next command
// //             }
// //         }

// //         clist = clist->next;
// //         i++;
// //     }

// //     // Close the final input fd if it exists
// //     if (in_fd != 0)
// //         close(in_fd);

// //     // Wait for all child processes to complete
// //     for (int j = 0; j < i; j++)
// //     {
// //         if (pids[j] > 0)
// //             waitpid(pids[j], NULL, 0);
// //     }

// //     free(pids);
// // }


char **filter_empty_args(c_cmd *cmd)
{
    if (cmd->qflag == 0 || cmd->array == NULL)
        return cmd->array; // No quotes, return as is

    int count = 0;
    int i = 0;
    int j;
    while (cmd->array[i])
    {
        if (strlen(cmd->array[i]) > 0)
            count++;
        i++;
    }
    char **filtered = malloc(sizeof(char *) * (count + 1));
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

// char **generate_envp_from_envlist(t_shell *shell)
// {
//     int size = ft_lstsize(shell->envv);
//     char **envp = malloc(sizeof(char *) * (size + 1));
//     int i = 0;
//     t_list *node = shell->envv;

//     while (node)
//     {
//         envp[i++] = ft_strdup((char *)node->content);
//         node = node->next;
//     }
//     envp[i] = NULL;
//     return envp;
// }


void execute_cmds(c_cmd *clist, t_shell *shell)
{
    int in_fd = 0;
    int pipe_fd[2];
    pid_t pid;
    char *cmd_path;
    char **filtered_args;
    char **envp;

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
            if (clist->next != NULL)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            
            // setup_redirections(clist);
            if (is_builtin(clist))
                exit(execute_builtin(clist, shell));

            cmd_path = find_path(clist->array[0], generate_envp_from_envlist(shell));

            if (!cmd_path)
                printf("command not found\n");

            filtered_args = filter_empty_args(clist);
            envp = generate_envp_from_envlist(shell);

            execve(cmd_path, filtered_args, envp);

            if (filtered_args != clist->array)
                free(filtered_args);
            // free_2d(envp);
            exit(127);
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
