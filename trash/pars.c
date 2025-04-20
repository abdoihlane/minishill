#include "mini.h"

void CommandOrnot(pars_T *pars,c_list **clist,w_list **wlist)
{
    int i = 1;
    clst_addback(clist,ccreate_node(pars->content1[0]));
    while(pars->content1[i])
    {
        if(pars->content1[i] && ft_strcmp(pars->content1[i],"|") == 0)
        {
            wlst_addback(wlist,wcreate_node(pars->content1[i]));
            i++;
            clst_addback(clist,ccreate_node(pars->content1[i]));
            i++;
        }
        else
        {
            wlst_addback(wlist,wcreate_node(pars->content1[i]));
            i++;
        }
    }
}
// quets single or double ---> checki flag open = 0 if u find a quets flag = 1 --> cmp char ' or "   
void checkClosedQuote(pars_T *pars, char c ,int start)
{
    int len = 0;
    pars->i++;
    while(pars->content[pars->i])
    {
        // printf("here\n");
        len = 0;
        while (pars->content[pars->i] != c && pars->content[pars->i])
        {
            pars->i++;
            len++;
        }
        // if(pars->content[pars->i] == '\0' || pars->content[pars->i] != c)
        //     //flag = 0;
        len++;
        pars->content1[pars->k] = malloc(len + 1);
        int j =0;
        while(j < len)
        {
            pars->content1[pars->k][j] = pars->content[start + j];
            j++;
        }
        pars->content1[pars->k][len] = '\0';
        pars->k++;
        pars->i++;
    }
}

void print_list(c_list *list)
{
    static int i = 0;
    c_list *begin = list;
    while(begin)
    {
        printf("commands number %d:%s\n",i,begin->content);
        i++;
        begin = begin->next;
    }
}
void print_list1(w_list *list)
{
    static int i = 0;
    w_list *begin = list;
    while(begin)
    {
        printf("args of command %d:%s\n",i,begin->content);
        i++;
        begin = begin->next;
    }
}

int valid(char c)
{
    return (c !=  32 && !(c >= 9 && c <= 13));
}

void SkipWhiteSpaces(pars_T *pars)
{
    while (pars->content[pars->i] && valid(pars->content[pars->i]))
        pars->i++;
    pars->c = pars->content[pars->i];
}

pars_T *count_and_allocate(char *in,pars_T *pars)
{
    pars = malloc(sizeof(pars_T));
    pars->i = 0;
    pars->k = 0;
    pars->content = in;
    int m = 0;

    while (pars->content[pars->i])
    {
        SkipWhiteSpaces(pars);
        if (pars->content[pars->i] == '\0')
            break;
        while (valid(pars->content[pars->i]))
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
        if (pars->content[pars->i] == '\'' ||  pars->content[pars->i] == '\"')
        {
                if(pars->content[pars->i] == '\"')
                {
                    checkClosedQuote(pars,'\"',pars->i);
                }
                else
                {
                    checkClosedQuote(pars,'\'',pars->i);
                }
                pars->nbOfPipes++;
        }
        SkipWhiteSpaces(pars);
        if (pars->content[pars->i] == '\0')
            break;
        int len = 0;
        int start = pars->i;
        while (valid(pars->content[pars->i]))
        {
            pars->i++;
            len++;
        }
        pars->content1[pars->k] = malloc(len + 1);
        int j =0;
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
void	free_wlist(w_list **list)
{
    w_list	*temp;

	while (*list)
	{
		temp = (*list)->content;
		free(*list);
		*list = temp;
	}
}

void	free_clist(c_list **list)
{
	c_list    *temp;

	while (*list)
	{
		temp = (*list)->content;
		free(*list);
		*list = temp;
	}
}

void call_all(char *in,pars_T *pars,c_list **clist,w_list **wlist)
{
    pars = count_and_allocate(in,pars);
    fill_the_array(pars);
    printf("ss\n");
    CommandOrnot(pars,clist,wlist);
}
int main()
{
    // if (ac < 2)
    //     return 1;
    char *in;
    c_list *clist = NULL;
    w_list *wlist = NULL;
    pars_T *pars = NULL;
    while(1)
    {
        in = readline("➜  mini_with_salah ");
        call_all(in,pars,&clist,&wlist);
        // print_list(clist);
        // print_list1(wlist);
        // free_wlist(&wlist);
        // free_clist(&clist);
    }
    int i = 1;
    return 0;
}
