/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:24 by salhali           #+#    #+#             */
/*   Updated: 2025/07/14 16:36:29 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  setup_redirections(c_cmd *cmd)
{
    r_list *tmp = cmd->file;
    //  r_list *head = cmd->file;
    // while (head)
    // {
    //     printf("content: {%s}, cmd : {%s} inout: {%d}\n", head->content,cmd->array[1],  head->inout);
    //     head = head->next;
    // }
    while (tmp)
    {
        if (tmp->inout == 0)   // <  in = 0; Redirect stdin from a file
        {
            int fd = open(tmp->content, O_RDONLY);
            if (fd < 0)
            {
                perror("bash");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (tmp->inout == 1) // > out = 1;  Redirect stdout to a file (overwrite)
        {
            int fd = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                perror("open");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (tmp->inout == 3) // >> Redirect stdout to a file (append)
        {
            int fd = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
                perror("open");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (tmp->inout == 4) // << herdoc
        {
            heredoc_input(tmp->content, tmp);
            continue;
            // r_list *head = cmd->file;
            //     while (head)
            //     {
            //         printf("Redirection content: %s, inout: %d\n", head->content, head->inout);
            //         head = head->next;
            //     }
        }
        tmp = tmp->next;
    }
    // r_list *head = cmd->file;
    // while (head)
    // {
    //     printf("Redirection content: %s, inout: %d\n", head->content, head->inout);
    //     head = head->next;
    // }
}
