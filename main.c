/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/05/25 21:39:47 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int argc, char **argv, char **envp)
//  {
//      // INIT ENV
//      t_shell shell;
//      (void)argc;
//      (void)argv;
//      // int  i;
     
//      shell.env = envp;            // dir envp f shell
//      shell.last_exit_status = 0;  // bda bi 0 exit status

//      // i = 0;
//      // while (shell.env && ft_strnstr(shell.env[i], "PATH", 4) == 0)
// 	// 	i++;
//      // printf("env -->  : %s\n", shell.env[i]);

//      // TEST CMD: echo
//      char *args_echo[] = {"echo", "Hello,", "World!", NULL};
//      c_cmd *cmd_echo = create_test_cmd("echo", args_echo);

//      // TEST CMD: pwd
//      char *args_pwd[] = {"pwd", NULL};
//      c_cmd *cmd_pwd = create_test_cmd("pwd", args_pwd);

//      // TEST CMD: env
//      char *args_env[] = {"env", NULL};
//      c_cmd *cmd_env = create_test_cmd("env", args_env);

//      // TEST CMD: cd
//      char *args_cd[] = {"cd", "..", NULL};
//      c_cmd *cmd_cd = create_test_cmd("cd", args_cd);

//      // TEST CMD: exit
//      char *args_exit[] = {"exit", NULL};
//      c_cmd *cmd_exit = create_test_cmd("exit", args_exit);

//      // TEST list
//      c_cmd *test_cmds[] = {cmd_echo, cmd_pwd, cmd_env, cmd_cd, cmd_exit};
//      int num_cmds = 5;

//      // Loop for testing each builtin
//      int  i = 0;
//      while (i < num_cmds)
//      {
//         if (is_builtin(test_cmds[i]->cmd))
//         {
//              printf("Executing builtin: %s\n", test_cmds[i]->cmd);
//              execute_builtin(test_cmds[i], &shell);
//              printf("Exit status: %d\n\n", shell.last_exit_status);
//         }
//         else
//         {
//              printf("Not a builtin: %s\n\n", test_cmds[i]->cmd);
//         }
//         i++;
//      }
//     i = 0;
//     while (i < num_cmds)
//          free(test_cmds[i++]);
//     return 0;
//  }


int main()
{
    char *input_user;
    
    c_cmd *clist = NULL;
    w_list *wlist = NULL;
    T_list *token = NULL;
    pars_T *pars = NULL;
    
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
               print_cmd_list(clist);

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

