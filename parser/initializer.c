/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:22 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/19 11:39:49 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_pars	*init_pars(char *in)
{
	t_pars	*pars;

	pars = malloc(sizeof(t_pars));
	pars->i = 0;
	pars->k = 0;
	pars->lenofarray = 0;
	pars->nbofpipes = 0;
	pars->content = ft_strdup(in);
	while (pars->content[pars->i])
	{
		skipwhitespaces(pars);
		if (pars->content[pars->i] == '\0')
			break ;
		while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
			pars->i++;
		pars->lenofarray++;
	}
	pars->content1 = malloc(sizeof(char *) * (pars->lenofarray + pars->nbofpipes
				+ 1));
	return (pars);
}

void	count_pipes(t_pars *pars)
{
	int	i;

	i = 0;
	while (pars->content[pars->i])
	{
		if (pars->content[pars->i] == '<' || pars->content[pars->i] == '>'
			|| pars->content[pars->i] == '|')
		{
			if (pars->i != 0 && !is_whitespace(pars->content[pars->i - 1])
				&& !is_whitespace(pars->content[pars->i + 1]))
				pars->nbofpipes += 2;
			else
				pars->nbofpipes += 1;
		}
		pars->i++;
	}
}
