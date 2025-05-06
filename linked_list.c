#include "mini.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
 
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}


size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	ft_memcpy(join + s1_len, s2, s2_len);
	join[s1_len + s2_len] = '\0';
	return (join);
}


r_list	*ccreate_node(char *value)
{
	r_list	*new_node;

	new_node = malloc(sizeof(r_list));
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

// void	clst_addback(c_list **lst, c_list *node)
// {
// 	c_list	*tmp;

// 	if (!node)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = node;
// 		return ;
// 	}
// 	tmp = *lst;
// 	while (tmp->next)
// 	{
// 		tmp = tmp->next;
// 	}
// 	tmp->next = node;
// }

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