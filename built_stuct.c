/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_stuct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42->fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:03:46 by avaures           #+#    #+#             */
/*   Updated: 2022/05/18 19:54:50 by avaures          ###   ########.fr       */
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
		j = 0;
		while (utils.pipecmd[i][j])
		{
			(*prompt)[i].cmd[j] = utils.pipecmd[i][j];
			j++;
		}
		(*prompt)[i].cmd[j] = '\0';
	//	printf("%s\n", (*prompt)[i].cmd);
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
	//	printf("before\n");
		while ((*prompt)[utils.i].cmd[utils.j])
		{
			if ((*prompt)[utils.i].cmd[utils.j] == '\'')
			{
				utils.j++;
				while ((*prompt)[utils.i].cmd[utils.j] != '\'')
					utils.j++;
				utils.j++;
			}
			else if ((*prompt)[utils.i].cmd[utils.j] == '\"')
			{
				utils.j++;
				while ((*prompt)[utils.i].cmd[utils.j] != '\"')
					utils.j++;
				utils.j++;
			}
			else if ((is_redirection((*prompt)[utils.i].cmd[utils\
			.j]) == 1) || ((*prompt)[utils.i].cmd[utils.j] == ' '))
			{
				if (is_redirection((*prompt)[utils.i].cmd[utils.j]) == 1)
				{
					utils.j++;
					if (is_redirection((*prompt)[utils.i].cmd[utils.j]) == 1)
						utils.j++;
					(*prompt)[utils.i].nb_token++;
				}
				while ((*prompt)[utils.i].cmd[utils.j] == ' ')
						utils.j++;
				if ((*prompt)[utils.i].cmd[utils.j] && !\
				is_redirection((*prompt)[utils.i].cmd[utils.j]))
					(*prompt)[utils.i].nb_token++;
			}
			else
				utils.j++;
		}
	//	printf("after\n");
		(*prompt)[utils.i].scmd = malloc(sizeof(t_token) * ((*prompt)[utils.i].nb_token));
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
				(*prompt)[utils.i].scmd[utils.k].len_value = 0;
			if (is_redirection((*prompt)[utils.i].cmd[utils.j]))
			{
				while (is_redirection((*prompt)[utils.i].cmd[utils.j]))
				{
						(*prompt)[utils.i].scmd[utils.k].len_value++;
						utils.j++;
				}
				if ((*prompt)[utils.i].cmd[utils.j] != ' ')
					utils.k++;
			}
			while (((*prompt)[utils.i].cmd[utils.j] && 
			(*prompt)[utils.i].cmd[utils.j] != ' ') && 
			(utils.k < (*prompt)[utils.i].nb_token) && \
			is_redirection((*prompt)[utils.i].cmd[utils.j]) == 0)
			{	
				if ((*prompt)[utils.i].cmd[utils.j] == '\'')
				{
					utils.j++;
					while ((*prompt)[utils.i].cmd[utils.j] != '\'')
					{
						(*prompt)[utils.i].scmd[utils.k].len_value++;
						utils.j++;
					}
					utils.j++;
				}
				if ((*prompt)[utils.i].cmd[utils.j] == '\"')
				{
					utils.j++;
					while ((*prompt)[utils.i].cmd[utils.j] != '\"')
					{
						(*prompt)[utils.i].scmd[utils.k].len_value++;
						utils.j++;
					}
					utils.j++;
				}
				if ((*prompt)[utils.i].cmd[utils.j] && (*prompt)[utils.i].cmd[utils.j] != ' ')	
				{
					(*prompt)[utils.i].scmd[utils.k].len_value++;
					utils.j++;
				}
			}
			utils.k++;
		}
		utils.i++;
	}
	utils.i = 0;
	while (utils.i < utils.nb_cmd)
	{
		utils.j = 0;
		printf("command[%d]\n", utils.i);
		printf("-------------------------------------------------\n");
		while (utils.j < (*prompt)[utils.i].nb_token)
		{
			printf("size_token : %d\n", (*prompt)[utils.i].scmd[utils.j].len_value);
			utils.j++;
		}
		printf("-------------------------------------------------\n");
		utils.i++;
	}
	printf("-------------------------------------------------------------------------------------\n\n");
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
			while (((*prompt)[utils.i].cmd[utils.j] && 
			(*prompt)[utils.i].cmd[utils.j] != ' ') && 
			(utils.k < (*prompt)[utils.i].nb_token) && \
			is_redirection((*prompt)[utils.i].cmd[utils.j]) == 0)
			{	
				if ((*prompt)[utils.i].cmd[utils.j] == '\'')
				{
					utils.j++;
					while ((*prompt)[utils.i].cmd[utils.j] != '\'')
					{
						(*prompt)[utils.i].scmd[utils.k].value[v] = (*prompt)[utils.i].cmd[utils.j];
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
						v++;
						utils.j++;
					}
					utils.j++;
				}
				if (((*prompt)[utils.i].cmd[utils.j] != '\0') && (*prompt)[utils.i].cmd[utils.j] != ' ')	
				{
					(*prompt)[utils.i].scmd[utils.k].value[v] = (*prompt)[utils.i].cmd[utils.j];
					utils.j++;
					v++;
				}
			}
			utils.k++;
		//	printf("size_token :%d %d\n",utils.k, prompt[utils.i]->scmd[utils.k].len_value);
		}
		//printf("%d\n", utils.i);
		// printf("hey %d\n", .nb_token);
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
			utils.k++;
		}
		printf("-------------------------------------------------\n");
		printf("\n\n");
		utils.i++;
	}
}