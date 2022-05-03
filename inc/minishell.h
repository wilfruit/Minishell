/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:17:24 by wgaspar           #+#    #+#             */
/*   Updated: 2022/05/03 16:36:41 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct t_satab
{
	char	**allpaths;
	char	**cells;
	char	**cmdargs;
	char	*cmdstat;
	char	*cmddyn;
	int		**pipe_fd;
	int		infile;
	int		outfile;
	int		cmdcount;
	pid_t	*c_pid;
}		t_exec;

// PIPE OPERATIONS

void	pipe_executionner(t_exec *data);

// GNL

char	*get_next_line(int fd);
char	*my_strchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);

// ERRORS

void	wrap_strerror(void);

// Execution Functions

int		ft_is_built_in(t_exec *data, int cmd_num);
void	ft_execve(t_exec *data, char *current_cmd);
void	ft_exec_built_in(t_exec *data, char **cmd);
void	ft_single_cmd(t_exec *data);

// Files redirections 

void	handle_outfile(t_exec *data);
void	handle_infile(t_exec *data);
void	handle_append(t_exec *data);

// Init

void    ft_init_data(t_exec *data, t_minishell *var);

// Dynamic parsing

void	parsing_cmd_bonus(t_exec *data, char *current_cmd);

#endif
