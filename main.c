/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/06/22 00:20:45 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	heredoc_input(char *delimiter)
// {
// 	char	*line = NULL;
// 	size_t	len = 0;
// 	int		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		perror("heredoc open");
// 		return;
// 	}

// 	while (1)
// 	{
// 		write(1, "> ", 2);
// 		ssize_t nread = getline(&line, &len, stdin);
// 		if (nread == -1)
// 			break;

// 		// delete newline for comparison
// 		if (line[nread - 1] == '\n')
// 			line[nread - 1] = '\0';

// 		if (strcmp(line, delimiter) == 0)
// 			break;

// 		write(fd, line, strlen(line));
// 		write(fd, "\n", 1);
// 	}
// 	free(line);
// 	close(fd);
// }

char *find_path(char *cmd, char **envp)
{
    if (access(cmd, X_OK) == 0)
        return strdup(cmd); // full path already

    char *path = get_env_value(envp, "PATH"); // khas tdirha nta
    char **dirs = ft_split(path, ':');
    char *full_path;

    for (int i = 0; dirs[i]; i++)
    {
        char *tmp = ft_strjoin(dirs[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);

        if (access(full_path, X_OK) == 0)
        {
            ft_free_2d_array(dirs);
            return full_path;
        }
        free(full_path);
    }
    ft_free_2d_array(dirs);
    return NULL;
}


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
        else if (tmp->inout == 4) // <<
        {
            // hna ghadi ndir `heredoc_input(tmp->content);`
            // o nfta7 `.heredoc_tmp`
        }
        tmp = tmp->next;
    }
}

void execute_cmds(c_cmd *clist, t_shell *shell)
{
    int in_fd = 0;
    int pipe_fd[2];
    pid_t pid;

    while (clist)
    {
        if (clist->next)
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
void	ft_free_2d_array(char **arr)
{
	int	i = 0;

	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
char *get_env_value(char **env, const char *key)
{
    size_t len = strlen(key);
    for (int i = 0; env[i]; i++)
    {
        if (strncmp(env[i], key, len) == 0 && env[i][len] == '=')
            return env[i] + len + 1;
    }
    return NULL;
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
    t_shell shell;

    shell.env = dup_envp(envp);
    shell.last_exit_status = 0;
    shell.envv = NULL;
    build_env_list(&shell);

    while (1)
    {
        input_user = readline("\001\033[38;2;255;105;180m\002➜  minishell \001\033[0m\002");
        if (!input_user)
            return 0;

        if (HardcodeChecks(input_user) == 0)
        {
            printf("syntax error\n");
            continue;
        }

        call_all(input_user, &wlist);
        token = typesee(&wlist);
        splitit(token, &clist);
        add_history(input_user);

        if (clist && is_builtin(clist) && clist->next == NULL)
            execute_builtin(clist, &shell);
        else
            execute_cmds(clist, &shell);

        free_wlist(&wlist);
        free_Plist(&pars);
        wlist = NULL;
        free(input_user);
        rl_on_new_line();
        rl_replace_line("", 0);
    }
    return 0;
}
