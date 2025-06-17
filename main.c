/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/06/16 09:36:10 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        else if (tmp->inout == 3) // <<
        {
            // handle heredoc (b chi function heredoc_input())
        }
        tmp = tmp->next;
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
            c_cmd     *tmp = clist;
            // pid_t   pid;
            while(tmp)
            {
                if (is_builtin(tmp) && !tmp->next) // wa7da o builtin?
                        execute_builtin(tmp, &shell);
                //  else
                //  {
                //       pid = fork();
                //       if (pid == 0) // CHILD PROCESS
                //       {
                //            // handle infile & outfile redirections
                //            if (tmp->infile != -1)
                //                 dup2(tmp->infile, STDIN_FILENO);
                //            if (tmp->outfile != -1)
                //                 dup2(tmp->outfile, STDOUT_FILENO);

                //         //    // pipes (ila kayn pipe bin had cmd w li b3d)
                //         //    if (has_pipe_to_next(tmp))
                //         //         dup2(pipe_fd[1], STDOUT_FILENO); // output ymsi l next cmd

                //         //    // check if builtin
                //         //    if (is_builtin(tmp))
                //         //         execute_builtin(tmp, &shell);
                //         //    else
                //         //         execve(tmp->path, tmp->args, shell->envp);

                //            exit(1); // important, child ykhrj
                //       }
                //       else if (pid < 0)
                //            perror("fork");
                //       // else parent may close pipe_fd[1] o ykhdem wait later
                //  }
                    tmp = tmp->next;
            }
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

