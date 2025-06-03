#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h> // PATH_MAX 4096
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"

// #define PATH_MAX  1024;

typedef struct PARSING_STRUCT
{
    unsigned int i; // 0
    unsigned int k; // 0
    int NumDollar; // 0
    unsigned int index;
    unsigned int lenOFarray; // 0
    char c;
	unsigned int nbOfPipes; // 0
    char **content1;
	int NbOfCommands;
    char *content; // input_user
}pars_T;


typedef struct REDIRECTION_list
{
    char *content;                      // file name
    int inout;                         // in or out (append) in = 1 out = 0;
    struct REDIRECTION_list *next;
} r_list;

typedef struct token_list
{
    struct token_list *next;
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
} T_list;

typedef struct t_cmd
{
    int index;                         // index dyal command f pipeline
    char **array;                      // words splited by pipes (arguments)
    char *cmd;                         // command name
    r_list *file;                      // redirections
    int qflag; // single quote
    struct t_cmd *next;                // next command (for pipes)
} c_cmd;

typedef struct s_env
{
    char *key;      // . "PATH"
    char *value;    // . "/usr/bin:/bin"
    struct s_env *next;
} t_env;


typedef struct words_list
{
    char *content;
    int index;
    struct words_list *next;

} w_list;

// Structure for shell environment
typedef struct t_shell
{
    t_env *envv;
    char **env;                       // environment variables
    char    **env_copy;
    int last_exit_status;              // $? value
    struct t_shell *next;
    // Add more fields as needed
} t_shell;

// Parsing functions
void SkipWhiteSpaces(pars_T *pars);
void Comands(pars_T *pars);
void print_list(T_list *list);
void print_list1(w_list *list);
pars_T *init_pars(char *in);
r_list *ccreate_node(char *value);
w_list *wcreate_node(char *value);
int     ft_strcmp(char *s1, const char *s2);
void clst_addback(r_list **lst, r_list *node);
void wlst_addback(w_list **lst, w_list *node);
int valid(char c);
char *expand_variables(char *input);

//---

void handle_redirection(c_cmd *list, T_list *token);
c_cmd *create_new_cmd(int array_size);
int count_cmd_args(T_list *start);
void splitit(T_list *token, c_cmd **final);
void CommandOrnot(pars_T *pars, w_list **wlist);
T_list *typesee(w_list **list);
int contains_single_quotes(const char *s);
char *Handlequotes(pars_T *pars, char c);
int is_whitespace(char c);
int is_redirection(char c);
void print_list(T_list *list);
pars_T *init_pars(char *in);
void fill_the_array(pars_T *pars);
void print_cmd_list(c_cmd *cmd);
void free_wlist(w_list **list);
void free_Plist(pars_T **list);
int check_quotes_closed(char *str);
int HardcodeChecks(char *str);
void call_all(char *input_user, w_list **wlist);


// ------ EXECUTION FUNCTIONS --------  //


// Main builtin functions

int                 is_builtin(c_cmd *command);
int                 execute_builtin(c_cmd *cmd, t_shell *shell);  // CORRECTED: c_cmd instead of t_command

// Individual builtin implementations

void                builtin_exit(c_cmd *cmd, t_shell *shell);   				  // Exit shell
int                 builtin_echo(c_cmd *cmd);                     // Echo command
int                 builtin_cd(c_cmd *cmd, t_shell *shell);       // Change directory
int                 builtin_pwd(void);                            // Print working directory
int                 builtin_export(c_cmd *cmd, t_shell *shell);   // Export env variables
int                 builtin_unset(c_cmd *cmd, t_shell *shell);    // Unset env variables
int                 builtin_env(t_shell *shell);                  // Print environment

// function utils check mul:
int                 is_numeric(const char *str);
void                free_test_cmd(c_cmd *cmd);
char                *get_env_value(char **env, const char *name);
int                 count_env_vars(char **env);
char                *ft_strcpy(char *dest,const char *src);
char                *create_env_string(const char *name, const char *value);
void                update_env_variable(t_shell *shell, const char *name, const char *value);
void                delete_env_variable(t_shell *shell, const char *name);
char                **dup_envp(char **envp);
void                print_env(char **env);
void                print_env_sorted(t_env *env);
char                *get_env_value_ll(t_env *env, const char *key);
t_env               *create_env_node(char *key, char *value);
void                build_env_list(t_shell *shell);
void                update_env_list(t_shell *shell, const char *key, const char *value);
int                 ft_strcmp_echo(const char *s);
// char            **function_split_env(t_shell *shell);
// t_env *create_env_node(char *key, char *value);
// void add_env_node(t_env **head, t_env *new);


// char	*find_path(char *cmd, char **envp);
// void	ft_free(char **str);
// void	execute(char *cmd, char **env);
// void            free_env(char **env); //check env is free or not
#endif

