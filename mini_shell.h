/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:45:56 by avaures           #+#    #+#             */
/*   Updated: 2022/05/13 14:44:36 by avaures          ###   ########.fr       */
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

typedef struct s_manage_pipe
{
	int	i;
	int	j;
	int	k;
	int	size;
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

int	is_redirection(char c);
int	set_struct(t_manage_pipe utils, t_pipe **prompt);
void	*cmd_struct(t_manage_pipe utils, t_pipe **prompt);
void	*found_len_token(t_manage_pipe utils, t_pipe **prompt);
void	*set_token(t_manage_pipe utils, t_pipe **prompt);
void	*make_tab_cmd(t_manage_pipe *mpipe, char *line);
void	*set_manage(t_manage_pipe *mpipe, char *line);
void	*len_cmd_pipe(t_manage_pipe *mpipe, char *line);
int	size_cmd_tab(char *line);
char	*set_path(char **infos);
void	*all_pipe_cmd(t_manage_pipe *mpipe, char *line);
void	clean_manage(t_manage_pipe *mpipe);
#endif
