/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:04:06 by salhali           #+#    #+#             */
/*   Updated: 2025/05/26 15:27:17 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void handle_redirection(c_cmd *list, T_list *token)
{
	if (!list->file)
	{
		list->file = malloc(sizeof(T_list));
		list->file->content = NULL;
	}
	if(token->next)
		list->file->content = token->next->value;
	if (token->type == TOKEN_REDIRECT_INPUT)
		list->file->inout = 1;
	else if(token->type == TOKEN_REDIRECT_OUTPUT)
		list->file->inout = 0;	
	else if(token->type == TOKEN_REDIRECT_OUTPUT_AM )
		list->file->inout = 3;
	else if(token->type == TOKEN_HERDOC )
		list->file->inout = 4;
}

c_cmd *create_new_cmd(int array_size)
{
    c_cmd *cmd = malloc(sizeof(c_cmd));
    if (!cmd)
        return NULL;

    cmd->array = malloc(sizeof(char *) * (array_size + 1));
    if (!cmd->array)
    {
        free(cmd);
        return NULL;
    }

    cmd->index = 0;
    cmd->file = NULL;
	cmd->cmd = NULL;
    cmd->next = NULL;
    return cmd;
}

int count_cmd_args(T_list *start)
{
	int count = 0;
	while (start && start->type != TOKEN_PIPE)
	{
		if (start->type == TOKEN_WORD)
			count++;
		else if (start->type == TOKEN_REDIRECT_INPUT || start->type == TOKEN_REDIRECT_OUTPUT || start->type == TOKEN_REDIRECT_OUTPUT_AM  || start->type == TOKEN_HERDOC  )	
		{
			count++;
			start = start->next;
		}
		if(start && start->next)
			start = start->next;
		else
			return count;
	}
		return count;

}

void splitit(T_list *token, c_cmd **final)
{
	
	T_list *tmp = token;
	int array_size = 0;
    c_cmd *cmd_head = NULL;
    c_cmd *current = NULL;
	// c_cmd *new_cmd = create_new_cmd(array_size);
	// if (!new_cmd)	
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
		int word_count = count_cmd_args(tmp);
		c_cmd *new_cmd = create_new_cmd(word_count);
		if (!new_cmd)
			return;
		
        // c_cmd *new_cmd = malloc(sizeof(c_cmd));
		// new_cmd->array = malloc(sizeof(char *) * (word_count + 1));
        // if (!new_cmd)
        //     return;
        // // new_cmd->array =malloc(sizeof(char *) * (array_size + 1));
        // if (!new_cmd->array)
        //     return;
        // new_cmd->index = 0;
        // new_cmd->file = NULL;
        // new_cmd->next = NULL;

        if (!cmd_head)
            cmd_head = new_cmd;
        else
            current->next = new_cmd;
			
			current = new_cmd;
			while (tmp && tmp->type != TOKEN_PIPE)
			{
				if (tmp->type == TOKEN_REDIRECT_INPUT || tmp->type == TOKEN_REDIRECT_OUTPUT || tmp->type == TOKEN_HERDOC ||tmp->type == TOKEN_REDIRECT_OUTPUT_AM  )
				{
					handle_redirection(current, tmp);
					tmp = tmp->next;
					continue;
				}
				if (tmp->value)
				{
					current->array[current->index] = strdup(tmp->value);
					current->index++;
				}
				tmp = tmp->next;
			}
			current->array[current->index] = NULL;
			if (tmp && tmp->type == TOKEN_PIPE)
            	tmp = tmp->next;
			if(current->array[0])
				current->cmd = ft_strdup(current->array[0]);
    }

    *final = cmd_head;
	// free(cmd_head);
	// free(current);
	// free(tmp);
}

void CommandOrnot(pars_T *pars, w_list **wlist)
{
	int i = 0;
	while (pars->content1[i])
	{
		wlst_addback(wlist, wcreate_node(pars->content1[i]));
		i++;
	}
}

T_list *typesee(w_list **list)
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
            return NULL;
        new_token->value = (begin->content);
        new_token->next = NULL;
        new_token->index = index++;
		if(!ft_strcmp(begin->content, ""))
			new_token->type = TOKEN_WORD;
        else if (!ft_strcmp(begin->content, "|"))
            new_token->type = TOKEN_PIPE;
        else if (!ft_strcmp(begin->content, "<"))
            new_token->type = TOKEN_REDIRECT_INPUT;
        else if (!ft_strcmp(begin->content, ">"))
            new_token->type = TOKEN_REDIRECT_OUTPUT;
        else if (!ft_strcmp(begin->content, "<<"))
            new_token->type = TOKEN_HERDOC;
        else if (!ft_strcmp(begin->content, ">>"))
            new_token->type = TOKEN_REDIRECT_OUTPUT_AM;
		else
            new_token->type = TOKEN_WORD;

        if (!tokens)
            tokens = new_token;
        else
            last->next = new_token;

        last = new_token;
        begin = begin->next;
    }
    return tokens;
}

char *expand_variables(char *input)
{
    if (!input || !ft_strchr(input, '$'))
        return ft_strdup(input);

    char *pos = ft_strchr(input, '$');
    if (!pos)
        return ft_strdup(input);

    char *key = pos + 1;
    if (*key == '\0')
        return ft_strdup(input);

    int i = 0;
    while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
        i++;

    char *varname = ft_substr(key, 0, i);
    char *env = getenv(varname);

    char *prefix = ft_substr(input, 0, pos - input);
    char *suffix = ft_strdup(pos + 1 + i);

    char *tmp1 = ft_strjoin(prefix, env ? env : "");
    char *result = ft_strjoin(tmp1, suffix);

    free(varname);
    free(prefix);
    free(suffix);
    free(tmp1);

    return result;
}


int contains_single_quotes(const char *s)
{
	while (*s)
	{
		if (*s == '\'')
			return 1;
		s++;
	}
	return 0;
}
char *Handlequotes(pars_T *pars, char c)
{
	pars->i++; 

	if (pars->content[pars->i] && pars->content[pars->i] == c)
	{
		pars->i++; 
		return ft_strdup(""); 
	}

	int start = pars->i;
	while (pars->content[pars->i] && pars->content[pars->i] != c)
		pars->i++;

	int len = pars->i - start;
	char *segment = malloc(len + 1);
	if (!segment)
		return NULL;

	for (int j = 0; j < len; j++)
		segment[j] = pars->content[start + j];
	segment[len] = '\0';

	pars->i++; 

	if (c == '"') 
	{
		int z = 0;
		char *expanded = NULL;
		while(z <= pars->NumDollar)
		{
			expanded = expand_variables(segment);
			free(segment);
			segment = expanded;
			z++;
///////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
//////////////////LEAKS I GUESS/////////////////////
////////////////////////////////////////////////////
/////////////////free(expanded);////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
		}
		// free(expanded);
	}
	return segment; 

}



int is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

void SkipWhiteSpaces(pars_T *pars)
{
	while (pars->content[pars->i] && is_whitespace(pars->content[pars->i]))
		pars->i++;
	pars->c = pars->content[pars->i];
}
int is_redirection(char c)
{
	return (c == '<' || c == '>' || c == '|' );
}

pars_T *init_pars(char *in)
{
	pars_T *pars = malloc(sizeof(pars_T));
	pars->i = 0;
	pars->k = 0;
	pars->lenOFarray = 0;
	pars->nbOfPipes = 0;
	pars->content = in;


	while(pars->content[pars->i])
	{
		if(pars->content[pars->i] == '<' || pars->content[pars->i] == '>' || pars->content[pars->i] == '|')
			{
				if(pars->i != 0 &&!is_whitespace(pars->content[pars->i -1]) && !is_whitespace(pars->content[pars->i +1]))
					pars->nbOfPipes +=2;
				else 
					pars->nbOfPipes+=1;
			}
		pars->i++;
	}
	pars->i = 0;
	while (pars->content[pars->i])
	{
		SkipWhiteSpaces(pars);
		if (pars->content[pars->i] == '\0')
			break;
		while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
			{
				pars->i++;
			}
		pars->lenOFarray++;
		}
	pars->content1 = malloc(sizeof(char *) * (pars->lenOFarray + pars->nbOfPipes + 1));
	return pars;
}

void fill_the_array(pars_T *pars)
{
	pars->i = 0;
	pars->k = 0;
	pars->NumDollar = 0;

	while(pars->content[pars->i])
	{
		if(pars->content[pars->i] == '$')
			pars->NumDollar++;
		pars->i++;
	}
	pars->i = 0;
	while (pars->content[pars->i])
	{
		SkipWhiteSpaces(pars);
		if (pars->content[pars->i] == '\0')
			break;

		char *token = ft_strdup("");

		while (pars->content[pars->i] &&
			   !is_whitespace(pars->content[pars->i]) &&
			   !is_redirection(pars->content[pars->i]))
		{
			char *part = NULL;

			if (pars->content[pars->i] == '\'' || pars->content[pars->i] == '\"')
			{
				part = Handlequotes(pars, pars->content[pars->i]);
			}
			else
			{
				int start = pars->i;
				while (pars->content[pars->i] &&
					   !is_whitespace(pars->content[pars->i]) &&
					   !is_redirection(pars->content[pars->i]) &&
					   pars->content[pars->i] != '\'' &&
					   pars->content[pars->i] != '\"')
				{
					pars->i++;
				}
				int len = pars->i - start;
				part = ft_substr(pars->content, start, len);
				int z = 0;
				while(pars->NumDollar > z)
				{
					char *expanded = expand_variables(part);
					free(part);
					part = expanded;
					z++;
				}
			}

			char *tmp = ft_strjoin(token, part);
			free(token);
			free(part);
			token = tmp;
			// free(tmp);
		}
		if (token[0]) 
			pars->content1[pars->k++] = token;
		else
			free(token);
		// free(token);
		if (is_redirection(pars->content[pars->i]))
		{
			if (pars->content[pars->i] == pars->content[pars->i + 1] &&
				(pars->content[pars->i] == '<' || pars->content[pars->i] == '>'))
			{
				pars->content1[pars->k++] = ft_substr(pars->content, pars->i, 2);
				pars->i += 2;
			}
			else
			{
				pars->content1[pars->k++] = ft_substr(pars->content, pars->i, 1);
				pars->i++;
			}
		}
	}
	
	// free(token);

	pars->content1[pars->k] = NULL;
}



void print_list(T_list *list)
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

void print_cmd_list(c_cmd *cmd)
{
	if (!cmd)
	{
		printf("Command list is NULL\n");
		return;
	}

	int cmd_num = 0;
	printf("=== Command List ===\n");
	int i = 1;
	while (cmd)
	{
		printf("-------comand : %s\n",cmd->cmd);
		// printf("--- arg #[ %d ]---\n", cmd_num);
		while(cmd->array[i])
		{
			printf("-------arg[%d]: %s\n", i, cmd->array[i]);
			i++;
		}
		i = 0;
		if (cmd->file)
		{
			printf("-------Redirection file: %s\n", cmd->file->content);
			if(cmd->file->inout == 1 || cmd->file->inout == 0)
				printf("-------Redirection type: %s\n\n", cmd->file->inout ? "INPUT" : "OUTPUT");
			else if(cmd->file->inout == 3 || cmd->file->inout == 4)
			{
				if(cmd->file->inout == 4)
					printf("-------Redirection type: %s\n\n","  HERDOC");
				if(cmd->file->inout == 3)
					printf("-------Redirection type: %s\n\n"," OUTPUT IN APPEND MODE");
			}
		}
		else
		{
			printf("No redirection file.\n\n");
		}

		cmd = cmd->next;
		cmd_num++;
	}
}


void print_list1(w_list *list)
{
	int i = 1;
	while (list)
	{
		printf("word %d: %s\n", i++, list->content);
		list = list->next;
	}
}

void free_wlist(w_list **list)
{
	w_list *temp = NULL;
	w_list *temp2 = NULL;
	temp = *list;
	if(temp)
	{
		while (temp->next)
		{
			temp2 = temp->next;
			if(temp)
				free(temp);
			temp = temp2;
		}
	}
}

void free_Plist(pars_T **list)
{
	pars_T *temp = NULL;
	temp = *list;
	int i = 0;
	if(temp)
	{
		if(temp->content1[i])
		{
			while(temp->content1[i])
			{
				free(temp->content1[i]);
				i++;
			}
			if(temp->content)
				free(temp->content);
		}
	}
}

int check_quotes_closed(char *str)
{
    int i = 0;
    int in_single = 0;
    int in_double = 0;

    while (str[i])
    {
        if (str[i] == '\'' && in_double == 0)
            in_single = !in_single;
        else if (str[i] == '\"' && in_single == 0)
            in_double = !in_double;
        i++;
    }
    return (in_single || in_double);
}


int HardcodeChecks(char *str)
{
	if(!str)
		return 0;
	int i = ft_strlen(str);
	int dquote = check_quotes_closed(str);
	if(dquote == 1)
		return 0;
	while(str && i && str[i] <= 32)
		i--;
	if(str[0] == '|'  || str[i] == '|')
		return 0;
	i = 0;
	while(str[i])
	{
		if(str[i] == '|')
			{
				if(str[i+1] == '|')
					return 0;
			}
		i++;
	}
	i = 0;
	while(str[i])
	{
		if(str[i] ==  '<' && str[i+1] == '<' && str[i+2] == '<')
			return 0;
		if((str[i] ==  '>' )&& (str[i+1] == '>') && (str[i+2] == '>'))
			return 0;
		i++;
	}
	return 1;
}

void call_all(char *in, w_list **wlist)
{
	pars_T *pars = init_pars(in);// to free
	fill_the_array(pars);
	CommandOrnot(pars,wlist);
	free(pars);
}



