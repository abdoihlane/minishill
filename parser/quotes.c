#include "../mini.h"

int	contains_single_quotes(const char *s)
{
	while (*s)
	{
		if (*s == '\'')
			return (1);
		s++;
	}
	return (0);
}

char	*expand_in_quotes(pars_T *pars, char *segment)
{
	int		z;
	char	*new_segment;
	char	*tmp;

	z = 0;
	new_segment = segment;
	while (z < pars->NumDollar)
	{
		tmp = expand_variables(new_segment);
		free(new_segment);
		new_segment = tmp;
		pars->expand_flag = 1;
		z++;
	}
	return (new_segment);
}

char	*Handlequotes(pars_T *pars, char c)
{
	int		start;
	int		len;
	char	*segment;
	int		j;

	pars->i++;
	if (pars->content[pars->i] && pars->content[pars->i] == c)
	{
		pars->i++;
		return (ft_strdup(""));
	}
	start = pars->i;
	while (pars->content[pars->i] && pars->content[pars->i] != c)
		pars->i++;
	len = pars->i - start;
	segment = malloc(len + 2);
	if (!segment)
		return (NULL);
	j = 0;
	while (j < len)
	{
		segment[j] = pars->content[start + j];
		j++;
	}
	segment[len] = '\0';
	pars->i++;
	if (c == '"')
		segment = expand_in_quotes(pars, segment);
	return (segment);
}

int	check_quotes_closed(char *str)
{
	int i = 0;
	int in_single = 0;
	int in_double = 0;

	while (str[i])
	{
		if (str[i] == '\'' && in_double == 0)
			in_single = !in_single;
		else if (str[i] == '\"' && in_single == 0)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}