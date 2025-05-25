/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/05/25 12:20:23 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
 {
     // INIT ENV
     (void)argc;
     (void)argv;

     t_shell shell;
     shell.env = envp;            // dir envp f shell
     shell.last_exit_status = 0;  // bda bi 0 exit status

     // TEST CMD: echo
     char *args_echo[] = {"echo", "Hello,", "World!", NULL};
     c_cmd *cmd_echo = create_test_cmd("echo", args_echo);

     // TEST CMD: pwd
     char *args_pwd[] = {"pwd", NULL};
     c_cmd *cmd_pwd = create_test_cmd("pwd", args_pwd);

     // TEST CMD: env
     char *args_env[] = {"env", NULL};
     c_cmd *cmd_env = create_test_cmd("env", args_env);

     // TEST CMD: cd
     char *args_cd[] = {"cd", "..", NULL};
     c_cmd *cmd_cd = create_test_cmd("cd", args_cd);

     // TEST CMD: exit
     char *args_exit[] = {"exit", NULL};
     c_cmd *cmd_exit = create_test_cmd("exit", args_exit);

     // TEST list
     c_cmd *test_cmds[] = {cmd_echo, cmd_pwd, cmd_env, cmd_cd, cmd_exit};
     int num_cmds = 5;

     // Loop for testing each builtin
     int  i = 0;
     while (i < num_cmds)
     {
        if (is_builtin(test_cmds[i]->cmd))
        {
             printf("Executing builtin: %s\n", test_cmds[i]->cmd);
             execute_builtin(test_cmds[i], &shell);
             printf("Exit status: %d\n\n", shell.last_exit_status);
        }
        else
        {
             printf("Not a builtin: %s\n\n", test_cmds[i]->cmd);
        }
        i++;
     }

     // Clean
    int i = 0;
    while (i < num_cmds)
         free_test_cmd(test_cmds[i++]);
    return 0;
 }
