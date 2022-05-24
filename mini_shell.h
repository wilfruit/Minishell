/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:45:56 by avaures           #+#    #+#             */
/*   Updated: 2022/05/24 12:42:41 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
#define MINI_SHELL_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include <signal.h>

# define TOKEN_ERROR -1
# define TOKEN_CMD 0
# define TOKEN_ARG 1
# define TOKEN_OUTPUT_REDIRECTION 2
# define TOKEN_OUTPUT_APPEND_EDIRECTION 3
# define TOKEN_INTPUT_REDIRECTION 4
# define TOKEN_INTPUT_HEREDOC_REDIRECTION 5
# define TOKEN_FILE 6
# define TOKEN_LIMITER 7

# define DOLLAR_NO 0
# define DOLLAR_MACRO 1

extern int	global_error;

typedef struct s_manage_pipe
{
	int	i;
	int	j;
	int	k;
	int	size;
	int	end;
	int	nb_cmd;
	int	*size_cmd;
	char	**pipecmd;
}	t_manage_pipe;

typedef struct s_token
{
	int	type;
	int	len_value;
	int	is_dollar;
	int	nb_token;
	char	*value;
}	t_token;

typedef struct	s_pipe
{
	t_token	*scmd;
	char	*cmd;
	int	len_cmd;
	int	nb_token;
}	t_pipe;

typedef struct    s_envi
{
    char        *str;
    struct s_envi    *next;
}        t_envi;

typedef struct	s_shell
{
	int	exit_end;
	int	std_in;
	int	std_out;
	int	std_error;
	t_pipe	*token;
	t_envi	*env;
	t_envi	*exports;
}		t_shell;

void	forced_prompt(int sig);
void	forced_continue(int sig);
char *check_line(char **line);
int		control(void);
void	free_struct(t_manage_pipe utils, t_pipe **prompt);
void	free_token(t_manage_pipe utils, t_pipe **prompt);
int		is_redirection(char c);
int		set_struct(char **line, t_manage_pipe utils, t_pipe **prompt);
void	*help_cmd_struct(int nb_cmd, int len_cmd, t_pipe **prompt);
void	*cmd_struct(t_manage_pipe utils, t_pipe **prompt);
void	*found_len_token(t_manage_pipe utils, t_pipe **prompt);
void	*set_token(t_manage_pipe utils, t_pipe **prompt);
void	*make_tab_cmd(t_manage_pipe *mpipe, char *line);
void	*set_manage(t_manage_pipe *mpipe, char *line);
void	*len_cmd_pipe(t_manage_pipe *mpipe, char *line);
int		size_cmd_tab(char *line);
char	*set_path(char **infos);
void 	*determine_type(t_pipe *prompt);
void	*all_pipe_cmd(t_manage_pipe *mpipe, char *line);
void	clean_manage(t_manage_pipe *mpipe, t_pipe **prompt);
t_envi    *init_our_env(char **env);
int    download_env_two(t_shell *our_shell, char **env);
int    download_env_one(t_shell *our_shell, char **env);
#endif
