/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_characters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:31:14 by avaures           #+#    #+#             */
/*   Updated: 2022/05/18 19:19:14 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	*len_cmd_pipe(t_manage_pipe *mpipe, char *line)
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

			if (line[r] != '\'')
				return (write(1, "invalid syntax\n", 15), NULL);
			mpipe->size++;
			r++;
		}
		else if (is_redirection(line[r]) == 1)
		{
			mpipe->size++;
			r++;
			if (is_redirection(line[r]) == 1)
			{
				if (line[r - 1] != line[r])
					return (write(1, "syntax error near unexpected token\n", 35), NULL);
				mpipe->size++;
				r++;
			}
			
		}
		else if (line[r] == '\"')
		{
			r++;
			mpipe->size++;
			while (line[r] && line[r] != '\"')
			{
				mpipe->size++;
				r++;
			}
			if (line[r] != '\"')
				return (write(1, "invalid syntax\n", 15), NULL);
			mpipe->size++;
			r++;
		}
		else if (line[r] == '|')
		{
			(*mpipe).size_cmd[cmd] = (*mpipe).size;
			mpipe->size = 0;
			cmd++;
			r++;
		}
		else
		{
			mpipe->size++;
			r++;
		}
	}
	mpipe->size_cmd[cmd] = mpipe->size;
}

void	*set_manage(t_manage_pipe *mpipe, char *line)
{	
	int	tmp;

	tmp = -1;
	mpipe->i = 0;
	mpipe->j = 0;
	mpipe->k = 0;
	mpipe->end = -1;
	mpipe->size = 0;
	mpipe->nb_cmd = size_cmd_tab(line);
	mpipe->size_cmd = ft_calloc(sizeof(int), mpipe->nb_cmd);
	mpipe->pipecmd = ft_calloc(sizeof(char *), mpipe->nb_cmd);
	if (!mpipe->size_cmd || !mpipe->pipecmd)
		return (NULL);
	while (++tmp < mpipe->nb_cmd)
		mpipe->size_cmd[tmp] = 0; 
	if (len_cmd_pipe(mpipe, line) == NULL)
		return (NULL);
	tmp = -1;
	while (++tmp < mpipe->nb_cmd)
	{
		printf("tmp : %d/ nb_cmd : %d/ lencmd : %d\n", tmp, mpipe->nb_cmd, mpipe->size_cmd[tmp]);
		mpipe->pipecmd[tmp] = ft_calloc(sizeof(char), (mpipe->size_cmd[tmp] + 1));
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
			(*mpipe).pipecmd[mpipe->i][mpipe->j] = line[l];
			mpipe->j++;
			l++;
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
	add_history(line);
	make_tab_cmd(mpipe, line);
}
void	clean_manage(t_manage_pipe *mpipe, t_pipe **prompt)
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
	free_token(*mpipe, prompt);
	free_struct(*mpipe, prompt);
}
