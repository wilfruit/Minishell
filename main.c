/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:35:38 by avaures           #+#    #+#             */
/*   Updated: 2022/05/18 16:13:55 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini_shell.h"

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	*path;
	int i = 0;
	t_manage_pipe	mpipe;
	t_pipe		*prompt;

//	path = set_path(env);
//	printf("%s\n", path);
	control();
	line = NULL; 
	while (1)
	//	readline( "mshell> " );
	{
		printf("%s\n", line = readline( "mshell> " ));
		if (all_pipe_cmd(&mpipe, line) == NULL)
			return (0);
		if (set_struct(&line, mpipe, &prompt) == 0)
			clean_manage(&mpipe, &pipe);
	//	clean_manage(&mpipe);
//		set_manage(&mpipe, line);
//		while (++i < mpipe.nb_cmd)
//			printf("command n%d : %s\n",i, mpipe.pipecmd[i]);
//		printf("nombre de commande : %d\n", size_cmd_tab(line));
	}
	free(line);
	return (0);
}

