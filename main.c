/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:35:38 by avaures           #+#    #+#             */
/*   Updated: 2022/05/11 15:16:47 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini_shell.h"

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	*path;
	t_manage_pipe	mpipe;
	t_pipe		*prompt;

//	path = set_path(env);
//	printf("%s\n", path);
	while (1)
	//	readline( "mshell> " );
	{
		int	i = -1;
		printf("%s\n", line = readline( "mshell> " ));
		all_pipe_cmd(&mpipe, line);
		set_struct(mpipe, &prompt);
//		set_manage(&mpipe, line);
//		while (++i < mpipe.nb_cmd)
//			printf("command n%d : %s\n",i, mpipe.pipecmd[i]);
		clean_manage(&mpipe);
//		printf("nombre de commande : %d\n", size_cmd_tab(line));
	}
	free(line);
	return (0);
}
