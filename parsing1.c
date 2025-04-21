#include "mini.h"

void CommandOrnot(pars_T *pars, c_list **clist, w_list **wlist)
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

	if (!begin)
		return NULL;

	while (begin)
	{
		new_token = malloc(sizeof(T_list));
		if (!new_token)
			break;

		new_token->value = begin->content;
		new_token->next = NULL;

		if (!ft_strcmp(begin->content, "|"))
			new_token->type = TOKEN_PIPE;
		else if (!ft_strcmp(begin->content, "<"))
			new_token->type = TOKEN_REDIRECT_INPUT;
		else if (!ft_strcmp(begin->content, ">"))
			new_token->type = TOKEN_REDIRECT_OUTPUT;
		else if (!ft_strcmp(begin->content, "<<"))
			new_token->type = TOKEN_DELIMITER;
		else if (!ft_strcmp(begin->content, ">>"))
			new_token->type = TOKEN_REDIREC_OUTPUT_AM;
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

void checkClosedQuote(pars_T *pars, char c)
{
	pars->i++; // skip the opening quote
	int start = pars->i;

	while (pars->content[pars->i] && pars->content[pars->i] != c)
		pars->i++;

	int len = pars->i - start;
	pars->content1[pars->k] = malloc(len + 1);
	for (int j = 0; j < len; j++)
		pars->content1[pars->k][j] = pars->content[start + j];
	pars->content1[pars->k][len] = '\0';
	pars->k++;

	if (pars->content[pars->i] == c)
		pars->i++; // skip the closing quote
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

pars_T *init_pars(char *in)
{
	pars_T *pars = malloc(sizeof(pars_T));
	pars->i = 0;
	pars->k = 0;
	pars->nbOfPipes = 0;
	pars->content = in;

	int m = 0;
	while (pars->content[pars->i])
	{
		SkipWhiteSpaces(pars);
		if (pars->content[pars->i] == '\0')
			break;
		while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
			pars->i++;
		m++;
	}
	pars->content1 = malloc(sizeof(char *) * (m + 1));
	return pars;
}

void fill_the_array(pars_T *pars)
{
	pars->i = 0;
	pars->k = 0;

	while (pars->content[pars->i])
	{
		SkipWhiteSpaces(pars);
		if (pars->content[pars->i] == '\0')
			break;

		if (pars->content[pars->i] == '\'' || pars->content[pars->i] == '\"')
		{
			checkClosedQuote(pars, pars->content[pars->i]);
			continue;
		}

		int start = pars->i;
		while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
			pars->i++;

		int len = pars->i - start;
		pars->content1[pars->k] = malloc(len + 1);
		for (int j = 0; j < len; j++)
			pars->content1[pars->k][j] = pars->content[start + j];
		pars->content1[pars->k][len] = '\0';
		pars->k++;
	}
	pars->content1[pars->k] = NULL;
}

void print_list(T_list *list)
{
	while (list)
	{
		printf("token : %s     ", list->value);
		switch (list->type)
		{
			case TOKEN_PIPE: printf("type: PIPE\n"); break;
			case TOKEN_WORD: printf("type: WORD\n"); break;
			case TOKEN_REDIRECT_INPUT: printf("type: REDIRECT_INPUT\n"); break;
			case TOKEN_REDIRECT_OUTPUT: printf("type: REDIRECT_OUTPUT\n"); break;
			case TOKEN_DELIMITER: printf("type: DELIMITER\n"); break;
			case TOKEN_REDIREC_OUTPUT_AM: printf("type: REDIRECT_OUTPUT_APPEND\n"); break;
		}
		list = list->next;
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
	w_list *temp;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = temp;
	}
}

void free_clist(c_list **list)
{
	c_list *temp;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = temp;
	}
}

void call_all(char *in, c_list **clist, w_list **wlist)
{
	pars_T *pars = init_pars(in);
	fill_the_array(pars);
	CommandOrnot(pars, clist, wlist);
	free(pars);
}

int main()
{
    char *in;
    c_list *clist = NULL;
    w_list *wlist = NULL;
    T_list *token = NULL;

    while (1)
    {
        in = readline("➜  mini_with_salah ");
        if (!in)
            break;
        call_all(in, &clist, &wlist);
        token = typesee(&wlist);
        // print_list1(wlist);
        print_list(token);
        // free_clist(&clist);
        free_wlist(&wlist);
        free(in);
    }

    return 0;
}
