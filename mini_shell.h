/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:45:56 by avaures           #+#    #+#             */
/*   Updated: 2022/05/03 16:49:00 by avaures          ###   ########.fr       */
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

void	*set_manage(t_manage_pipe *mpipe, char *line);
void	len_cmd_pipe(t_manage_pipe *mpipe, char *line);
int	size_cmd_tab(char *line);
char	*set_path(char **infos);
void	*all_pipe_cmd(t_manage_pipe *mpipe, char *line);
void	clean_manage(t_manage_pipe *mpipe);
#endif
