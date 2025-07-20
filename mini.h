/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:51:56 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/20 23:08:01 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define COLOR_RESET "\001\033[0m\002"
# define COLOR_PINK "\001\033[38;2;255;105;180m\002"

typedef struct PARSING_STRUCT
{
	int						expand_flag;
	int						herdoc_flag;
	unsigned int			i;
	unsigned int			dflag;
	unsigned int			k;
	int						numdollar;
	unsigned int			index;
	unsigned int			lenofarray;
	char					c;
	unsigned int			nbofpipes;
	char					**content1;
	int						nbofcommands;
	char					*content;
}							t_pars;

typedef struct REDIRECTION_list
{
	char					*content;
	int						inout;
	struct REDIRECTION_list	*next;
}							t_red_list;

enum e_token
{
	TOKEN_quotes,
	TOKEN_PIPE,
	TOKEN_WORD,
	TOKEN_REDIRECT_OUTPUT_AM,
	TOKEN_HERDOC,
	TOKEN_REDIRECT_INPUT,
	TOKEN_REDIRECT_OUTPUT
};

typedef struct token_list
{
	enum e_token			type;
	struct token_list		*next;
	int						index;
	char					*value;
}							t_token;

typedef struct t_cmd
{
	int						index;
	int						capacity;
	char					**array;
	char					*cmd;
	int						qflag;
	t_red_list				*file;
	struct t_cmd			*next;
}							t_cmd;

typedef struct words_list
{
	char					*content;
	struct words_list		*next;
	int						index;

}							t_wlist;

t_wlist						*wcreate_node(char *value);
void						wlst_addback(t_wlist **lst, t_wlist *node);
int							ft_strcmp(char *s1, char *s2);
/* ===== Parsing Functions ===== */
void						commandornot(t_pars *pars, t_wlist **wlist);
void						typesee_plus(t_wlist *list, t_token *new_token);
t_token						*typesee(t_wlist **list);
int							add_token_node(t_wlist *begin, t_token **tokens,
								t_token **last, int *index);
int							is_quotes(char c);
int							is_whitespace(char c);
void						skipwhitespaces(t_pars *pars);
int							is_redirection(char c);
void						count_dollar(t_pars *pars);

t_pars						*init_pars(char *in);
void						fill_array_plus(t_pars *pars);
void						fill_the_array(t_pars *pars);
char						*fill_array_and_callexpand(t_pars *pars);
char						*fill_between_space_and_red(t_pars *pars,
								char *token);
t_token						*fill_command_fields(t_token *tmp, t_cmd *current);

void						print_token(t_token *list);
void						free_wlist(t_wlist **list);
void						free_plist(t_pars **list);
void						call_all(char *in, t_wlist **wlist);

int							check_quotes_closed(char *str);
int							red_check(char *str);
int							hardcodechecks(char *str);
int							check_spaces_and_red(t_pars *pars);

/* ===== Expansion Functions ===== */
// static char	*build_result(char *input, char *varname, int var_len);
char						*expand_variables(char *input);
char						*build_result(char *input, char *varname,
								int var_len);
int							contains_single_quotes(const char *s);
char						*expand_in_quotes(t_pars *pars, char *segment);
char						*handlequotes(t_pars *pars, char c);
char						*ft_strjoin_all(char **array);

/* ===== Redirection & Command Handling ===== */
void						handle_red_plus(t_cmd *list, t_token *token);
void						handle_redirection(t_cmd *list, t_token *token);

t_cmd						*create_new_cmd(int array_size);
int							count_cmd_args(t_token *start);
void						splitit(t_token *token, t_cmd **final);
void						print_cmd_list(t_cmd *cmd);
void						reparse_variable(t_pars *pars);

#endif