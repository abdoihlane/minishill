#ifndef MINI_H
#define MINI_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"



typedef struct PARSING_STRUCT 
{
	int expand_flag;
	int herdoc_flag;
    unsigned int i;
    unsigned int k;
     int NumDollar;
    unsigned int index;
    unsigned int lenOFarray;
    char c;
	unsigned int nbOfPipes;
    char **content1;
	int NbOfCommands;
    char *content;
}pars_T;

typedef struct REDIRECTION_list
{
	char			*content; // file name
	int				inout; // in or out (append) in = 1 out = 0;
	struct REDIRECTION_list	*next;

}					r_list;

typedef struct token_list
{
	struct token_list	*next;
	int index;
	enum token{
		TOKEN_quotes,
		TOKEN_PIPE,
		TOKEN_WORD,
		TOKEN_REDIRECT_OUTPUT_AM,
		TOKEN_HERDOC,
		TOKEN_REDIRECT_INPUT,
		TOKEN_REDIRECT_OUTPUT,
	} type;
	char *value;
}T_list;

typedef struct t_cmd
{
	int index;
	char **array; // words splited by pipes
	char *cmd;
	int qflag; // single quote
	// int dflag; // double quote
	r_list *file; //any rederection
	struct t_cmd *next;
}	c_cmd;


typedef struct words_list
{
	char			*content;
	struct words_list	*next;
	int				index;

}					w_list;

int ft_strcmp(char *s1, char *s2);
/* ===== Parsing Functions ===== */
void     CommandOrnot(pars_T *pars, w_list **wlist);
void     typesee_plus(w_list *list, T_list *new_token);
T_list  *typesee(w_list **list);

int      is_whitespace(char c);
int      is_redirection(char c);

pars_T  *init_pars(char *in);
void     fill_array_plus(pars_T *pars);
void     fill_the_array(pars_T *pars);
void     SkipWhiteSpaces(pars_T *pars);

void     print_list(T_list *list);
void     free_wlist(w_list **list);
void     free_Plist(pars_T **list);
void     call_all(char *in, w_list **wlist);

int      check_quotes_closed(char *str);
int      red_check(char *str);
int      HardcodeChecks(char *str);


/* ===== Expansion Functions ===== */
char    *expand_variables(char *input);
int      contains_single_quotes(const char *s);
char    *expand_in_quotes(pars_T *pars, char *segment);
char    *Handlequotes(pars_T *pars, char c);
char    *ft_strjoin_all(char **array);


/* ===== Redirection & Command Handling ===== */
void     handle_red_plus(c_cmd *list, T_list *token);
void     handle_redirection(c_cmd *list, T_list *token);

c_cmd   *create_new_cmd(int array_size);
int      count_cmd_args(T_list *start);
void     splitit(T_list *token, c_cmd **final);
void     print_cmd_list(c_cmd *cmd);


#endif