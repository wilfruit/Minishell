/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:21:22 by avaures           #+#    #+#             */
/*   Updated: 2022/05/18 18:00:55 by avaures          ###   ########.fr       */
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
		printf("nb_command : %d\n", utils.i);
		utils.j = -1;
		printf("nb_tokkkk : %d\n", (*prompt)[utils.i].nb_token);
		while (++utils.j < (*prompt)[utils.i].nb_token)
		{
			printf("nb_token : %d\n", utils.j);
			free((*prompt)[utils.i].scmd[utils.j].value);
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
/*
int main(void)
{
    char *buf = malloc(sizeof(char) * 500);
    size_t size = 500;
    int nb = getline(&buf, &size, stdin);
    if (nb == -1)
        printf("CTRL + D captured\n");
    free(buf);
    return (0);
}

int  main(void)
{
    signal(SIGINT, forced_exit);

     while (1)
     {
     }
    return 0;
}*/
/*
free(*line);
if (mpipe->end && isatty(0))
	*line = readline("mshell> ");
*/
