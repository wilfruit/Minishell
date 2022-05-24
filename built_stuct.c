/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_stuct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:03:46 by avaures           #+#    #+#             */
/*   Updated: 2022/05/24 17:53:56 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h" 

int	set_struct(char **line, t_manage_pipe utils, t_pipe **prompt)
{
	int	i;
	int	j;

	i = -1;
	*prompt = ft_calloc(sizeof(t_pipe), utils.nb_cmd);
	if (!prompt)
		return (1);
	while (++i < utils.nb_cmd)
		(*prompt)[i].cmd = ft_calloc(sizeof(char), (utils.size_cmd[i] + 1));
	i = 0;
	while (i < utils.nb_cmd)
	{
		j = -1;
		while (utils.pipecmd[i][++j])
			(*prompt)[i].cmd[j] = utils.pipecmd[i][j];
		(*prompt)[i].cmd[j] = '\0';
		(*prompt)[i].len_cmd = utils.size_cmd[i];
		i++;
	}
	cmd_struct(utils, prompt);
	found_len_token(utils, prompt);
	set_token(utils, prompt);
	return (0);
}

void	*more_help_cmd_struct(int *nb_cmd, int *len_cmd, t_pipe **prompt)
{
	if (is_redirection((*prompt)[*nb_cmd].cmd[*len_cmd]) == 1)
	{
		*len_cmd += 1;
		if (is_redirection((*prompt)[*nb_cmd].cmd[*len_cmd]) == 1)
			*len_cmd += 1;
		(*prompt)[*nb_cmd].nb_token++;
	}
	while ((*prompt)[*nb_cmd].cmd[*len_cmd] == ' ')
		*len_cmd += 1;
	if ((*prompt)[*nb_cmd].cmd[*len_cmd] && !\
	is_redirection((*prompt)[*nb_cmd].cmd[*len_cmd]) \
	&& (*prompt)[*nb_cmd].cmd[*len_cmd] != '$')
		(*prompt)[*nb_cmd].nb_token++;
}

void	*last_help_cmd_struct(int *nb_cmd, int *len_cmd, t_pipe **prompt)
{
	if (*len_cmd > 0)
		(*prompt)[*nb_cmd].nb_token++;
	while ((*prompt)[*nb_cmd].cmd[*len_cmd] && \
	(*prompt)[*nb_cmd].cmd[*len_cmd] != ' '\
	&& (*prompt)[*nb_cmd].cmd[*len_cmd] != '\'' && \
	(*prompt)[*nb_cmd].cmd[*len_cmd] != '\"'\
	&& !is_redirection((*prompt)[*nb_cmd].cmd[*len_cmd]))
		*len_cmd += 1;
}

void	*help_cmd_struct(int nb_cmd, int len_cmd, t_pipe **prompt)
{
	while ((*prompt)[nb_cmd].cmd[len_cmd])
	{
		if ((*prompt)[nb_cmd].cmd[len_cmd] == '\'')
		{
			len_cmd++;
			while ((*prompt)[nb_cmd].cmd[len_cmd] != '\'')
				len_cmd++;
			len_cmd++;
		}
		else if ((*prompt)[nb_cmd].cmd[len_cmd] == '\"')
		{
			len_cmd++;
			while ((*prompt)[nb_cmd].cmd[len_cmd] != '\"')
				len_cmd++;
			len_cmd++;
		}
		else if ((is_redirection((*prompt)[nb_cmd].cmd[len_cmd]) \
		== 1) || ((*prompt)[nb_cmd].cmd[len_cmd] == ' '))
			more_help_cmd_struct(&nb_cmd, &len_cmd, prompt);
		else if ((*prompt)[nb_cmd].cmd[len_cmd] == '$')
			last_help_cmd_struct(&nb_cmd, &len_cmd, prompt);
		else
			len_cmd++;
	}
}

void	*cmd_struct(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		(*prompt)[utils.i].nb_token = 1;
		if (is_redirection((*prompt)[utils.i].cmd[utils.j]) == 1)
		{
			(*prompt)[utils.i].nb_token++;
			while (is_redirection((*prompt)[utils.i].cmd[utils.j]) == 1)
				utils.j++;
			if (!(*prompt)[utils.i].cmd[utils.j])
				(*prompt)[utils.i].nb_token = 1;
		}
		while ((*prompt)[utils.i].cmd[utils.j] == ' ')
				utils.j++;
		help_cmd_struct(utils.i, utils.j, prompt);
		(*prompt)[utils.i].scmd = malloc(sizeof(t_token) * \
		((*prompt)[utils.i].nb_token));
		utils.i++;
	}
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		printf("command[%d]\n", utils.i);
		printf("-------------------------------------------------\n");
		printf("nb_token : %d\n", (*prompt)[utils.i].nb_token);
		printf("-------------------------------------------------\n");
		printf("\n\n");
		utils.i++;
	}
	printf("-------------------------------------------------------------------------------------\n\n");
}