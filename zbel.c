
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





