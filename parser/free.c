#include "../mini.h"

void	free_wlist(w_list **list)
{
	w_list	*temp;
	w_list	*temp2;

	temp = NULL;
	temp2 = NULL;
	temp = *list;
	if (temp)
	{
		while (temp->next)
		{
			temp2 = temp->next;
			if (temp)
				free(temp);
			temp = temp2;
		}
	}
}
void	free_Plist(pars_T **list)
{
	pars_T	*temp;

	if (!list || !*list)
		return ;
	temp = *list;
	if (temp->content1)
	{
		for (int i = 0; temp->content1[i]; i++)
			free(temp->content1[i]);
		free(temp->content1);
	}
	if (temp->content)
		free(temp->content);
	free(temp);
	*list = NULL;
}
