#include "../mini.h"

char	*ft_strjoin_all(char **array)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	if (!array)
		return (NULL);
	result = ft_strdup("");
	while (array[i])
	{
		tmp = ft_strjoin(result, array[i]);
		free(result);
		result = tmp;
		i++;
		if (array[i])
		{
			tmp = ft_strjoin(result, " ");
			free(result);
			result = tmp;
		}
	}
	return (result);
}

int	is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

void	SkipWhiteSpaces(pars_T *pars)
{
	while (pars->content[pars->i] && is_whitespace(pars->content[pars->i]))
		pars->i++;
	pars->c = pars->content[pars->i];
}
