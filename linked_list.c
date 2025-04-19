#include "mini.h"

c_list	*ccreate_node(char *value)
{
	c_list	*new_node;

	new_node = malloc(sizeof(c_list));
	if (!new_node)
		return (NULL);
	new_node->content = value;
	new_node->next = NULL;
	return (new_node);
}

w_list	*wcreate_node(char *value)
{
	w_list	*new_node;

	new_node = malloc(sizeof(w_list));
	if (!new_node)
		return (NULL);
	new_node->content = value;
	new_node->next = NULL;
	return (new_node);
}

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while(s1[i])
	{
		if(s1[i] != s2[i])
			return 1;
		i++;
	}
	return 0;
}
void	clst_addback(c_list **lst, c_list *node)
{
	c_list	*tmp;

	if (!node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = node;
}

void	wlst_addback(w_list **lst, w_list *node)
{
	w_list	*tmp;

	if (!node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = node;
}