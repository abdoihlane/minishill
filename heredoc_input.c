#include "minishell.h"

void	write_heredoc_line(int fd, char *line)
{
	char	*expanded;

	expanded = expand_variables(line);
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
}

void	heredoc_input(char *delimiter, r_list *head)
{
	char	*line;
	size_t	len;
	ssize_t	nread;
	int		fd;

	line = NULL;
	len = 0;
	signal(SIGINT, sigint_heredoc);
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc open");
		return ;
	}
	while (1)
	{
		write(1, "> ", 2);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break ;
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		write_heredoc_line(fd, line);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	head->content = ft_strdup(".heredoc_tmp");
	head->inout = 0;
	if (line)
		free(line);
	close(fd);
}
