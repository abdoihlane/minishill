
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