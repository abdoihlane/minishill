/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:38 by salhali           #+#    #+#             */
/*   Updated: 2025/07/22 14:42:14 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

 char *find_path(char *cmd, char **envp)
{
    if (access(cmd, X_OK) == 0)
        return ft_strdup(cmd); // full path already

    char *path = get_env_value(envp, "PATH");
    char **string = ft_split(path, ':');
    char *full_path;

    int i = 0;
    while (string[i])
    {
        char *tmp = ft_strjoin(string[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);

        if (access(full_path, X_OK) == 0)
        {
            ft_free_2d_array(string);
            return full_path;
        }
        free(full_path);
        i++;
    }
    ft_free_2d_array(string);
    return NULL;
}
