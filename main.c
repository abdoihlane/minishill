/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 04:46:55 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/20 23:09:30 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	call_all(char *in, t_wlist **wlist)
{
	t_token	*token;
	t_pars	*pars;
	char	*history_in;
	t_cmd	*clist;

	if (hardcodechecks(in) == 0)
	{
		printf("syntax error\n");
		return ;
	}
	if (in)
	{
		history_in = ft_strdup(in);
		add_history(history_in);
	}
	clist = NULL;
	pars = init_pars(in);
	fill_the_array(pars);
	commandornot(pars, wlist);
	token = typesee(wlist);
	splitit(token, &clist);
	free_plist(&pars);
}

int	main(void)
{
	char	*in;
	t_wlist	*wlist;
	t_pars	*pars;

	wlist = NULL;
	pars = NULL;
	while (1)
	{
		in = readline(COLOR_PINK
				"➜ minishell" COLOR_RESET);
		if (!in)
			return (0);
		else
		{
			call_all(in, &wlist);
			wlist = NULL;
			pars = NULL;
			free(in);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
	}
	return (0);
}
