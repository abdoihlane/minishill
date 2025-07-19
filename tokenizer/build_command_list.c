/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 04:33:06 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/19 11:57:14 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	is_red(t_token *tmp)
{
	if (tmp->type == TOKEN_REDIRECT_INPUT || tmp->type == TOKEN_REDIRECT_OUTPUT
		|| tmp->type == TOKEN_HERDOC || tmp->type == TOKEN_REDIRECT_OUTPUT_AM)
		return (1);
	return (0);
}

// void	splitit(t_token *token, t_cmd **final)
// {
// 	t_token	*tmp;
// 	t_cmd	*cmd_head;
// 	t_cmd	*current;
// 	int		word_count;
// 	t_cmd	*new_cmd;

// 	tmp = token;
// 	cmd_head = NULL;
// 	current = NULL;
// 	tmp = token;
// 	while (tmp)
// 	{
// 		word_count = count_cmd_args(tmp);
// 		new_cmd = create_new_cmd(word_count);
// 		if (!new_cmd)
// 			return ;
// 		if (!cmd_head)
// 			cmd_head = new_cmd;
// 		else
// 			current->next = new_cmd;
// 		current = new_cmd;
// 		while (tmp && tmp->type != TOKEN_PIPE)
// 		{
// 			if (is_red(tmp) == 1)
// 			{
// 				handle_redirection(current, tmp);
// 				tmp = tmp->next;
// 				if (tmp)
// 					tmp = tmp->next;
// 				continue ;
// 			}
// 			else if ((tmp->type == TOKEN_WORD) && tmp->value)
// 			{
// 				current->array[current->index] = strdup(tmp->value);
// 				current->index++;
// 			}
// 			else if (tmp->type == TOKEN_quotes)
// 			{
// 				current->qflag = 1;
// 				if (tmp->value && tmp->value[0] != '\0')
// 				{
// 					current->array[current->index] = strdup(tmp->value);
// 					current->index++;
// 				}
// 			}
// 			tmp = tmp->next;
// 		}
// 		current->array[current->index] = NULL;
// 		if (current->index > 0 && current->array[0]
// 			&& current->array[0][0] != '\0')
// 			current->cmd = ft_strdup(current->array[0]);
// 		else
// 			current->cmd = NULL;
// 		if (tmp && tmp->type == TOKEN_PIPE)
// 			tmp = tmp->next;
// 	}
// 	*final = cmd_head;
// }

void	splitit(t_token *token, t_cmd **final)
{
	t_token	*tmp;
	t_cmd	*cmd_head;
	t_cmd	*current;
	t_cmd	*new_cmd;
	int		word_count;

	tmp = token;
	cmd_head = NULL;
	current = NULL;
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
		tmp = fill_command_fields(tmp, current);
	}
	*final = cmd_head;
}

void handle_word_and_quotes(t_cmd *current, t_token *tmp)
{
    /* never write past the end */
    if (current->index >= current->capacity)
        return;

    if (tmp->type == TOKEN_WORD && tmp->value)
    {
        current->array[current->index++] = ft_strdup(tmp->value);
    }
    else if (tmp->type == TOKEN_quotes)
    {
        current->qflag = 1;
        if (tmp->value && tmp->value[0] != '\0'
            && current->index < current->capacity)
        {
            current->array[current->index++] = ft_strdup(tmp->value);
        }
    }
}



t_token	*fill_command_fields(t_token *tmp, t_cmd *current)
{
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_red(tmp))
		{
			handle_redirection(current, tmp);
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		handle_word_and_quotes(current, tmp);
	}
	current->array[current->index] = NULL;
	if (current->index > 0)
	{
		if (current->array[0] && current->array[0][0])
			current->cmd = ft_strdup(current->array[0]);
		else
			current->cmd = NULL;
	}
	else
		current->cmd = NULL;
	if (tmp && tmp->type == TOKEN_PIPE)
		tmp = tmp->next;
	return (tmp);
}
