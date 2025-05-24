#ifndef MINISHELL_H
#define MINISHELL_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"


typedef struct PARSING_STRUCT
{
    unsigned int i;
    unsigned int k;
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
		TOKEN_PIPE,
		TOKEN_WORD,
		TOKEN_REDIREC_OUTPUT_AM,
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
	char	*cmd; // salah-cmd
	r_list *file; //any rederection
	struct t_cmd *next;
}	c_cmd;


typedef struct words_list
{
	char			*content;
	struct words_list	*next;
	int				index;

}					w_list;

typedef struct t_shell
{
    char **env;                        // environment variables
    int last_exit_status;              // $? value
    // Add more fields as needed
} t_shell;

void SkipWhiteSpaces(pars_T *pars);
void Comands(pars_T *pars);
void print_list(T_list *list);
void print_list1(w_list *list);
pars_T *init_pars(char *in);
r_list	*ccreate_node(char  *value);
w_list	*wcreate_node(char *value);
int ft_strcmp(char *s1, char *s2);
void	clst_addback(r_list **lst, r_list *node);
void	wlst_addback(w_list **lst, w_list *node);
int valid(char c);
// void expand_variables(T_list *tokens);
char *expand_variables(char *input);

//functions bultines

int builtin_cd(c_cmd *cmd, t_shell *shell);
int builtin_echo(c_cmd *cmd);

#endif
