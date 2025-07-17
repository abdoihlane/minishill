#include "../mini.h"

pars_T	*init_pars(char *in)
{
	pars_T *pars = malloc(sizeof(pars_T));
	pars->i = 0;
	pars->k = 0;
	pars->lenOFarray = 0;
	pars->nbOfPipes = 0;
	pars->content = in;

	while (pars->content[pars->i])
	{
		if (pars->content[pars->i] == '<' || pars->content[pars->i] == '>'
			|| pars->content[pars->i] == '|')
		{
			if (pars->i != 0 && !is_whitespace(pars->content[pars->i - 1])
				&& !is_whitespace(pars->content[pars->i + 1]))
				pars->nbOfPipes += 2;
			else
				pars->nbOfPipes += 1;
		}
		pars->i++;
	}
	pars->i = 0;
	while (pars->content[pars->i])
	{
		SkipWhiteSpaces(pars);
		if (pars->content[pars->i] == '\0')
			break ;
		while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
			pars->i++;
		pars->lenOFarray++;
	}
	pars->content1 = malloc(sizeof(char *) * (pars->lenOFarray + pars->nbOfPipes
				+ 1));
	return (pars);
}