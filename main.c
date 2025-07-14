#include "mini.h"

void	call_all(char *in, w_list **wlist)
{
	pars_T *pars = init_pars(in); // to free
	fill_the_array(pars);
	CommandOrnot(pars, wlist);
}

int	main(void)
{
	char	*in;
	c_cmd	*clist;
	char	*history_in;

	clist = NULL;
	w_list *wlist = NULL;
	T_list *token = NULL; 
	pars_T *pars = NULL;  // to free
	while (1)
	{
		in = readline("\001\033[38;2;255;105;180m\002➜  minishell \001\033[0m\002");
		if (!in)
			return (0);
		else
		{
			if (in)
			{
				history_in = ft_strdup(in);
				add_history(history_in);
			}
			if (HardcodeChecks(in) == 0)
			{
				printf("syntax error\n");
				free(in);
				continue ;
			}
			call_all(in, &wlist);
			token = typesee(&wlist);
			splitit(token, &clist);
			free_Plist(&pars);
			free_wlist(&wlist);
			print_cmd_list(clist);
			wlist = NULL;
			free(pars);
			pars = NULL;
			free(in);
			rl_on_new_line();       // Regenerate the prompt on a newline
			rl_replace_line("", 0); // Clear the previous text
			// rl_redisplay();
		}
	}
	return (0);
}
