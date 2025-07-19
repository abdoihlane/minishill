/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:46 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/19 11:38:37 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	skipwhitespaces(t_pars *pars)
{
	while (pars->content[pars->i] && is_whitespace(pars->content[pars->i]))
		pars->i++;
	pars->c = pars->content[pars->i];
}

int	is_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	check_spaces_and_red(t_pars *pars)
{
	if (pars->content[pars->i] && !is_whitespace(pars->content[pars->i])
		&& !is_redirection(pars->content[pars->i])
		&& pars->content[pars->i] != '\'' && pars->content[pars->i] != '\"')
		return (1);
	return (0);
}
