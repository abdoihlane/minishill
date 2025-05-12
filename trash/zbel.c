
// int len_counter(char *str)
// {
//     int i = 0;
//     while(str[i])
//         i++;
//     return i;
// }

// int words_counter(char **str)
// {
//     int i = 0;
//     while(str[i])
//         i++;
//     return i;
// }


// void allocForIt(pars_T *pars)
// {
//     pars->content1[pars->k] = malloc(sizeof(char) *(ft_strlen()));
// }


// void init_pars(char *in)
// {
//     pars_T *pars = malloc(sizeof(pars_T));
//     pars->i = 0;
//     pars->k = 0;
//     pars->content = in;
//     pars->c = pars->content[pars->i];
// }

if((ft_strcmp(pars->content1[i],"echo")) == 0)
{
    clst_addback(clist,ccreate_node(pars->content1[i]));
    i++;
}
else if(ft_strcmp(pars->content1[i],"cd") == 0)
{
    clst_addback(clist,ccreate_node(pars->content1[i]));
    i++;
}
else if(ft_strcmp(pars->content1[i],"pwd") == 0)
{
    clst_addback(clist,ccreate_node(pars->content1[i]));
    i++;
}
else if(ft_strcmp(pars->content1[i],"unset") == 0)
{
    clst_addback(clist,ccreate_node(pars->content1[i]));
    i++;
}
else if(ft_strcmp(pars->content1[i],"env") == 0)
{
    clst_addback(clist,ccreate_node(pars->content1[i]));
    i++;
}
else if(ft_strcmp(pars->content1[i],"exit") == 0)
{
    clst_addback(clist,ccreate_node(pars->content1[i]));
    i++;
}
else if(ft_strcmp(pars->content1[i],"export") == 0)
{
    clst_addback(clist,ccreate_node(pars->content1[i]));
    i++;
}



// void Comands(pars_T *pars)
// {
//     SkipWhiteSpaces(pars);
//     int z = 0;
    
//     while(pars->content[pars->i] && pars->content[pars->i] > 32)
//     {
//         pars->commands[pars->NbOfCommands][z] = pars->content[pars->i];
//         pars->i++;
//         z++;
//     }
//     pars->commands[pars->NbOfCommands][z] = '\0';
//     pars->NbOfCommands++;
// }







void splitit(T_list *token  ,c_cmd *final)
{
	int k = 0;
	final = malloc(sizeof(c_cmd));
	final->array = malloc(sizeof(char *)*(token->index +1));
	while(token)
	{
		final->array[k] = ft_strdup("");
		while(token->type != TOKEN_PIPE && token)
		{

			final->array[k] = ft_strjoin(final->array[k],token->value);
			token = token->next;
		}
			k++;
		if(token->next)
			token = token->next;
	}
}





void handle_redirection(c_cmd *list,T_list *token)
{
	int i= 0;
	list->file->content = token->value;
	if(token->type == TOKEN_REDIRECT_INPUT)
		list->file->inout = 1;
	else 
		list->file->inout = 0;
	// if(token->next)
		// token = token->next;
}

void splitit(T_list *token, c_cmd **final)
{
    int k = 0;
    
    *final = malloc(sizeof(c_cmd));  
    (*final)->array = malloc(sizeof(char *) * (token->index + 1));

    while (token)
	{
        (*final)->array[k] = ft_strdup("");  
        while (token->type != TOKEN_PIPE && token) 
		{
			if(token->type == TOKEN_REDIRECT_INPUT || token->type == TOKEN_REDIRECT_OUTPUT)
			{
				handle_redirection(final,token);
				token = token->next;
			}
				(*final)->array[k] = ft_strjoin((*final)->array[k], token->value);
            token = token->next;
        }
		k++;
        if (token && token->next) 
            token = token->next;
    }
}


// void expand_variables(T_list *tokens)
// {
//     while (tokens)
//     {
//         if (tokens->type == TOKEN_WORD && ft_strchr(tokens->value, '$'))
//         {
//             char *pos = ft_strchr(tokens->value, '$');
//             char *key = pos + 1;

//             if (*key == '\0')
//             {
//                 tokens = tokens->next;
//                 continue;
//             }

//             int i = 0;
//             while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
//                 i++;

//             char *varname = ft_substr(key, 0, i);
//             char *env = getenv(varname);
//             if (env)
//             {
//                 int prefix_len = pos - tokens->value;
//                 char *prefix = ft_substr(tokens->value, 0, prefix_len);
//                 char *suffix = ft_strdup(pos + 1 + i);

//                 char *tmp1 = ft_strjoin(prefix, env);
//                 char *newval = ft_strjoin(tmp1, suffix);

// 				if (tokens->value)
// 					free(tokens->value);
// 				tokens->value = newval;

// 				if(prefix)
//                 	free(prefix);
//                 if(suffix)
// 					free(suffix);
// 				if(tmp1)
//                 	free(tmp1);
//             }

// 			else
// 			{
// 				int prefix_len = pos - tokens->value;
//                 char *prefix = ft_substr(tokens->value, 0, prefix_len);
//                 char *suffix = ft_strdup(pos + 1 + i);

//                 char *tmp1 = ft_strjoin(prefix, ft_strdup(""));
//                 char *newval = ft_strjoin(tmp1, suffix);
// 				if(tokens->value)
// 					free(tokens->value);
// 				tokens->value = newval;
// 			}

//             free(varname);
// 			continue;
// 		}
//         tokens = tokens->next;
//     }
// }

















void fill_the_array(pars_T *pars)
{
	pars->i = 0;
	pars->k = 0;
	pars->index = 0;

	while (pars->content[pars->i] && pars->k < pars->lenOFarray)
	{
		SkipWhiteSpaces(pars);
		if (pars->content[pars->i] == '\0')
			break;
			
		if (pars->content[pars->i] == '\'' || pars->content[pars->i] == '\"')
		{
			Handlequotes(pars, pars->content[pars->i]);
			continue;
		}
		// if (pars->content[pars->i] == '<' || pars->content[pars->i] == '>' || pars->content[pars->i] == '|')
		// {
		// 	printf("sssssssssss");
		// 	if(pars->content[pars->i+1] == '<' && pars->content[pars->i] == '<' )
		// 		Handlered(pars, pars->content[pars->i],1);
		// 	else if(pars->content[pars->i] == '>' && pars->content[pars->i+1] == '>')
		// 		Handlered(pars, pars->content[pars->i],2);
		// 	else 
		// 		Handlered(pars, pars->content[pars->i],0);
		// 	continue;
		// }
		int start = pars->i;
		while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
			pars->i++;
		int len = pars->i - start;
		
		pars->content1[pars->k] = malloc((len + 1));
		// int j = 0;
		while(pars->index < len)
		{
			if (pars->content[start + pars->index] == '<' || pars->content[start + pars->index] == '>' || pars->content[start + pars->index] == '|')
			{
				// printf("sssssssssss");
				if(pars->content[start + pars->index] == '<' && pars->content[start + pars->index + 1] == '<' )
					Handlered(pars, pars->content[start + pars->index],1);
				else if(pars->content[start + pars->index] == '>' && pars->content[start + pars->index + 1] == '>')
					Handlered(pars, pars->content[start + pars->index],2);
				else 
					Handlered(pars, pars->content[start + pars->index],0);
				// continue;
			}
			pars->content1[pars->k][pars->index] = pars->content[start + pars->index];
			pars->index++;
		}
		pars->content1[pars->k][len] = '\0';
		char *expanded = expand_variables(pars->content1[pars->k]);
		free(pars->content1[pars->k]);
		pars->content1[pars->k] = expanded;
		pars->k++;
			
	}
	pars->content1[pars->k] = NULL;
}



// void fill_the_array(pars_T *pars)
// {
// 	pars->i = 0;
// 	pars->k = 0;
// 	pars->index = 0;

// 	while (pars->content[pars->i] && pars->k < pars->lenOFarray)
// 	{
// 		SkipWhiteSpaces(pars);
// 		if (pars->content[pars->i] == '\0')
// 			break;

// 		if (pars->content[pars->i] == '\'' || pars->content[pars->i] == '\"')
// 		{
// 			Handlequotes(pars, pars->content[pars->i]);
// 			continue;
// 		}

// 		if (is_redirection(pars->content[pars->i]))
// 		{
// 			if ((pars->content[pars->i] == '<' && pars->content[pars->i + 1] == '<') ||
// 				(pars->content[pars->i] == '>' && pars->content[pars->i + 1] == '>'))
// 			{
// 				pars->content1[pars->k++] = ft_substr(pars->content, pars->i, 2);
// 				pars->i += 2;
// 			}
// 			else
// 			{
// 				pars->content1[pars->k++] = ft_substr(pars->content, pars->i, 1);
// 				pars->i += 1;
// 			}
// 			continue;
// 		}

// 		int start = pars->i;
// 		while (pars->content[pars->i] &&
// 			   !is_whitespace(pars->content[pars->i]) &&
// 			   !is_redirection(pars->content[pars->i]) &&
// 			   pars->content[pars->i] != '\'' &&
// 			   pars->content[pars->i] != '\"')
// 		{
// 			pars->i++;
// 		}
		
// 		// Add word before redirection
// 		if (pars->i > start)
// 		{
// 			pars->content1[pars->k] = ft_substr(pars->content, start, pars->i - start);
// 			char *expanded = expand_variables(pars->content1[pars->k]);
// 			free(pars->content1[pars->k]);
// 			pars->content1[pars->k] = expanded;
// 			pars->k++;
// 		}
		
// 		// If the next char is a redirection, go back to main loop to handle it
		
// 		}
// 	pars->content1[pars->k] = NULL;
// }


// void Handlered(pars_T *pars, const char *token)
// {
// 	pars->content1[pars->k] = ft_strdup(token);
// 	if (!pars->content1[pars->k])
// 		exit(1);
// 	pars->k++;
// }

// void fill_the_array(pars_T *pars)
// {
// 	pars->i = 0;
// 	pars->k = 0;

// 	while (pars->content[pars->i] && pars->k < pars->lenOFarray)
// 	{
// 		SkipWhiteSpaces(pars);
// 		if (!pars->content[pars->i])
// 			break;

// 		// Check for redirection or pipe
// 		if (pars->content[pars->i] == '<' || pars->content[pars->i] == '>' || pars->content[pars->i] == '|')
// 		{
// 			if (pars->content[pars->i] == '<' && pars->content[pars->i + 1] == '<')
// 				Handlered(pars, "<<"), pars->i += 2;
// 			else if (pars->content[pars->i] == '>' && pars->content[pars->i + 1] == '>')
// 				Handlered(pars, ">>"), pars->i += 2;
// 			else
// 			{
// 				char tmp[2] = {pars->content[pars->i], '\0'};
// 				Handlered(pars, tmp);
// 				pars->i++;
// 			}
// 			continue;
// 		}

// 		// Handle word (stop when you find redirection or whitespace)
// 		int start = pars->i;
// 		while (pars->content[pars->i] &&
// 			   !is_whitespace(pars->content[pars->i]) &&
// 			   pars->content[pars->i] != '<' &&
// 			   pars->content[pars->i] != '>' &&
// 			   pars->content[pars->i] != '|')
// 		{
// 			pars->i++;
// 		}

// 		int len = pars->i - start;
// 		if (len <= 0)
// 			continue;

// 		pars->content1[pars->k] = malloc(len + 1);
// 		if (!pars->content1[pars->k])
// 			exit(1);
// 		strncpy(pars->content1[pars->k], &pars->content[start], len);
// 		pars->content1[pars->k][len] = '\0';

// 		// Expand variables if needed
// 		char *expanded = expand_variables(pars->content1[pars->k]);
// 		free(pars->content1[pars->k]);
// 		pars->content1[pars->k] = expanded;

// 		pars->k++;
// 	}

// 	pars->content1[pars->k] = NULL;
// }



// int searchForIt(char *str, int z)
// {
// 	int i = 0;
// 	while(str[z])
// 	{

// 	}
// }

// int count_wanted_char(char *str)
// {
// 	int i = 0;
// 	int z = 1;
// 	int k = 1;
// 	while(str[i])
// 	{
// 		if(str[i] == '\"')
// 		{
// 			while(str[i] && str[i] != '\"')
// 				i++;
// 			if(str[i] != '\"')
// 				return 1;
// 			printf("%c\n",str[i]);
// 		}
// 		if(str[i] == '\'')
// 		{
// 			while(str[i] && str[i] != '\'')
// 				i++;
// 			if(str[i] != '\'')
// 				return 1;
// 			printf("123");
// 		}
// 		if(str[i+1])
// 			i++;
// 		else 
// 			break;
// 	}
// 	return 0;
// }




// void fill_the_array(pars_T *pars)
// {
// 	pars->i = 0;
// 	pars->k = 0;
// 	pars->index = 0;

// 	while (pars->content[pars->i] && pars->k < pars->lenOFarray)
// 	{
// 		SkipWhiteSpaces(pars);
// 		if (pars->content[pars->i] == '\0')
// 			break;
			
// 		if (pars->content[pars->i] == '\'' || pars->content[pars->i] == '\"')
// 		{
// 			Handlequotes(pars, pars->content[pars->i]);
// 			continue;
// 		}
// 		// if (pars->content[pars->i] == '<' || pars->content[pars->i] == '>' || pars->content[pars->i] == '|')
// 		// {
// 		// 	printf("sssss|sssss\n");
// 		// 	if(pars->content[pars->i+1] == '<' && pars->content[pars->i] == '<' )
// 		// 		Handlered(pars, pars->content[pars->i],1);
// 		// 	else if(pars->content[pars->i] == '>' && pars->content[pars->i+1] == '>')
// 		// 		Handlered(pars, pars->content[pars->i],2);
// 		// 	else 
// 		// 		Handlered(pars, pars->content[pars->i],0);
// 		// 	// continue;
// 		// }
// 		int start = pars->i;
// 		while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
// 			pars->i++;
// 		int len = pars->i - start;
		
// 		pars->content1[pars->k] = malloc((len + 1));
// 		int j = 0;
// 		while(j < len)
// 		{
// 			if (pars->content[start + j] == '<' || pars->content[start + j] == '>' || pars->content[start + j] == '|')
// 			{
// 				if(pars->content[start + j] == '<')
// 				{
// 					// pars->k++;
					
// 					pars->content1[pars->k] = ft_strdup("<");
// 					pars->k++;
// 					printf("-----------%d--------------------\n",pars->k);
// 				}
// 				// if(pars->content[start + j] == '<' && pars->content[start + j + 1] == '<' )
// 				// {
// 					// pars->content1[pars->k][j] = '\0';
// 					// pars->k++;
// 					// Handlered(pars, pars->content[start + j],1);
// 				// else if(pars->content[start + j] == '>' && pars->content[start + j + 1] == '>')
// 				// {
// 				// 	// pars->content1[pars->k][j] = '\0';
// 				// 	// pars->k++;
// 				// 	Handlered(pars, pars->content[start + j],1);
// 				// }
// 				// // Handlered(pars, pars->content[start + j],2);
// 				// 	else 
// 				// 	{
// 				// 		// pars->content1[pars->k][j] = '\0';
// 				// 		// pars->k++;
// 				// 		Handlered(pars, pars->content[start + j],1);
// 				// 	}
// 				// 	// Handlered(pars, pars->content[start + j],0);
// 				// pars->content1[pars->k][j] = '\0';
// 				// printf("sssssssssss\n");
// 				// printf("%c\n",pars->content[start + j]);
				
// 			}
// 			else
// 				pars->content1[pars->k][j] = pars->content[start + j];
// 			// pars->content1[pars->k][j] = pars->content[start + j];
// 			j++;
// 		}
// 		pars->content1[pars->k][len] = '\0';
// 		char *expanded = expand_variables(pars->content1[pars->k]);
// 		free(pars->content1[pars->k]);
// 		pars->content1[pars->k] = expanded;
// 		pars->k++;
	
// 	}
// 	printf("-----------%d--------------------\n",pars->k);
// 	pars->content1[pars->k] = NULL;
// }




void Handlered(pars_T *pars, char c, int flag)
{
	if(pars->content[pars->i] && flag == 1)
	{

		pars->content1[pars->k] = ft_strdup("<<");
		pars->i +=2;
		pars->k++;
		return;
	}
	else if(pars->content[pars->i] && flag == 2)
	{
		pars->content1[pars->k] = ft_strdup(">>");
		pars->i +=2;
		pars->k++;
		return;
	}
	else if(pars->content[pars->i] && pars->content[pars->i] == '<')
	{
		pars->content1[pars->k] = ft_strdup("<");
		pars->k++;
		pars->i++;
		return;
	}
	else if(pars->content[pars->i] && pars->content[pars->i] == '>')
	{
		// pars->k++;
		pars->content1[pars->k] = ft_strdup(">");
		pars->k++;
		pars->i++;
		return;
	}
	else if(pars->content[pars->i] && pars->content[pars->i] == '|')
	{
		pars->content1[pars->k] = ft_strdup("|");
		pars->k++;
		pars->i++;
		return;
	}
}
