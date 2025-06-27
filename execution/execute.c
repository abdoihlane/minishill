/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:16:53 by salhali           #+#    #+#             */
/*   Updated: 2025/06/27 17:17:25 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_cmds(c_cmd *clist, t_shell *shell)
{
    int in_fd = 0;
    int pipe_fd[2];
    pid_t pid;
    char *cmd_path;

    while (clist)
    {
        if (clist->next != NULL)
            pipe(pipe_fd);

        pid = fork();
        if (pid == 0)
        {
            setup_redirections(clist);
            if (is_builtin(clist))
                exit(execute_builtin(clist, shell));
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

            cmd_path = find_path(clist->array[0], shell->env);
            if (!cmd_path)
                printf("find_path failed !!!!\n");
            char **filtered_args = filter_empty_args(clist);
            execve(cmd_path, filtered_args, shell->env);
            
            if (filtered_args != clist->array)
                free(filtered_args);
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


// void execute_cmds(c_cmd *clist, t_shell *shell)
// {
//     int in_fd = 0;
//     int pipe_fd[2];
//     pid_t *pids;
//     char *cmd_path;
//     int cmd_count = 0;
//     c_cmd *temp = clist;
    
//     // Count the number of commands
//     while (temp)
//     {
//         cmd_count++;
//         temp = temp->next;
//     }
    
//     // Allocate array to store all PIDs
//     pids = malloc(sizeof(pid_t) * cmd_count);
//     if (!pids)
//         return;
    
//     int i = 0;
//     while (clist)
//     {
//         // Create pipe only if there's a next command
//         if (clist->next != NULL)
//         {
//             if (pipe(pipe_fd) == -1)
//             {
//                 perror("pipe");
//                 break;
//             }
//         }

//         pids[i] = fork();
//         if (pids[i] == 0)
//         {
//             // Child process
            
//             // Set up input redirection
//             if (in_fd != 0)
//             {
//                 dup2(in_fd, STDIN_FILENO);
//                 close(in_fd);
//             }
            
//             // Set up output redirection
//             if (clist->next != NULL)
//             {
//                 close(pipe_fd[0]); // Close read end
//                 dup2(pipe_fd[1], STDOUT_FILENO);
//                 close(pipe_fd[1]); // Close write end
//             }
            
//             // Handle file redirections
//             // setup_redirections(clist);
            
//             // Execute builtin or external command
//             if (is_builtin(clist))
//                 exit(execute_builtin(clist, shell));

//             cmd_path = find_path(clist->array[0], shell->env);
//             if (!cmd_path)
//             {
//                 fprintf(stderr, "%s: command not found\n", clist->array[0]);
//                 exit(127);
//             }
//             execve(cmd_path, clist->array, shell->env);
//             perror("execve"); // This should never be reached
//             exit(1);
//         }
//         else if (pids[i] < 0)
//         {
//             perror("fork");
//             break;
//         }
//         else
//         {
//             // Parent process
            
//             // Close the previous input fd if it exists
//             if (in_fd != 0)
//                 close(in_fd);
            
//             // If we created a pipe, close write end and save read end for next iteration
//             if (clist->next != NULL)
//             {
//                 close(pipe_fd[1]); // Close write end
//                 in_fd = pipe_fd[0]; // Save read end for next command
//             }
//         }
        
//         clist = clist->next;
//         i++;
//     }
    
//     // Close the final input fd if it exists
//     if (in_fd != 0)
//         close(in_fd);
    
//     // Wait for all child processes to complete
//     for (int j = 0; j < i; j++)
//     {
//         if (pids[j] > 0)
//             waitpid(pids[j], NULL, 0);
//     }
    
//     free(pids);
// }


// Add this function to your code
char **filter_empty_args(c_cmd *cmd)
{
    if (!cmd->qflag || !cmd->array)
        return cmd->array; // No quotes, return as is
    
    // Count non-empty arguments
    int count = 0;
    int i = 0;
    while (cmd->array[i])
    {
        if (strlen(cmd->array[i]) > 0)
            count++;
        i++;
    }
    
    // Create new array without empty strings
    char **filtered = malloc(sizeof(char *) * (count + 1));
    if (!filtered)
        return cmd->array;
    
    int j = 0;
    i = 0;
    while (cmd->array[i])
    {
        if (strlen(cmd->array[i]) > 0)
        {
            filtered[j] = cmd->array[i];
            j++;
        }
        i++;
    }
    filtered[j] = NULL;
    
    return filtered;
}

// Modify your execute_cmds function - add this before execve:
// void execute_cmds(c_cmd *clist, t_shell *shell)
// {
//     // ... your existing code ...
    
//     if (pid == 0)
//     {
//         // ... your existing setup code ...
        
//         if (is_builtin(clist))
//             exit(execute_builtin(clist, shell));

//         cmd_path = find_path(clist->array[0], shell->env);
//         if (!cmd_path)
//         {
//             fprintf(stderr, "%s: command not found\n", clist->array[0]);
//             exit(127);
//         }
        
//         // FILTER EMPTY ARGS HERE:
//         char **filtered_args = filter_empty_args(clist);
//         execve(cmd_path, filtered_args, shell->env);
        
//         // Free filtered array if it's different from original
//         if (filtered_args != clist->array)
//             free(filtered_args);
//     }
    
//     // ... rest of your code ...
// }