/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legible_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:05:29 by avaures           #+#    #+#             */
/*   Updated: 2022/05/24 12:06:13 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
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
			(*prompt)[utils.i].scmd[utils.j].value = ft_calloc(sizeof(char), ((*prompt)[utils.i].scmd[utils.j].len_value + 1));
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
			if (is_redirection((*prompt)[utils.i].cmd[utils.j]))
			{
				while (is_redirection((*prompt)[utils.i].cmd[utils.j]))
				{
						(*prompt)[utils.i].scmd[utils.k].value[v] = (*prompt)[utils.i].cmd[utils.j];
						utils.j++;
						v++;
				}
				if ((*prompt)[utils.i].cmd[utils.j] != ' ')
				{
					utils.k++;
					v = 0;
				}
			}
			if ((*prompt)[utils.i].cmd[utils.j] == '$')
			{
				(*prompt)[utils.i].scmd[utils.k].is_dollar = DOLLAR_MACRO;
				(*prompt)[utils.i].scmd[utils.k].value[v] = (*prompt)[utils.i].cmd[utils.j];
				utils.j++;
				v++;
			}
			while (((*prompt)[utils.i].cmd[utils.j] && 
			(*prompt)[utils.i].cmd[utils.j] != ' ') && 
			(utils.k < (*prompt)[utils.i].nb_token) && \
			!is_redirection((*prompt)[utils.i].cmd[utils.j])\
			&& ((*prompt)[utils.i].cmd[utils.j] != '$'))
			{	
				if ((*prompt)[utils.i].cmd[utils.j] == '\'')
				{
					utils.j++;
					while ((*prompt)[utils.i].cmd[utils.j] != '\'')
					{
						(*prompt)[utils.i].scmd[utils.k].value[v] = (*prompt)[utils.i].cmd[utils.j];
						if ((*prompt)[utils.i].cmd[utils.j] == '$')
							(*prompt)[utils.i].scmd[utils.k].is_dollar = DOLLAR_NO;
						v++;
						utils.j++;
					}
					utils.j++;
				}
				if ((*prompt)[utils.i].cmd[utils.j] == '\"')
				{
					utils.j++;
					while ((*prompt)[utils.i].cmd[utils.j] != '\"')
					{
						(*prompt)[utils.i].scmd[utils.k].value[v] = (*prompt)[utils.i].cmd[utils.j];
						if ((*prompt)[utils.i].cmd[utils.j] == '$')
							(*prompt)[utils.i].scmd[utils.k].is_dollar = DOLLAR_MACRO;
						v++;
						utils.j++;
					}
					utils.j++;
				}
				if (((*prompt)[utils.i].cmd[utils.j] != '\0') && (*prompt)[utils.i].cmd[utils.j] != ' ')	
				{
					if ((*prompt)[utils.i].cmd[utils.j] == '$')
						(*prompt)[utils.i].scmd[utils.k].is_dollar = DOLLAR_MACRO;
					(*prompt)[utils.i].scmd[utils.k].value[v] = (*prompt)[utils.i].cmd[utils.j];
					utils.j++;
					v++;
				}
			}
			utils.k++;
		}
		determine_type(&(*prompt)[utils.i]);
		utils.i++;
	}
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.k = 0;
		printf("commande[%d]\n", utils.i);
		printf("-------------------------------------------------\n");
		while (utils.k < (*prompt)[utils.i].nb_token)
		{
			printf("token[%d] : %s\n",utils.k, (*prompt)[utils.i].scmd[utils.k].value);
			printf("is_dollar : %d\n", (*prompt)[utils.i].scmd[utils.k].is_dollar);
			utils.k++;
		}
		printf("-------------------------------------------------\n");
		printf("\n\n");
		utils.i++;
	}
}