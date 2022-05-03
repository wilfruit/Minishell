/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:53:16 by avaures           #+#    #+#             */
/*   Updated: 2022/05/03 16:51:24 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
char	*set_path(char **str)
{
	int	i;

	i = 0;
	while(ft_strncmp("PATH=", str[i], 5) != 0)
		i++;
	return (str[i] + 5);
}

int	size_cmd_tab(char *line)
{
	int	i;
	int	size;

	i = 0;
	size = 1;
	while (line[i])
	{	
		if (/*i > 0 && (line[i] == ' ' && line[i - 1] != ' ') ||*/ line[i] == '|')
			size++;
		i++;
	}
	return (size);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	*path;
	t_manage_pipe mpipe;

	path = set_path(env);
	printf("%s\n", path);
	while (1)
	//	readline( "mshell> " );
	{
		int	i = -1;
		printf("%s\n", line = readline( "mshell> " ));
		all_pipe_cmd(&mpipe, line);
//		set_manage(&mpipe, line);
		while (++i < mpipe.nb_cmd)
			printf("command n%d : %s\n",i, mpipe.pipecmd[i]);
		clean_manage(&mpipe);
//		printf("nombre de commande : %d\n", size_cmd_tab(line));
	}
	free(line);
	return (0);
}
