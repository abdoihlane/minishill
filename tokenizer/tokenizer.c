/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:42:20 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/19 11:48:38 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	typesee_plus(t_wlist *list, t_token *new_token)
{
	t_wlist	*begin;

	begin = list;
	if (!ft_strcmp("|", begin->content))
		new_token->type = TOKEN_PIPE;
	else if (!ft_strcmp("<", begin->content))
		new_token->type = TOKEN_REDIRECT_INPUT;
	else if (!ft_strcmp(">", begin->content))
		new_token->type = TOKEN_REDIRECT_OUTPUT;
	else if (!ft_strcmp("<<", begin->content))
		new_token->type = TOKEN_HERDOC;
	else if (!ft_strcmp(">>", begin->content))
		new_token->type = TOKEN_REDIRECT_OUTPUT_AM;
	else
		new_token->type = TOKEN_WORD;
}

t_token	*typesee(t_wlist **list)
{
	t_wlist	*begin;
	t_token	*tokens;
	t_token	*last;
	int		index;

	begin = *list;
	tokens = NULL;
	last = NULL;
	index = 0;
	while (begin)
	{
		if (!add_token_node(begin, &tokens, &last, &index))
			return (NULL);
		begin = begin->next;
	}
	return (tokens);
}

int	add_token_node(t_wlist *begin, t_token **tokens, t_token **last, int *index)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->value = ft_strdup(begin->content);
	if (!new_token->value)
	{
		free(new_token);
		return (0);
	}
	new_token->next = NULL;
	new_token->index = (*index)++;
	if (!ft_strcmp("", begin->content))
		new_token->type = TOKEN_quotes;
	else
		typesee_plus(begin, new_token);
	if (!*tokens)
		*tokens = new_token;
	else
		(*last)->next = new_token;
	*last = new_token;
	return (1);
}

int count_cmd_args(t_token *start)
{
    int count = 0;

    while (start && start->type != TOKEN_PIPE)
    {
        if (start->type == TOKEN_WORD
         || start->type == TOKEN_quotes)
        {
            count++;
        }
        else if (start->type == TOKEN_REDIRECT_INPUT
              || start->type == TOKEN_REDIRECT_OUTPUT
              || start->type == TOKEN_REDIRECT_OUTPUT_AM
              || start->type == TOKEN_HERDOC)
        {
            // skip the next token (the filename), but do NOT count it
            start = start->next;
        }
        // advance to next token
        if (start)
            start = start->next;
    }
    return (count);
}

void	commandornot(t_pars *pars, t_wlist **wlist)
{
	int	i;

	i = 0;
	while (pars->content1[i])
	{
		wlst_addback(wlist, wcreate_node(pars->content1[i]));
		i++;
	}
}
