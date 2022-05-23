/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:35:38 by avaures           #+#    #+#             */
/*   Updated: 2022/05/18 19:21:31 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini_shell.h"

void    print_linked_list(t_envi *our_env)
{
    while (our_env)
    {
        printf("%s\n", our_env->str);
        our_env = our_env->next;
    }
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	*path;
	t_shell	shell_pack;
	t_manage_pipe	mpipe;
	t_pipe		*prompt;

	download_env_one(&shell_pack, env);
	download_env_two(&shell_pack, env);
//	print_linked_list(shell_pack.env);
	control();
	line = NULL;
	while (1)
	{
		line = readline( "mshell> " );
		if (check_line(&line) == NULL)
			exit(0);
		if (all_pipe_cmd(&mpipe, line) != NULL)
		{
			set_struct(&line, mpipe, &prompt);
			clean_manage(&mpipe, &prompt);
			//	minishell(&shell_pack);
		}
		free(line);
	}
	free(line);
	return (0);
}