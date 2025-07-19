#include "../mini.h"

void	print_cmd_list(t_cmd *cmd)
{
	int	i;

	if (!cmd)
	{
		printf("Command list is NULL\n");
		return ;
	}
	printf("=== Command List ===\n");
	while (cmd)
	{
		if (cmd->qflag == 1)
			printf("\nthere is quotes\n\n");
		printf("-------command : %s\n", cmd->cmd);
		i = 1;
		while (cmd->array[i])
		{
			printf("-------arg[%d]: %s\n", i, cmd->array[i]);
			i++;
		}
		if (cmd->file)
		{
			printf("-------Redirection file: %s\n", cmd->file->content);
			if (cmd->file->inout == 1 || cmd->file->inout == 0)
				printf("-------Redirection type: %s\n\n",
					cmd->file->inout ? "INPUT" : "OUTPUT");
			else if (cmd->file->inout == 3 || cmd->file->inout == 4)
			{
				if (cmd->file->inout == 4)
					printf("-------Redirection type: %s\n\n", "HERDOC");
				if (cmd->file->inout == 3)
					printf("-------Redirection type: %s\n\n",
						"OUTPUT IN APPEND MODE");
			}
		}
		else
		{
			printf("No redirection file.\n\n");
		}
		cmd = cmd->next;
	}
}
void	print_token(t_token *list)
{
	while (list)
	{
		printf("token : %s     ", list->value);
		if (list->type == TOKEN_PIPE)
			printf("type: PIPE\n");
		else if (list->type == TOKEN_WORD)
			printf("type: WORD\n");
		else if (list->type == TOKEN_REDIRECT_INPUT)
			printf("type: REDIRECT_INPUT\n");
		else if (list->type == TOKEN_REDIRECT_OUTPUT)
			printf("type: REDIRECT_OUTPUT\n");
		else if (list->type == TOKEN_HERDOC)
			printf("type: HERDOC\n");
		else if (list->type == TOKEN_REDIRECT_OUTPUT_AM)
			printf("type: REDIRECT_OUTPUT_APPEND\n");
		list = list->next;
	}
}