/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_stuct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42->fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:03:46 by avaures           #+#    #+#             */
/*   Updated: 2022/05/11 18:11:34 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h" 

int	set_struct(t_manage_pipe utils, t_pipe **prompt)
{
	int	i;
	int	j;

	i = -1;
	*prompt = malloc(sizeof(t_pipe) * utils.nb_cmd);
	if (!prompt)
		return (1);
	while (++i < utils.nb_cmd)
		(*prompt)[i].cmd = malloc(sizeof(char) * (utils.size_cmd[i] + 1));
	i = 0;
	while (i < utils.nb_cmd)
	{
		j = 0;
		while (utils.pipecmd[i][j])
		{
			(*prompt)[i].cmd[j] = utils.pipecmd[i][j];
			j++;
		}
		(*prompt)[i].cmd[j] = '\0';
		(*prompt)[i].len_cmd = utils.size_cmd[i];
		i++;
	}
	cmd_struct(utils, prompt);
	found_len_token(utils, prompt);
	set_token(utils, prompt);
	return (0);
}

void	*cmd_struct(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		(*prompt)[utils.i].nb_token = 1;
		if ((*prompt)[utils.i].cmd[utils.j] == ' ')
			while ((*prompt)[utils.i].cmd[utils.j] == ' ')
				utils.j++;
		while ((*prompt)[utils.i].cmd[utils.j])
		{
			if ((*prompt)[utils.i].cmd[utils.j] == ' ' && (utils.j != 0))
			{
				while ((*prompt)[utils.i].cmd[utils.j] == ' ')
					utils.j++;
				if ((*prompt)[utils.i].cmd[utils.j] != '\0')
					(*prompt)[utils.i].nb_token++;
			}
			utils.j++;
		}
		(*prompt)[utils.i].scmd = malloc(sizeof(t_token) * ((*prompt)[utils.i].nb_token));
		utils.i++;
	}
//	utils.i = 0;
//	while (utils.i < utils.nb_cmd)
//	{
//		printf("nb_token : %d\n", prompt[utils.i]->nb_token);
//		utils.i++;
//	}
}
void	*found_len_token(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		utils.k = 0;
		while ((*prompt)[utils.i].cmd[utils.j])
		{
			while ((*prompt)[utils.i].cmd[utils.j] == ' ')
				utils.j++;
			if ((*prompt)[utils.i].cmd[utils.j] != '\0')
			{
				(*prompt)[utils.i].scmd[utils.k].len_value = 0;
				while ((*prompt)[utils.i].cmd[utils.j] && ((*prompt)[utils.i].cmd[utils.j] != ' '))
				{
					(*prompt)[utils.i].scmd[utils.k].len_value++;
					utils.j++;
				}
			//	printf("size_token :%d %d\n",utils.k, prompt[utils.i]->scmd[utils.k].len_value);
				utils.k++;
			}
		}
		utils.i++;
	}
//	utils.i = 0;
//	while (utils.i < utils.nb_cmd)
//	{
//		utils.j = 0;
//		while (utils.j < prompt[utils.i]->nb_token)
//		{
//			printf("size_token : %d\n", prompt[utils.i]->scmd[utils.j].len_value);
//			utils.j++;
//		}
//		utils.i++;
//	}
}

void	*set_token(t_manage_pipe utils, t_pipe **prompt)
{
	int	v;

	utils.i = -1;
	while (++utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		while (utils.j < (*prompt)[utils.i].nb_token)
		{
	//		printf("size_token :%d\n", prompt[utils.i]->scmd[utils.j].len_value);
			(*prompt)[utils.i].scmd[utils.j].value = malloc(sizeof(char) * ((*prompt)[utils.i].scmd[utils.j].len_value + 1));
			utils.j++;
		}
	}
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		utils.k = 0;
		while ((*prompt)[utils.i].cmd[utils.j])
		{
			v = 0;
			while ((*prompt)[utils.i].cmd[utils.j] == ' ')
				utils.j++;
			if ((*prompt)[utils.i].cmd[utils.j] != '\0')
			{
				(*prompt)[utils.i].scmd[utils.k].len_value = 0;
				while ((*prompt)[utils.i].cmd[utils.j] && ((*prompt)[utils.i].cmd[utils.j] != ' '))
				{
					(*prompt)[utils.i].scmd[utils.k].value[v] = (*prompt)[utils.i].cmd[utils.j];
					v++;
					utils.j++;
				}
			//	printf("size_token :%d %d\n",utils.k, prompt[utils.i]->scmd[utils.k].len_value);
				utils.k++;
			}
		}
		utils.i++;
	}
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.k = 0;
		while (utils.k < (*prompt)[utils.i].nb_token)
		{
			printf("token : %s\n", (*prompt)[utils.i].scmd[utils.k].value);
			utils.k++;
		}
		utils.i++;
	}
}

