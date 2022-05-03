/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_characters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:31:14 by avaures           #+#    #+#             */
/*   Updated: 2022/05/03 17:46:32 by avaures          ###   ########.fr       */
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
	while (line[r] && cmd < mpipe->nb_cmd)
	{
		while (line[r] && line[r] != '|')
		{
			mpipe->size++;
			r++;
		}
		mpipe->size_cmd[cmd] = mpipe->size;
		cmd++;
		mpipe->size = 0;
		if (line[r])
			r++;
	}
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
	if((mpipe->size_cmd = (int *)malloc(sizeof(int) * mpipe->nb_cmd)) == NULL)
		return (NULL);
	len_cmd_pipe(mpipe, line);
//	while (++tmp < mpipe->nb_cmd)
//	{
//		printf("lencmd : %d\n", mpipe->size_cmd[tmp]);
//	}
	if ((mpipe->pipecmd = malloc(sizeof(char) * mpipe->nb_cmd))  == NULL)
		return (NULL);
	while (++tmp < mpipe->nb_cmd)
	{
		printf("tmp : %d/ nb_cmd : %d/ lencmd : %d\n", tmp, mpipe->nb_cmd, mpipe->size_cmd[tmp]);
		if ((mpipe->pipecmd[tmp] = malloc(sizeof(char) * mpipe->size_cmd[tmp] + 1)) == NULL)
			return (NULL);
	}
	printf("ici\n");
}

void	*all_pipe_cmd(t_manage_pipe *mpipe, char *line)
{

	if ((set_manage(mpipe, line)) == NULL)
		return (NULL);
	mpipe->i = 0;
	while (line[mpipe->i])
	{
		mpipe->j = 0;
		while (line[mpipe->i] && line[mpipe->i] != '|')
		{
			mpipe->pipecmd[mpipe->k][mpipe->j] = line[mpipe->i];
			mpipe->i++;
			mpipe->j++;
		}
		mpipe->pipecmd[mpipe->k][mpipe->j + 1] = '\0';
		mpipe->i++;
		mpipe->k++;
	}
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
