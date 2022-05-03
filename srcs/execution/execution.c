/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:33:59 by wgaspar           #+#    #+#             */
/*   Updated: 2022/05/03 16:31:00 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_fill_builtin_tab(char **tab)
{
	tab[0] = "echo";
	tab[1] = "cd";
	tab[2] = "pwd";
	tab[3] = "export";
	tab[4] = "unset";
	tab[5] = "env";
	tab[6] = "exit";
	tab[7] = "\0";
}

int	ft_is_built_in(t_exec *data, int cmd_num)
{
	char **built_tab;
	char *cmd;
	int	i;

	i = 0;
	cmd = data->cmds[cmd_num];
	built_tab = (char **)malloc(sizeof(char *) * 8);
	if (!built_tab)
		perror("malloc :");
	ft_fill_builtin_tab(built_tab);
	while (built_in[i] != '\0')
	{
		if (strncmp(built_tab[i], cmd, ft_strlen(built_tab[i]))
		{
			free(built_tab);
			return(1);
		}
		i++;
	}
	free(cmd);
	free(built_tab);
	return(0);
}

void	ft_execve(t_exec *data, char *current_cmd)
{
	int	i;

	i = -1;
	parsing_cmd_bonus(data, current_cmd);
	while (data->allpaths[++i])
	{
		if (is_pathed(data->cmdargs[0]) == -1)
			data->cmddyn = ft_strjoin(data->allpaths[i], data->cmdstat);
		else
			data->cmdyn = data->cmdargs[0];
		if (access(data->cmddyn, F_OK) == 0)
			execve(data->cmddyn, data->cmdargs, data->env);
		free(data->cmddyn);
	}
	ft_putstr("minishell : ");
	ft_putstr(data->cmdstat);
	ft_putstr(": command not found\n");
	ft_small_clean(data);
	exit(127);
}

void	ft_exec_built_in(t_exec *data, char **cmd)
{
	if (!strncmp(cmd[0], "echo"))
		ft_echo(cmd[1]);
	if (!strncmp(cmd[0], "cd"))
		ft_cd(cmd[1]);
	if (!strncmp(cmd[0], "pwd"))
		ft_pwd();
	if (!strncmp(cmd[0], "export"))
		ft_export();
	if (!strncmp(cmd[0], "unset"))
		ft_unset();
	if (!strncmp(cmd[0], "env"))
		ft_unset();
	if (!strncmp(cmd[0], "exit"))
		ft_exit();
}

void	ft_single_cmd(t_exec *data)
{
	if (!ft_is_built_in(data->cells[0]))
		ft_execve(data, data->cells[0]);
	else
		ft_exec_built_in(data, data->cells[0]);
}