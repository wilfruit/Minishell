/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:45:56 by avaures           #+#    #+#             */
/*   Updated: 2022/05/20 14:27:33 by avaures          ###   ########.fr       */
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
# include "./libft/libft.h"
#include <signal.h>

# define TOKEN_ERROR -1
# define TOKEN_CMD 0
# define TOKEN_ARG 1
# define TOKEN_OUTPUT_REDIRECTION 2
# define TOKEN_OUTPUT_APPEND_EDIRECTION 3
# define TOKEN_INTPUT_REDIRECTION 4
# define TOKEN_INTPUT_HEREDOC_REDIRECTION 5
# define TOKEN_FILE 6
# define TOKEN_LIMITER 7

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

typedef struct	s_shell
{
	int	exit_end;
	int	std_in;
	int	std_out;
	int	std_error;
	t_pipe	*token;
//	t_envi	*env;
//	t_envi	*exports;
}		t_shell;

void	forced_prompt(int sig);
void	forced_continue(int sig);
char *check_line(char **line);
int		control(void);
void	free_struct(t_manage_pipe utils, t_pipe **prompt);
void	free_token(t_manage_pipe utils, t_pipe **prompt);
int		is_redirection(char c);
int		set_struct(char **line, t_manage_pipe utils, t_pipe **prompt);
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
#endif
