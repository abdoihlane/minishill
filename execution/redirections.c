/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:24 by salhali           #+#    #+#             */
/*   Updated: 2025/07/11 13:51:58 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  setup_redirections(c_cmd *cmd)
{
    r_list *tmp = cmd->file;

    while (tmp)
    {
        if (tmp->inout == 0)   // <  in = 1;
        {
            int fd = open(tmp->content, O_RDONLY);
            if (fd < 0)
                perror("open");
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (tmp->inout == 1) // > out = 0;
        {
            int fd = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                perror("open");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (tmp->inout == 3) // >>
        {
            int fd = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
                perror("open");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (tmp->inout == 4) // <<
        {
            // hna ghadi ndir `heredoc_input(tmp->content);`
            // o nfta7 `.heredoc_tmp`
        }
        tmp = tmp->next;
    }
}