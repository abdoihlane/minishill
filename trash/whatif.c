#include "mini.h"

void handle_redirection(c_cmd *list, T_list *token)
{
	if (!list->file)
	{
		list->file = malloc(sizeof(T_list));
		if (!list->file)
			return;
		list->file->content = NULL;
	}
	list->file->content = token->value;
	list->file->inout = (token->type == TOKEN_REDIRECT_INPUT);
}

// void splitit(T_list *token, c_cmd **final)
// {
// 	*final = malloc(sizeof(c_cmd));
// 	if (!(*final))
// 		return;

// 	(*final)->array = malloc(sizeof(char *) * (token->index + 1));
// 	(*final)->file = NULL;
// 	(*final)->index = 0;

// 	while (token)
// 	{
// 		(*final)->array[(*final)->index] = ft_strdup("");

// 		while (token && token->type != TOKEN_PIPE)
// 		{
// 			if (token->type == TOKEN_REDIRECT_INPUT || token->type == TOKEN_REDIRECT_OUTPUT)
// 			{
// 				handle_redirection(*final, token);
// 				token = token->next;
// 				continue;
// 			}

// 			char *tmp = (*final)->array[(*final)->index];
// 			(*final)->array[(*final)->index] = ft_strjoin(tmp, token->value);
// 			free(tmp);
// 			token = token->next;
// 		}
// 		(*final)->index++;
// 		if (token)
// 			token = token->next;
// 	}
// }
void splitit(T_list *token, c_cmd **final)
{
	int array_size = 0;
	T_list *tmp = token;

	// Count how many command arrays we will need
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			array_size++;
		tmp = tmp->next;
	}
	array_size++; // For the last command

	*final = malloc(sizeof(c_cmd));
	if (!*final)
		return;

	(*final)->array = malloc(sizeof(char *) * (array_size + 1));
	if (!(*final)->array)
		return;

	(*final)->file = NULL;
	(*final)->index = 0;

	while (token)
	{
		(*final)->array[(*final)->index] = ft_strdup("");

		while (token && token->type != TOKEN_PIPE)
		{
			if (token->type == TOKEN_REDIRECT_INPUT || token->type == TOKEN_REDIRECT_OUTPUT)
			{
				handle_redirection(*final, token);
				token = token->next;
				continue;
			}

			char *tmp_str = (*final)->array[(*final)->index];
			(*final)->array[(*final)->index] = ft_strjoin(tmp_str, token->value);
			free(tmp_str);
			token = token->next;
		}

		(*final)->index++;

		if (token && token->type == TOKEN_PIPE)
			token = token->next;
	}

	(*final)->array[(*final)->index] = NULL;
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
	T_list *tokens = NULL, *last = NULL, *new_token;
	int index = 0;

	while (begin)
	{
		new_token = malloc(sizeof(T_list));
		if (!new_token)
			return NULL;

		new_token->value = begin->content;
		new_token->next = NULL;
		new_token->index = index++;

		if (!ft_strcmp(begin->content, ""))
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

void expand_variables(T_list *tokens)
{
    while (tokens)
    {
        if (tokens->type == TOKEN_WORD && ft_strchr(tokens->value, '$'))
        {
            char *pos = ft_strchr(tokens->value, '$');
            char *key = pos + 1;

            if (*key == '\0')
            {
                tokens = tokens->next;
                continue;
            }

            int i = 0;
            while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
                i++;

            char *varname = ft_substr(key, 0, i);
            char *env = getenv(varname);
            if (env)
            {
                int prefix_len = pos - tokens->value;
                char *prefix = ft_substr(tokens->value, 0, prefix_len);
                char *suffix = ft_strdup(pos + 1 + i);

                char *tmp1 = ft_strjoin(prefix, env);
                char *newval = ft_strjoin(tmp1, suffix);

				if (tokens->value)
					free(tokens->value);
				tokens->value = newval;

				if(prefix)
                	free(prefix);
                if(suffix)
					free(suffix);
				if(tmp1)
                	free(tmp1);
            }

			else
			{
				int prefix_len = pos - tokens->value;
                char *prefix = ft_substr(tokens->value, 0, prefix_len);
                char *suffix = ft_strdup(pos + 1 + i);

                char *tmp1 = ft_strjoin(prefix, ft_strdup(""));
                char *newval = ft_strjoin(tmp1, suffix);
				if(tokens->value)
					free(tokens->value);
				tokens->value = newval;
			}

            free(varname);
        }

        tokens = tokens->next;
    }
}
// void expand_variables(T_list *tokens)
// {
// 	while (tokens)
// 	{
// 		if (tokens->type == TOKEN_WORD && ft_strchr(tokens->value, '$'))
// 		{
// 			char *pos = ft_strchr(tokens->value, '$');
// 			char *key = pos + 1;

// 			if (*key == '\0')
// 			{
// 				tokens = tokens->next;
// 				continue;
// 			}

// 			int i = 0;
// 			while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
// 				i++;

// 			char *varname = ft_substr(key, 0, i);
// 			char *env = getenv(varname);

// 			int prefix_len = pos - tokens->value;
// 			char *prefix = ft_substr(tokens->value, 0, prefix_len);
// 			char *suffix = ft_strdup(pos + 1 + i);
// 			char *tmp1 = ft_strjoin(prefix, env ? env : "");
// 			char *newval = ft_strjoin(tmp1, suffix);

// 			free(tokens->value);
// 			tokens->value = newval;

// 			free(varname);
// 			free(prefix);
// 			free(suffix);
// 			free(tmp1);
// 		}
// 		tokens = tokens->next;
// 	}
// }

void Handlequotes(pars_T *pars, char c)
{
	pars->i++;
	int start = pars->i;
	while (pars->content[pars->i] && pars->content[pars->i] != c)
		pars->i++;

	int len = pars->i - start;
	pars->content1[pars->k] = malloc(len + 1);
	if (!pars->content1[pars->k])
		return;
    int j = 0;
    while(j < len)
    {
		pars->content1[pars->k][j] = pars->content[start + j];
        j++;
    }
    pars->content1[pars->k][len] = '\0';

	if (pars->k < pars->lenOFarray)
		pars->k++;

	if (pars->content[pars->i] == c)
		pars->i++;
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
	pars->i = pars->k = pars->nbOfPipes = 0;
	pars->content = in;

	while (pars->content[pars->i])
	{
		SkipWhiteSpaces(pars);
		if (!pars->content[pars->i])
			break;
		while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
			pars->i++;
		pars->lenOFarray++;
	}

	pars->content1 = malloc(sizeof(char *) * (pars->lenOFarray + 2));
	return pars;
}

void fill_the_array(pars_T *pars)
{
    int j = 0;
	pars->i = 0; 
    pars->k = 0;
	while (pars->content[pars->i] && pars->k < pars->lenOFarray)
	{
		SkipWhiteSpaces(pars);
		if (!pars->content[pars->i])
			break;

		if (pars->content[pars->i] == '\'' || pars->content[pars->i] == '\"')
		{
			Handlequotes(pars, pars->content[pars->i]);
			continue;
		}
		int start = pars->i;
		while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
			pars->i++;

		int len = pars->i - start;
		pars->content1[pars->k] = malloc(len + 1);
        while(j < len)
        {
            pars->content1[pars->k][j] = pars->content[start + j];
            j++;
        }
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
        else if (list->type == TOKEN_REDIREC_OUTPUT_AM)
            printf("type: REDIRECT_OUTPUT_APPEND\n");
		list = list->next;
	}
} 

void free_wlist(w_list **list)
{
	w_list *temp = *list;
	while (temp)
	{
		w_list *next = temp->next;
		free(temp);
		temp = next;
	}
	*list = NULL;
}

int count_wanted_char(char *str, char c)
{
	int count = 0;
	for (int i = 0; str[i]; i++)
		if (str[i] == c)
			count++;
	return count;
}

int HardcodeChecks(char *str)
{
	if (!str)
		return 0;
	int len = ft_strlen(str);
	int dq = count_wanted_char(str, '\"');
	int sq = count_wanted_char(str, '\'');
	if (dq % 2 || sq % 2)
		return 0;

	int i = len - 1;
	while (i >= 0 && str[i] <= 32)
		i--;
	if (str[0] == '|' || str[i] == '|')
		return 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return 0;
		if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<') ||
			(str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
			return 0;
	}
	return 1;
}

void call_all(char *in, w_list **wlist)
{
	pars_T *pars = init_pars(in);
	fill_the_array(pars);
	CommandOrnot(pars, wlist);
	free(pars);
}

int main()
{
	char *in;
	c_cmd *clist = NULL;
	w_list *wlist = NULL;
	T_list *token = NULL;

	while (1)
	{
		in = readline("➜  mini_with_salah ");
		if (!in)
			break;

		if (!HardcodeChecks(in))
		{
			printf("syntax error\n");
			free(in);
			continue;
		}
		call_all(in, &wlist);
		token = typesee(&wlist);
        expand_variables(token);
		splitit(token, &clist);
		add_history(in);
		print_list(token);
		free_wlist(&wlist);
		free(in);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return 0;
}
