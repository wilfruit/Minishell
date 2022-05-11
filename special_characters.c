/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_characters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:31:14 by avaures           #+#    #+#             */
/*   Updated: 2022/05/11 17:57:54 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	len_cmd_pipe(t_manage_pipe *mpipe, char *line)
{
	int	r;
	int	cmd;
	
	r = 0;
	cmd = 0;
	mpipe->size = 0;
	while (line[r])
	{
		if (line[r] == '\'')
		{
			r++;
			mpipe->size++;
			while (line[r] && line[r] != '\'')
			{
				mpipe->size++;
				r++;
			}
		}
		if (line[r] == '\"')
		{
			r++;
			mpipe->size++;
			while (line[r] && line[r] != '\'')
			{
				mpipe->size++;
				r++;
			}
		}
		if (line[r] == '|')
		{
			(*mpipe).size_cmd[cmd] = (*mpipe).size;
			mpipe->size = 0;
			cmd++;
			r++;
		}
		mpipe->size++;
		r++;
	}
	mpipe->size_cmd[cmd] = mpipe->size;
	return ;
}

void	*set_manage(t_manage_pipe *mpipe, char *line)
{	
	int	tmp;

	tmp = -1;
	mpipe->i = 0;
	mpipe->j = 0;
	mpipe->k = 0;
	mpipe->size = 0;
	mpipe->nb_cmd = size_cmd_tab(line);
	mpipe->size_cmd = malloc(sizeof(int) * mpipe->nb_cmd);
	mpipe->pipecmd = malloc(sizeof(char *) * mpipe->nb_cmd);
	if (!mpipe->size_cmd || !mpipe->pipecmd)
		return (NULL);
	while (++tmp < mpipe->nb_cmd)
		mpipe->size_cmd[tmp] = 0; 
	len_cmd_pipe(mpipe, line);
	tmp = -1;
	while (++tmp < mpipe->nb_cmd)
	{
		printf("tmp : %d/ nb_cmd : %d/ lencmd : %d\n", tmp, mpipe->nb_cmd, mpipe->size_cmd[tmp]);
		mpipe->pipecmd[tmp] = malloc(sizeof(char) * (mpipe->size_cmd[tmp] + 1));
		if (mpipe->pipecmd[tmp] == NULL)
			return (NULL);
	}
}
void	*make_tab_cmd(t_manage_pipe *mpipe, char *line)
{
	int	l;

	l = 0;
	mpipe->i = 0;
	while (mpipe->i < mpipe->nb_cmd)
	{
		mpipe->j = 0;
		while (mpipe->j < (*mpipe).size_cmd[mpipe->k])
		{
			if (line[l] == '\'' && line[l + 1] != '\'' && line[l + 1])
			{
				l++;
				(*mpipe).pipecmd[mpipe->i][mpipe->j] = line[l];
			}
			else if (line[l] == '\'' && line[l + 1] == '\'' && line[l + 2])
			{
				l += 2;
				(*mpipe).pipecmd[mpipe->i][mpipe->j] = line[l];
			}
			else if (line[l] == '\'' && line[l + 1] == '\0')
			{
				l++;
				(*mpipe).pipecmd[mpipe->i][mpipe->j] = '\0'; 
			}
			else
			{
				(*mpipe).pipecmd[mpipe->i][mpipe->j] = line[l];
				mpipe->j++;
				l++;
			}
		}
		l++;
		(*mpipe).pipecmd[mpipe->i][mpipe->j] = '\0';
		mpipe->i++;
		mpipe->k++;
	}
}
void	*all_pipe_cmd(t_manage_pipe *mpipe, char *line)
{
	if ((set_manage(mpipe, line)) == NULL)
		return (NULL);
	mpipe->i = 0;
	make_tab_cmd(mpipe, line);
}
void	clean_manage(t_manage_pipe *mpipe)
{
	int	tmp;

	tmp  = -1;
	free(mpipe->size_cmd);
	mpipe->size_cmd = NULL;
	while (++tmp < mpipe->nb_cmd)
	{
		free((mpipe->pipecmd[tmp]));
		mpipe->pipecmd[tmp] = NULL;
	}
	free(mpipe->pipecmd);
	mpipe->pipecmd = NULL;
}
