/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:24 by salhali           #+#    #+#             */
/*   Updated: 2025/07/12 17:40:02 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  setup_redirections(c_cmd *cmd)
{
    r_list *tmp = cmd->file;

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
            heredoc_input(tmp->content);
        tmp = tmp->next;
    }
}
