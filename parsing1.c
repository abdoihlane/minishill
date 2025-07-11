#include "mini.h"

char *ft_strjoin_all(char **array)
{
	int i = 0;
	if (!array)
		return NULL;
	char *result = ft_strdup("");
	while(array[i])
	{
		char *tmp = ft_strjoin(result, array[i]);
		free(result);
		result = tmp;
		i++;
		if(array[i])
		{
			tmp = ft_strjoin(result, " ");
			free(result);
			result = tmp;
		}
	}
	return result;
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

void typesee_plus(w_list *list,T_list *new_token )
{
	w_list *begin = list;
	    if (!ft_strcmp("|",begin->content))
            new_token->type = TOKEN_PIPE;
        else if (!ft_strcmp("<" ,begin->content))
            new_token->type = TOKEN_REDIRECT_INPUT;
        else if (!ft_strcmp(">",begin->content))
            new_token->type = TOKEN_REDIRECT_OUTPUT;
        else if (!ft_strcmp("<<",begin->content))
            new_token->type = TOKEN_HERDOC;
        else if (!ft_strcmp(">>",begin->content))
            new_token->type = TOKEN_REDIRECT_OUTPUT_AM;
		else
            new_token->type = TOKEN_WORD;
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
		if(!ft_strcmp("",begin->content))
			new_token->type = TOKEN_quotes;
		else
			typesee_plus(begin,new_token);
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

char *expand_in_quotes(pars_T *pars, char *segment)
{
	int z = 0;
	char *new_segment = segment;

	while (z < pars->NumDollar)
	{
		char *tmp = expand_variables(new_segment);
		free(new_segment);
		new_segment = tmp;
		pars->expand_flag = 1;
		z++;
	}
	return new_segment;
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
	char *segment = malloc(len + 2);
	if (!segment)
		return NULL;
	int j = 0;
	while (j < len)
	{
		segment[j] = pars->content[start + j];
		j++;
	}

	segment[len] = '\0';
	pars->i++; 
	if (c == '"')
		{
			segment = expand_in_quotes(pars,segment);
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
				pars->i++;
		pars->lenOFarray++;
		}
	pars->content1 = malloc(sizeof(char *) * (pars->lenOFarray + pars->nbOfPipes + 1));
	return pars;
}

void fill_array_plus(pars_T *pars)
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

void fill_the_array(pars_T *pars)
{
    pars->i = 0;
    pars->k = 0;
    pars->NumDollar = 0;
	pars->expand_flag = 0;

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
                part = Handlequotes(pars, pars->content[pars->i]);
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
					pars->expand_flag = 1;
                    free(part);
                    part = expanded;
                    z++;
                }
            }
			if (token[0] != '\0')
				pars->content1[pars->k++] = ft_strdup(token);
			// free(token);

            char *tmp = ft_strjoin(token, part);
            free(token);
            free(part);
            token = tmp;
        }
        
        if (token[0]) 
            pars->content1[pars->k++] = ft_strdup(token);
        else
            pars->content1[pars->k++] = ft_strdup("");
        free(token);
        if (is_redirection(pars->content[pars->i]))
			fill_array_plus(pars);
    }
    pars->content1[pars->k] = NULL;
	printf("------------------------ %d\n",pars->expand_flag);
	if (pars->expand_flag)
		{
			char *new_input = ft_strjoin_all(pars->content1);
			// free(pars->content);
			pars->content = ft_strdup(new_input);
			free(new_input);
			for (int j = 0; j < pars->lenOFarray + pars->nbOfPipes; j++)
				free(pars->content1[j]);
			free(pars->content1);

			pars->content1 = malloc(sizeof(char *) * (pars->lenOFarray + pars->nbOfPipes + 1));

			fill_the_array(pars);
			return;
		}
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
	if (!list || !*list)
		return;
	pars_T *temp = *list;

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

int red_check(char *str)
{
	int i = 0;
	while(str && i && str[i] <= 32)
		i--;
	if(str[0] == '|'  || str[i] == '|')
		return 0;
	i = 0;
	while(str[i])
	{
		if(str[i] ==  '<' && str[i+1] == '<' && str[i+2] == '<')
			return 0;
		if(str[i] ==  '<' && str[i+1] == '>')
			return 0;
		if(str[i] ==  '>' && str[i+1] == '<')
			return 0;					
		if((str[i] ==  '>' )&& (str[i+1] == '>') && (str[i+2] == '>'))
			return 0;
		i++;
	}
	return 1;
}

int HardcodeChecks(char *str)
{
	if(!str)
		return 0;
	int i =0;
	int dquote = check_quotes_closed(str);
	if(dquote == 1)
		return 0;
	int red = red_check(str);
	if(red == 0)
		return 0;
	while(str[i])
	{
		if(str[i] == '|')
			{
				if(str[i+1] == '|')
					return 0;
			}
		i++;
	}
	if(str[0] == '>' ||str[0] == '<')
		return 0;
	i = 0;
	return 1;
}

void call_all(char *in, w_list **wlist)
{
	pars_T *pars = init_pars(in);// to free
	fill_the_array(pars);

	CommandOrnot(pars,wlist);
	// free(pars);
}



void handle_red_plus(c_cmd *list, T_list *token)
{
	if(token->type == TOKEN_REDIRECT_OUTPUT_AM )
		list->file->inout = 3;	
	else if(token->type == TOKEN_HERDOC )
		list->file->inout = 4;
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
	if(token->type == TOKEN_REDIRECT_OUTPUT)
		list->file->inout = 0;
	else if (token->type == TOKEN_REDIRECT_INPUT)
		list->file->inout = 1;
	else 
		handle_red_plus(list,token);
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
	cmd->qflag = 0;
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
        if (start->type == TOKEN_WORD || start->type == TOKEN_quotes)
            count++;
        else if (start->type == TOKEN_REDIRECT_INPUT || start->type == TOKEN_REDIRECT_OUTPUT || 
                 start->type == TOKEN_REDIRECT_OUTPUT_AM || start->type == TOKEN_HERDOC)    
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

        if (!cmd_head)
            cmd_head = new_cmd;
        else
            current->next = new_cmd;

        current = new_cmd;
        while (tmp && tmp->type != TOKEN_PIPE)
        {
            if (tmp->type == TOKEN_REDIRECT_INPUT || tmp->type == TOKEN_REDIRECT_OUTPUT || 
                tmp->type == TOKEN_HERDOC || tmp->type == TOKEN_REDIRECT_OUTPUT_AM)
            {
                handle_redirection(current, tmp);
                tmp = tmp->next;
                continue;
            }
			else if (tmp->type == TOKEN_WORD && tmp->value)
			{
				current->array[current->index] = strdup(tmp->value);
				current->index++;
			}
			else if(tmp->type == TOKEN_quotes)
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

        if (current->index > 0 && current->array[0] && current->array[0][0] != '\0')
            current->cmd = ft_strdup(current->array[0]);
        else
            current->cmd = NULL;

        if (tmp && tmp->type == TOKEN_PIPE)
            tmp = tmp->next;
    }
    *final = cmd_head;
}

void print_cmd_list(c_cmd *cmd)
{
	if (!cmd)
	{
		printf("Command list is NULL\n");
		return;
	}

	printf("=== Command List ===\n");
	while (cmd)
	{
		if(cmd->qflag == 1)
		 	printf("\nthere is quotes\n\n");
		printf("-------command : %s\n", cmd->cmd);
		
		int i = 1;
		while(cmd->array[i])
		{
			printf("-------arg[%d]: %s\n", i, cmd->array[i]);
			i++;
		}
		
		if (cmd->file)
		{
			printf("-------Redirection file: %s\n", cmd->file->content);
			if(cmd->file->inout == 1 || cmd->file->inout == 0)
				printf("-------Redirection type: %s\n\n", cmd->file->inout ? "INPUT" : "OUTPUT");
			else if(cmd->file->inout == 3 || cmd->file->inout == 4)
			{
				if(cmd->file->inout == 4)
					printf("-------Redirection type: %s\n\n", "HERDOC");
				if(cmd->file->inout == 3)
					printf("-------Redirection type: %s\n\n", "OUTPUT IN APPEND MODE");
			}
		}
		else
		{
			printf("No redirection file.\n\n");
		}

		cmd = cmd->next;
	}
}


int main()
{
    char *in;
    c_cmd *clist = NULL;
    w_list *wlist = NULL; // to free
    T_list *token = NULL; // to free
    pars_T *pars = NULL; // to free

    while (1)
    {
		in = readline("\001\033[38;2;255;105;180m\002➜  minishell \001\033[0m\002");
        if (!in)
            return 0;
		else
		{
			if(in)
			{
				char *history_in = ft_strdup(in);
				add_history(history_in);
			}
		if(HardcodeChecks(in) == 0)
			{
				printf("syntax error\n");
				free(in);
				continue;
			}
		call_all(in,&wlist);
		token = typesee(&wlist);
		splitit(token,&clist);
		// add_history(in);
        // print_list(token);
		free_Plist(&pars);
		free_wlist(&wlist);
		print_cmd_list(clist);
		// c_cmd *cmd = clist;
		wlist = NULL;
		free(pars);
		pars = NULL;
        free(in);
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		// rl_redisplay();
		}
    }
    return 0;
}