#include "mini.h"

void CommandOrnot(pars_T *pars, c_list **clist, w_list **wlist)
{
    int i = 0;
    // clst_addback(clist, ccreate_node(pars->content1[0]));
    while (pars->content1[i])
    {
        // if (ft_strcmp(pars->content1[i], "|") == 0)
        // {
        //     wlst_addback(wlist, wcreate_node(pars->content1[i]));
        //     i++;
        //     if (pars->content1[i])
        //         clst_addback(clist, ccreate_node(pars->content1[i]));
        //     i++;
        // }
        // else
        // {
            wlst_addback(wlist, wcreate_node(pars->content1[i]));
            i++;
        // }
    }
}

void   *typesee(w_list **list)
{
    w_list *begin = *list;
    T_list *tokens = NULL;
    T_list *last = NULL;
    T_list *new_token;

    if (!begin)
        return NULL;

    new_token = malloc(sizeof(T_list));
    if (!new_token)
        return *list;

    new_token->value = begin->content;
    new_token->type = TOKEN_WORD;
    new_token->next = NULL;

    tokens = new_token;
    last = new_token;
    begin = begin->next;

    while (begin)
    {
        new_token = malloc(sizeof(T_list));
        if (!new_token)
            break;

        new_token->value = begin->content;
        new_token->next = NULL;

        if (ft_strcmp(begin->content, "|") == 0)
            new_token->type = TOKEN_PIPE;
        else if (ft_strcmp(begin->content, "<") == 0)
            new_token->type = TOKEN_REDIRECT_INPUT;
        else if (ft_strcmp(begin->content, ">") == 0)
            new_token->type = TOKEN_REDIRECT_OUTPUT;
        else if (ft_strcmp(begin->content, "<<") == 0)
            new_token->type = TOKEN_HERDOC;
        else if (ft_strcmp(begin->content, ">>") == 0)
            new_token->type = TOKEN_REDIREC_OUTPUT_AM;
        else
            new_token->type = TOKEN_WORD;

        last->next = new_token;
        last = new_token;
        begin = begin->next;
    }
    return tokens;
    // Now `tokens` holds your full typed list starting with a word.
}

// void typesee(w_list **list)
// {
//     T_list *tokens = NULL;
//     w_list *begin = *list;
//     if(begin)
//     {
//         tokens->value = begin->content;
//         tokens->type = TOKEN_WORD;
//         begin = begin->next;
//     }
//     while(begin)
//     {
//         if(ft_strcmp(begin->content,"|"))
//         {
//             tokens->value = begin->content;
//             tokens->type = TOKEN_PIPE;
//             begin = begin->next;            
//         }
//         else if(ft_strcmp(begin->content,"<"))
//         {
//             tokens->value = begin->content;
//             tokens->type = TOKEN_REDIRECT_INPUT;
//             begin = begin->next;            
//         }
//         else if(ft_strcmp(begin->content,">"))
//         {
//             tokens->value = begin->content;
//             tokens->type = TOKEN_REDIRECT_OUTPUT;
//             begin = begin->next;            
//         }
//         else if(ft_strcmp(begin->content,"<<"))
//         {
//             tokens->value = begin->content;
//             tokens->type = TOKEN_DELIMITER;
//             begin = begin->next;            
//         }
//         else if(ft_strcmp(begin->content,">>"))
//         {
//             tokens->value = begin->content;
//             tokens->type = TOKEN_REDIREC_OUTPUT_AM;
//             begin = begin->next;            
//         }
//         else 
//         {
//             tokens->value = begin->content;
//             tokens->type = TOKEN_WORD;
//             begin = begin->next;
//         }
//     }
// }
void checkClosedQuote(pars_T *pars, char c, int start)
{
    pars->i++; //to check later wsch ndekhleha wla la " "
    int s = pars->i;
    while (pars->content[pars->i] && pars->content[pars->i] != c)
        pars->i++;
    int len = pars->i - s;
    pars->content1[pars->k] = malloc(len + 1);
    int j = 0;
    while (j < len)
    {
        pars->content1[pars->k][j] = pars->content[s + j];
        j++;
    }
    pars->content1[pars->k][len] = '\0';
    pars->k++;
    if (pars->content[pars->i] == c)
        pars->i++; //to check later wsch ndekhleha wla la " "
}

void print_list(T_list *list)
{
    while (list)
    {
        printf("token : %s     ", list->value);
        printf("type: %s\n", list->type);
        list = list->next;
    }
}

void print_list1(w_list *list)
{
    static int i = 1;
    while (list)
    {
        printf("word %d: %s\n", i++, list->content);
        list = list->next;
    }
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

pars_T *count_and_allocate(char *in)
{
    pars_T *pars = malloc(sizeof(pars_T));
    pars->i = 0;
    pars->k = 0;
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
    pars->nbOfPipes = 0;

    while (pars->content[pars->i])
    {
        SkipWhiteSpaces(pars);
        if (pars->content[pars->i] == '\0')
            break;

        if (pars->content[pars->i] == '\'' || pars->content[pars->i] == '\"')
        {
            checkClosedQuote(pars, pars->content[pars->i], pars->i);
            continue;
        }

        int start = pars->i;
        int len = 0;
        while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
        {
            pars->i++;
            len++;
        }
        pars->content1[pars->k] = malloc(len + 1);
        int j = 0;
        while (j < len)
        {
            pars->content1[pars->k][j] = pars->content[start + j];
            j++;
        }
        pars->content1[pars->k][len] = '\0';
        pars->k++;
    }
    pars->content1[pars->k] = NULL;
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
    pars_T *pars = count_and_allocate(in);
    fill_the_array(pars);
    CommandOrnot(pars, clist, wlist);
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
