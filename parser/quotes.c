/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:49:57 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/19 11:39:13 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*expand_in_quotes(t_pars *pars, char *segment)
{
	int		z;
	char	*new_segment;
	char	*tmp;

	z = 0;
	new_segment = segment;
	while (z < pars->numdollar)
	{
		tmp = expand_variables(new_segment);
		free(new_segment);
		new_segment = tmp;
		pars->expand_flag = 1;
		z++;
	}
	return (new_segment);
}

char	*handlequotes(t_pars *pars, char c)
{
	int		start;
	int		len;
	char	*segment;
	int		j;

	pars->i++;
	if (pars->content[pars->i] && pars->content[pars->i] == c)
		return ((pars->i++), ft_strdup(""));
	start = pars->i;
	while (pars->content[pars->i] && pars->content[pars->i] != c)
		pars->i++;
	len = pars->i - start;
	segment = malloc(len + 2);
	if (!segment)
		return (NULL);
	j = -1;
	while (++j < len)
		segment[j] = pars->content[start + j];
	segment[len] = '\0';
	pars->i++;
	if (c == '"')
		segment = expand_in_quotes(pars, segment);
	return (segment);
}

int	check_quotes_closed(char *str)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
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
