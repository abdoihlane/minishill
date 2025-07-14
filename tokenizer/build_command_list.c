#include "../mini.h"

void	splitit(T_list *token, c_cmd **final)
{
	T_list	*tmp;
	int		array_size;
	c_cmd	*cmd_head;
	c_cmd	*current;
	int		word_count;
	c_cmd	*new_cmd;

	tmp = token;
	array_size = 0;
	cmd_head = NULL;
	current = NULL;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			array_size++;
		tmp = tmp->next;
	}
	array_size++;
	tmp = token;
	while (tmp)
	{
		word_count = count_cmd_args(tmp);
		new_cmd = create_new_cmd(word_count);
		if (!new_cmd)
			return ;
		if (!cmd_head)
			cmd_head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		while (tmp && tmp->type != TOKEN_PIPE)
		{
			if (tmp->type == TOKEN_REDIRECT_INPUT
				|| tmp->type == TOKEN_REDIRECT_OUTPUT
				|| tmp->type == TOKEN_HERDOC
				|| tmp->type == TOKEN_REDIRECT_OUTPUT_AM)
			{
				handle_redirection(current, tmp);
				tmp = tmp->next;
				if (tmp)
					tmp = tmp->next;
				continue ;
			}
			else if ((tmp->type == TOKEN_WORD) && tmp->value)
			{
				current->array[current->index] = strdup(tmp->value);
				current->index++;
			}
			else if (tmp->type == TOKEN_quotes)
			{
				current->qflag = 1;
				if (tmp->value && tmp->value[0] != '\0')
				{
					current->array[current->index] = strdup(tmp->value);
					current->index++;
				}
			}
			tmp = tmp->next;
		}
		current->array[current->index] = NULL;
		if (current->index > 0 && current->array[0]
			&& current->array[0][0] != '\0')
			current->cmd = ft_strdup(current->array[0]);
		else
			current->cmd = NULL;
		if (tmp && tmp->type == TOKEN_PIPE)
			tmp = tmp->next;
	}
	*final = cmd_head;
}
