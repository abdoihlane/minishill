#include "../mini.h"

void	typesee_plus(w_list *list, T_list *new_token)
{
	w_list	*begin;

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

T_list	*typesee(w_list **list)
{
	w_list *begin = *list;
	T_list *tokens = NULL;
	T_list *last = NULL;
	T_list *new_token;
	int index = 0;
	while (begin)
	{
		new_token = malloc(sizeof(T_list));
		if (!new_token)
			return (NULL);
		new_token->value = (begin->content);
		new_token->next = NULL;
		new_token->index = index++;
		if (!ft_strcmp("", begin->content))
			new_token->type = TOKEN_quotes;
		else
			typesee_plus(begin, new_token);
		if (!tokens)
			tokens = new_token;
		else
			last->next = new_token;
		last = new_token;
		begin = begin->next;
	}
	return (tokens);
}