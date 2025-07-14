#include "../mini.h"

void	fill_array_plus(pars_T *pars)
{
	if (pars->content[pars->i] == pars->content[pars->i + 1]
		&& (pars->content[pars->i] == '<' || pars->content[pars->i] == '>'))
	{
		pars->content1[pars->k++] = ft_substr(pars->content, pars->i, 2);
		pars->i += 2;
		if (pars->i == '<')
			pars->herdoc_flag = 1;
	}
	else
	{
		pars->content1[pars->k++] = ft_substr(pars->content, pars->i, 1);
		pars->i++;
	}
}

void	fill_the_array(pars_T *pars)
{
	pars->i = 0;
	pars->k = 0;
	pars->NumDollar = 0;
	pars->expand_flag = 0;
	pars->herdoc_flag = 0;
	int dflag = 0;

	while (pars->content[pars->i])
	{
		if (pars->content[pars->i] == '$')
			pars->NumDollar++;
		pars->i++;
	}
	pars->i = 0;

	while (pars->content[pars->i])
	{
		SkipWhiteSpaces(pars);
		if (pars->content[pars->i] == '\0')
			break ;

		char *token = ft_strdup("");
		while (pars->content[pars->i] && !is_whitespace(pars->content[pars->i])
			&& !is_redirection(pars->content[pars->i]))
		{
			char *part = NULL;

			if (pars->content[pars->i] == '\''
				|| pars->content[pars->i] == '\"')
			{
				part = Handlequotes(pars, pars->content[pars->i]);
				dflag = 1;
			}
			else
			{
				int start = pars->i;
				while (pars->content[pars->i]
					&& !is_whitespace(pars->content[pars->i])
					&& !is_redirection(pars->content[pars->i])
					&& pars->content[pars->i] != '\''
					&& pars->content[pars->i] != '\"')
				{
					pars->i++;
				}
				int len = pars->i - start;
				part = ft_substr(pars->content, start, len);
				int z = 0;
				while (pars->NumDollar > z)
				{
					char *expanded = expand_variables(part);
					pars->expand_flag = 1;
					free(part);
					part = expanded;
					z++;
				}
			}
			if (token[0] != '\0')
				pars->content1[pars->k++] = ft_strdup(token);
			// free(token);

			char *tmp = ft_strjoin(token, part);
			free(token);
			free(part);
			token = tmp;
		}

		if (token[0])
			pars->content1[pars->k++] = ft_strdup(token);
		else
			pars->content1[pars->k++] = ft_strdup("");
		free(token);
		if (is_redirection(pars->content[pars->i]))
		{
			fill_array_plus(pars);
		}
	}
	pars->content1[pars->k] = NULL;
	if (pars->expand_flag && dflag == 0)
	{
		char *new_input = ft_strjoin_all(pars->content1);
		// free(pars->content);
		pars->content = ft_strdup(new_input);
		free(new_input);
		for (unsigned int j = 0; j < pars->lenOFarray + pars->nbOfPipes; j++)
			free(pars->content1[j]);
		free(pars->content1);

		pars->content1 = malloc(sizeof(char *) * (pars->lenOFarray
					+ pars->nbOfPipes + 1));

		fill_the_array(pars);
		return ;
	}
}
