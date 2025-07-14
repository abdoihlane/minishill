#include "../mini.h"

int	is_redirection(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

void	handle_redirection(c_cmd *list, T_list *token)
{
	if (!list->file)
	{
		list->file = malloc(sizeof(T_list));
		list->file->content = NULL;
	}
	if (token->next)
		list->file->content = token->next->value;
	if (token->type == TOKEN_REDIRECT_OUTPUT)
		list->file->inout = 0;
	else if (token->type == TOKEN_REDIRECT_INPUT)
		list->file->inout = 1;
	else
		handle_red_plus(list, token);
}

void	handle_red_plus(c_cmd *list, T_list *token)
{
	if (token->type == TOKEN_REDIRECT_OUTPUT_AM)
		list->file->inout = 3;
	else if (token->type == TOKEN_HERDOC)
		list->file->inout = 4;
}