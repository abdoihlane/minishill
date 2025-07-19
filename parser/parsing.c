/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:06 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/19 02:59:14 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	hardcodechecks(char *str)
{
	int	i;
	int	dquote;
	int	red;

	if (!str)
		return (0);
	i = 0;
	dquote = check_quotes_closed(str);
	if (dquote == 1)
		return (0);
	red = red_check(str);
	if (red == 0 || str[0] == '>')
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

int	red_check(char *str)
{
	int	i;

	i = 0;
	while (str && i && str[i] <= 32)
		i--;
	if (str[0] == '|' || str[i] == '|')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (0);
		if (str[i] == '<' && str[i + 1] == '>')
			return (0);
		if (str[i] == '>' && str[i + 1] == '<')
			return (0);
		if ((str[i] == '>') && (str[i + 1] == '>') && (str[i + 2] == '>'))
			return (0);
		i++;
	}
	return (1);
}
