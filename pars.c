#include "mini.h"

void CommandOrnot(pars_T *pars,c_list **clist,w_list **wlist)
{
    int i = 1;

    clst_addback(clist,ccreate_node(pars->content1[0]));
    while(pars->content1[i])
    {
        if(ft_strcmp(pars->content1[i],"|") == 0)
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
        len++;
        pars->content1[pars->k] = malloc(len + 1);
        int j =0;
        while(j <= len)
        {
            pars->content1[pars->k][j] = pars->content[start + j];
            j++;
        }
        pars->content1[pars->k][len+1] = '\0';
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
    return (c > 32);
}

void SkipWhiteSpaces(pars_T *pars)
{
    while (pars->content[pars->i] && pars->content[pars->i] <= 32)
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
    CommandOrnot(pars,clist,wlist);
}
int main(int ac, char **av)
{
    // if (ac < 2)
    //     return 1;
    char *in;
    c_list *clist = NULL;
    w_list *wlist = NULL;
    pars_T *pars;
    while(1)
    {
        in = readline("➜  mini_with_salah ");
        call_all(in,pars,&clist,&wlist);
        print_list1(wlist);
        print_list(clist);
        // free_wlist(&wlist);
        // free_clist(&clist);
    }
    int i = 1;
    return 0;
}
