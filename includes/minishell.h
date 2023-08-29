/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:31:37 by gmiyakaw          #+#    #+#             */
/*   Updated: 2023/08/05 16:42:08 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "./readline/history.h"
# include "./readline/readline.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_CMD 1024
# define PATH_MAX 1024

/*--  GLOBAL VARIABLE  ---*/
long long				g_exit_v;

/*--  QUOTE TYPES  ---*/

typedef enum e_quote
{
	NO_QUOTE,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	SINGLE_META,
	DOUBLE_META,
	ERROR,
}						t_quote;

/*--  DATA STRUCTURES  --*/
typedef struct s_cmd	t_cmd;
typedef struct s_exp	t_exp;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	DOLLAR,
}						t_type;

typedef struct s_token
{
	t_type				type;
	t_quote				quote;
	char				*arg;
	int					pos_in;
	int					pos_out;
	int					i;
	int					k;
	int					is_quoted;
	int					is_exp;
	int					flag_do;
	int					w_space_between;
}						t_token;

typedef struct s_data
{
	t_token				*tok_ch;
	t_cmd				*cmd_list;
	char				*raw_line;
	int					size_raw_line;
	int					token_count;
	int					token_count_temp;
	int					cmd_count;
	char				**envp;
	char				**paths;
	int					*pid;
	int					**fd;
	int					pos_cmd_i;
	char				*buffer;
	int					back_up_out;
	int					back_up_in;
	int					nb_meta;
	int					k_temp;
	int					i;
	int					j;
	int					count;
	char				*pwd;
}						t_data;

typedef struct s_cmd
{
	t_token				*cmd_tokens;
	t_data				*data;
	int					cmd_token_count;
	int					fd_count;
	int					fd_input;
	int					fd_output;
	t_type				input_type;
	t_type				output_type;
	char				**args;
	char				*cmd_path;
	int					no_built;
	int					flag_echo;
	int					flag2_echo;
	int					error;
	int					i;
	int					j;
}						t_cmd;

typedef struct s_exp
{
	char				*alias;
	char				*target;
}						t_exp;

/**--  ERROR MESSAGES  --*/
# define MLLC_ERR "malloc error\n"
# define PTH_ERR "error. path not found\n"
# define OPN_ERR "error opening file\n"
# define EXP_ERR "error during alias expansion\n"
# define EXP_INV_VNM "export error. invalid variable name. \
please follow the format: $>export $VAR=VALUE\n"
# define UST_PATH "error. PATH is unset, please restart terminal\n"

/*--  MACROS  --*/
# define TMP_HD "tmp_heredoc"
# define PRE_EXP "declare -x "

/*--  INITIALIZATION FUNCITON  --*/
void					ft_init_data(t_data *data);
void					ft_init_data_2(t_data *data);
void					set_env_path(t_data *data, char **envp);
char					**pathfinder(t_data *data);

/*--  MAIN FUNCITON  --*/
void					ft_main_program(t_data *data);
void					ft_buff_null(t_data *data);

/*-- PARSING FUNCTIONS  --*/

/*--  LEXER FUNCTIONS  --*/
t_data					*ft_split_struct(char *str, char *charset,
							t_data *data);
int						ft_is_charset_2(t_data *data, int j, int i);
void					ft_flag_space(t_data *data, int i);
int						ft_tchek_if_quote(char *str);
t_data					*ft_split_struct_on_quote(char *str, t_data *data);
int						ft_split_struct_on_quote_2(t_data *data, char *str);
void					ft_go_to_meta(t_data *data, char *str);
void					ft_quote_part_2(t_data *data, char *str);
void					ft_split_quote(char *str, t_data *data);
void					ft_fix_position(t_data *data, char c, char *str);
int						ft_split_quote_2(char *str, t_data *data, char c);
char					ft_is_c(char *str, t_data *data, char c);
char					*ft_strdup_end_start(char *src, int start, int end);
char					*ft_strdup_end_start2(char *src, int start, int end);
int						ft_search_next(char *str, t_data *data, char c);
void					ft_clean_array_struct(t_data *data);
void					ft_print_array_struct(t_data *data);
void					ft_split_metachar(char *str, t_data *data);
char					ft_metachar_2(t_data *data, int i, char c, char *str);
void					ft_stock_meta(t_data *data, char *str);
int						ft_count_same_metachar(char *str, t_data *data, char c);
int						ft_is_charset(char c, char *charset);
int						ft_is_white_space(char c);
int						ft_is_meta_char(char c);
int						ft_is_quote(char c);
void					ft_before_meta_quote(char *str, t_data *data);
void					ft_free_lexical(t_data *data);
void					ft_clean_token(t_data *data);
int						ft_tchek_what_before(char *str, t_data *data);
int						ft_tchek_only_space(char *str, t_data *data);
int						ft_count_word(char *str, char *charset);
int						ft_size_w(char *str, char *charset, int i);
void					ft_is_dollar(char *str, t_data *data);
int						ft_tchek_if_end(char *str, t_data *data);
int						ft_is_single_quote(char *str, t_data *data, char c);
int						ft_is_meta_char_2(char c);
int						ft_tchek_if_only_meta(char *str);
int						ft_tchek_if_end(char *str, t_data *data);
int						ft_tchek_if_dollar(char *str, t_data *data);
int						ft_tchek_if_dollar2(char *str);
int						ft_check_multiple_c(char *str, char c);
void					ft_fill_fds(t_data *data);

/*--  PARSER FUNCTIONS  --*/
int						parser(t_data *data);
void					classifier(t_data *data);
void					ft_init_token(t_token *tok_ch);
t_data					*ft_split_struct(char *str, char *charset,
							t_data *data);
bool					is_path_a_variable(t_cmd *cmd);

/*--  SYNTAX CHECKING FUNCTIONS  --*/
int						syntax_check(t_data *data);
void					check_append(t_data *data, int i, bool *invalid);
void					check_heredoc(t_data *data, int i, bool *invalid);
void					check_redir_out(t_data *data, int i, bool *invalid);
void					check_redir_in(t_data *data, int i, bool *invalid);
void					check_pipe(t_data *data, int i, bool *invalid);

/*--  EXPANSION FUNCTIONS  --*/
int						find_expansion(t_data *data);
int						find_expansion_loop(t_data *data, int *i, int *arg_i);
int						expand(t_token *token, int dollar_position,
							t_data *data);
void					expand_free_array(t_exp *expansion);
void					switcheroo(t_token *token, int dollar_position,
							t_exp *expansion);
bool					is_expansion(t_token *tok, int i, int tok_i);
char					*alias_finder(t_token *tok, int i);
char					*target_finder(char *alias, t_data *data);
void					replace_empty(t_token *token, int dollar_position,
							t_exp *exp);

/*--  HEREDOC FUNCTIONS  --*/
void					just_here_docking(t_cmd *cmd, int metachar_pos);
char					*heredoc_expand(char *buffer, int dollar_pos,
							t_data *data);
char					*heredoc_find_expansion(t_cmd *cmd, char *buffer,
							int metachar_pos);
char					*heredoc_alias_finder(char *buffer, int dollar_pos);
bool					is_valid_alias_char(char c);
char					*heredoc_switcheroo(char *buffer, int dollar_pos,
							t_exp *exp);
char					*heredoc_replace_null(char *buffer, int dollar_position,
							t_exp *exp);
void					delete_file(char *filename);
void					heredoc_free_arrays(char *a, char *b, char *c, char *d);

/*--  COMMAND PARSING FUNCTIONS  --*/
int						init_cmds(t_data *data);
void					ft_init_cmd_var(t_data *data, int i);
int						make_cmd_tokens(t_data *data, t_token *tok_ch);
int						get_cmd_argcount(t_cmd *cmd);
bool					is_absolute(char *arg);
bool					is_path_unset(t_data *data);
char					*cmd_pathfinder(t_cmd *cmd, char **paths);
int						parse_cmds(t_cmd *cmd_list, int cmd_count, char **envp);
int						set_cmd_args(t_cmd *cmd);
int						ft_error_set_arg(void);
int						set_cmd_fds(t_cmd *cmd);
int						open_inputs(t_cmd *cmd);
int						open_outputs(t_cmd *cmd);
int						open_append(t_cmd *cmd, int i);
int						open_heredoc(t_cmd *cmd, int i);
int						open_redir_in(t_cmd *cmd, int i);
int						open_redir_out(t_cmd *cmd, int i);

/*--  EXECUTION FUNCITONS  --*/
void					ft_multi_pipe(t_data *data);
void					ft_run_process(t_data *data);
void					ft_parent(t_data *data);
void					ft_child_part_2(t_data *data);
long long				ft_close_exit(t_data *data);
int						ft_init_fd(t_data *data);
void					ft_print_path(t_data *data);
char					*ft_str_min(char *str);
long long				ft_is_built_ins(t_data *data);
long long				ft_execute_export_no_arg(t_data *data);
int						ft_is_built_ins_parent(t_data *data);
int						ft_is_built_ins_yes(t_data *data);
int						ft_is_built_ins_all(t_data *data);
int						ft_exec_export_no_arg(t_data *data);
void					ft_all_fd_in(t_data *data);
void					ft_all_fd_out(t_data *data);
void					ft_close_all(void);
void					ft_single_cmd(t_data *data);
void					set_exit_code(t_data *data, int status);
void					ft_fill_fds_single(t_data *data);
int						ft_single_cmd_child(t_data *data, int pid);
void					ft_single_cmd_builtins(t_data *data);
void					ft_free_pid(t_data *data);

/*--  SIGNAL FUNCTIONS  --*/
void					ft_handler_ctrl_c(int signum, siginfo_t *s_info,
							void *content);
void					ft_handler_ctrl_not(int signum, siginfo_t *s_info,
							void *content);
void					ft_init_signal(void);

/*--  STRING FUNCTIONS  --*/

/*--  BUILT-IN FUNCTIONS  --*/

/*EXPORT*/
int						our_export(t_cmd *cmd);
char					*get_alias(char *env_str);
char					**get_var_names(t_cmd *cmd);
char					**get_values(t_cmd *cmd);
int						find_equal(char *str);
char					**make_new_env(char **var_names, char **values,
							char **env);
char					**export_handle_quotes(t_cmd *cmd);
char					**export_join_quoted_arg(t_cmd *cmd, char **new_args,
							int i, int j);
char					**export_handle_expansion(t_cmd *cmd);
void					export_join_expanded(t_cmd *cmd, char **new_args, int i,
							int j);
void					export_free_arrays(char **var_names, char **values,
							char **envp);
void					replace_in_env(char **var_names, char **values,
							int var_i, char **env);
bool					export_print_error(void);
bool					is_in_env(char *var_name, char **env);
int						count_repeats(char **var_names, char **env);
char					**export_copy_env(char **old_env, char **var_names);
bool					export_valid_char(char c);
bool					export_check_valid_arg(t_cmd *cmd);

/* EXPORT NO ARG*/
int						export_no_arg(t_data *data);
void					ft_print_pwd(t_data *data);
void					ft_print_normal(t_data *data, char *tmp);
char					*ft_get_path_2(t_data *data, char *path);
char					**make_alias_list(char **envp);
void					put_in_order(char **alias_list);
int						print_ordered_list(char **alias_list, char **env,
							t_data *data);
void					print_ordered_list_2(int *repeat, char **env,
							char *alias_list, t_data *data);

/*ENV*/
int						our_env(t_cmd *cmd);
void					env_print_pwd(t_cmd *cmd);
char					*env_set_path(t_cmd *cmd);

/*EXIT*/
int						our_exit(t_cmd *cmd);
int						ft_tchek_arg_exit(t_cmd *cmd);
int						ft_str_is_numeric(char *str);
char					*ft_tchek_if_quoted(t_cmd *cmd);
long long				ft_atoll(const char *str);
int						ft_is_int(char *str);
void					ft_check_max_min(t_cmd *cmd);
int						ft_max_min_longlong(t_cmd *cmd);
int						ft_min_longlong(t_cmd *cmd);
void					ft_tk_count_2(t_cmd *cmd);
void					ft_int_num(t_cmd *cmd, long long num);

/*UNSET*/
int						our_unset(t_cmd *cmd);

/*ECHO*/
int						our_echo(t_cmd *cmd);
int						ft_if_flag(t_cmd *cmd, int i);
int						ft_put_space(t_cmd *cmd, int i, int flag2);
int						ft_put_flag(t_cmd *cmd, int flag, int i);
void					ft_put_n(int flag);
int						ft_is_condition(t_cmd *cmd, int i);

/*CD*/
int						our_cd(t_cmd *cmd);
char					*ft_cd_directory(t_cmd *cmd, char *path);
char					*ft_cd_home_2(t_cmd *cmd, char *pwd);
char					*ft_cd_home(t_cmd *cmd, char *path, char *pwd);
int						ft_tchek_if_env(t_cmd *cmd);

/*SIMPLE BUILT-INS*/
int						our_pwd(t_cmd *cmd);
int						ft_tab_len(t_cmd *cmd);
char					*ft_add_alias_path(char *new_pwd, char *path);
char					*ft_strncpy(char *dest, char *src, unsigned int n);
void					ft_printf_env(char **env);

/*--  EXIT / ERROR FUNCTIONS--*/
int						syntax_error(t_data *data);
void					free_cmd_ch(t_cmd *cmd);
void					ft_free_all_fd(t_data *data);
// void	syntax_error2(t_data *data);
void					clean_exit(t_data *data);
void					free_token_chain(t_token *tok_ch, int token_count);
void					*free_data_struct(t_data *data);
void					free_cmd_list(t_data *data);

/*--  PRINT / TEST FUNCTIONS ---*/
void					print_token(t_token *token);
void					print_token_chain(t_token *token_chain,
							int token_count);
void					print_struct(t_data *data);
void					print_cmd_tok_chain(t_data *data);
void					print_cmd_struct(t_cmd *cmd);

/*--  MISC. FUNCTIONS  --*/
t_token					*clone_tok_ch(t_data *data, int start, int end,
							int *cmd_token_count);
t_token					*remove_token(t_token *tok_ch, int rmv_i,
							int *tok_count);
t_token					copy_token(t_token old_tok);
int						ft_error_404(t_token *cmd_tokens);

char					**join_args(t_cmd *cmd);
bool					should_join(t_token *token);
int						count_splits(t_cmd *cmd);
char					**cmd_rmv_empty(t_cmd *cmd);
#endif