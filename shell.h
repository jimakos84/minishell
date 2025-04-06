#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../ft_libft/libft.h"
# include "../ft_libft/ft_printf.h"
# include "../ft_libft/get_next_line.h"

/**
 * data node strucutre to hold the tokens extract from input, this node will make a linked list
*/
typedef struct s_list
{
	char *token;
	struct s_list *next;
} t_list;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char *command;
	char **args;
	int num_args;
	struct s_cmd *next;
} t_cmd;

typedef struct s_shell
{
	int num_cmds;
	char **envp;
	char **copy_env;
	char *trim;
	t_cmd *cmds;
	//t_list *tokens;
	char	**tokens;
	t_env	*env;
} t_shell;

/**
 * Implementaion in main.c
*/
void print(t_list *list, char *msg);

/**
 * Implementaion in srcs/validate.c
*/
int input_validate(char *input);
char *in_quotes(char *input);

/**
 * Implementaion in srcs/error.c
*/
int syntax_error(char *msg);

/**
 * Implementation in srcs/helper.c
*/
int activate_shell(char *input);

/**
 * Implementation in srcs/token.c
*/
t_list *list_add_back(t_list *list, char *str);
t_cmd *list_add_command(t_cmd *cmds, t_cmd *node);
int extract_tokens(t_list **tokens, char *input);

/**
 * Implementation in srcs/parser.c
*/
int parse_and_expand(t_shell *mini);

/**
 * Implementaion in srcs/utils.c
*/
int ft_strnmcpy(char **dest, char *src, int n, int m);

/**
 * Implementaion in srcs/execute.c
*/
int execute(t_shell *mini);

/**
 * Implementaion in srcs/cleaner.c
*/
int clear_and_exit(t_shell *mini);


/**
 * Implementaion in srcs/signal.c
*/
void init_sig(void);

#endif
