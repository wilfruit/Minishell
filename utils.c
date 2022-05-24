/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:21:22 by avaures           #+#    #+#             */
/*   Updated: 2022/05/24 18:25:10 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	forced_prompt(int sig)
{
	printf("\n");
	printf("mshell> ");
}

void	forced_continue(int sig)
{
//	rl_replace_line("", 0);
//	rl_on_new_line();
//	rl_redisplay();
}

int	control(void)
{
	signal(SIGINT, forced_prompt);
	signal(SIGQUIT, forced_continue);
}

void	free_token(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = -1;
	while (++utils.i < utils.nb_cmd)
	{
		utils.j = -1;
		while (++utils.j < (*prompt)[utils.i].nb_token)
		{
			free((*prompt)[utils.i].scmd[utils.j].value);
			(*prompt)[utils.i].scmd[utils.j].value = NULL;
		}
		free((*prompt)[utils.i].scmd);
	}
}

void	free_struct(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = -1;
	while (++utils.i < utils.nb_cmd)
	{
		free((*prompt)[utils.i].cmd);
		(*prompt)[utils.i].cmd = NULL;
	}
	free((*prompt));
}
