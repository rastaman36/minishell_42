/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:46:09 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/02 23:21:30 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_status;

enum				e_def
{
	QUOT = 19,
	QUOTS = 20,
	SPACES = 23,
	PIPE = 24,
	REDR = 25,
	REDL = 26,
};

typedef struct Node
{
	char			*str;
	struct Node		*next;
}					t_list;

typedef struct s_cmd
{
	int				type;
}					t_cmd;

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
	int				j;
	int				fd;
	char			*s;
	char			*name_vr;
	char			*name_vl;
	char			*status;
	char			*v;
	int				l;
}					t_env;

typedef struct s_execdata
{
	int				type;
	char			**path;
	char			**argv;
	char			*infile;
	char			*outfile;
	int				pid;
	char			*tmp;
	t_list			*arg;
}					t_execdata;

typedef struct s_pipe
{
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
	int				pid;
	int				pid2;
	int				pipefd[2];

}					t_pipe;

typedef struct s_rede
{
	int				type;
	int				infd;
	int				outfd;
	int				append;
	struct s_cmd	*cmds;
}					t_redir;

typedef struct s_here_doc
{
	int				type;

	int				herfd;
	int				outfd;
	struct s_cmd	*cmds;
}					t_here;

void				ft_lstadd_back(t_env **lst, t_env *new);
t_env				*ft_lstnew(char *name, char *value);
int					ft_strncmp(char *s1, char *s2, int n);
int					ft_strlen(char *str);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char *s1, char c);
char				*ft_strdup(const char *src);
void				bost_free(char **s);
int					checking_pipe(char **str, char c, int *a);
t_cmd				*piping(t_cmd *left, t_cmd *right);
char				**building_data(char **s, int *a);
int					arrlen(char **str);
t_cmd				*exec_data(char **str, t_env *env);
char				*ft_strjoin2(char *s1, char *s2);
void				creation_of_env(t_env **env, char **envp);
char				*get_next_line(int fd);
void				putinfile(int fd, char *s);
char				*get_next_line(int fd);
char				**building_data(char **s, int *a);
int					checking_pipe(char **str, char c, int *a);
char				**geting_argument(char **str);
char				*geting_names_files(char **string, char c, t_env *env);
void				handling_here_doc(char *string, int fd, t_env *env);
char				*geting_name_limiter(char **string, char c);
int					checking_here_doc(char **str, char c);
int					limiter_expanding(char c);
char				*get_variable(char *str);
char				*get_value(char *name_vr, t_env *env);
char				*expanding_env(char *s, t_env *env);
int					ft_strcmp(char *s1, char *s2);
void				execute_pipeline(t_cmd *tree, int *counter, t_env **env,
						t_list *args);
int					check_cmp(char **str, char *s);
int					ft_isalnum(int c);
int					ft_strchr(char *str, char c);
void				new_env_var(t_env **env, char *name, char *value);
void				join_env_var(t_env **env, char *name, char *value);
void				handle_signals(int signo);
void				unset(t_env **env, t_list *args);
int					checkerrors(char **s);
void				ft_pwd(void);
char				*ft_itoa(int n);
void				creation_of_node(t_env **env, char **envp);
t_list				*create_linked_list(char **str);
void				printer_env(t_env *env);
char				**ft_split2(char const *s, char c);
void				display_list(char **string2);
int					check_quotes(char *str);
t_list				*create_linked_list(char **str);
void				free_dd(char **str);
void				free_recur(t_cmd *tree);
char				*check(char *name_vr, t_env *env);
void				ft_rremove(char *str);
int					ft_strchr2(char *str, char c);
void				free_linked_list(t_list *head);
int					ft_isdegit(char *string);
void				export(t_env **varenv, t_list *args);
void				ft_echo(t_list *args);
void				unset(t_env **env, t_list *args);
void				builtins(t_env **env, t_list *args, char *s,
						t_execdata *execnode);
void				ft_cd(t_list *arg, t_env **env);
void				execute_single_command(char **command, t_cmd *tree,
						t_env **env, t_list *args);
int					is_builtin(char *s);
void				parent_of_all(t_pipe *pipenode);
void				childe1_pipes(t_pipe *pipenode, t_env **env, t_list *args,
						int *counter);
void				childe2_pipes(t_pipe *pipenode, t_env **env, t_list *args,
						int *counter);
void				error_msg(int i);
void				if_it_pipe(t_cmd *tree, int *counter, t_env **env,
						t_list *args);
void				the_last_exec(t_execdata *execnode, char *str);
void				path_exec1(t_execdata *execnode, int pid, int status);
void				fork_failed(int pid);
char				*execute_single2(t_execdata *execnode, char *str,
						int status, int pid);
void				execute_single1(t_execdata *execnode);
void				restoring_data_utls(char **str, int a, int j);
void				restoring_data(char **str);
char				*norm_remov(char *s, int *a, char *string);
char				*removing_spaces(char *s);
char				*puting_space(char *s);
int					is_duplicate(t_env *env, char *var_name);
void				ft_norm(t_env *env, char **f, int *a, char **string);
void				her_light(char *string, int fd, t_env *env, char **tmp);
void				free_of_magic(t_list *args, char *line_cmd, char **string,
						t_cmd *parce);
int					norming_main(char *line_cmd);
t_cmd				*parce_tree(char **str, int *a, t_env **env);
#endif