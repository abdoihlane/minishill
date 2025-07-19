/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:56 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/19 11:38:37 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	free_wlist(t_wlist **list)
{
	t_wlist	*curr;
	t_wlist	*next;

	if (!list || !*list)
		return ;
	curr = *list;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*list = NULL;
}

void	free_plist(t_pars **par)
{
	t_pars	*p;
	int		i;

	if (!par || !*par)
		return ;
	p = *par;
	if (p->content1)
	{
		i = 0;
		while (p->content1[i])
			free(p->content1[i++]);
		free(p->content1);
	}
	free(p);
	*par = NULL;
}
