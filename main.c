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

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	*path;
	t_shell	shell_pack;
	t_manage_pipe	mpipe;
	t_pipe		*prompt;

	//	path = set_path(env);
	//	printf("%s\n", path);
	//shell_pack.env = download_env(env);
	//shell_pack.exports = download_env(env);
	//shell_pack.std_in = open(copy->redir.in, O_RDONLY);
	//shell_pack.std_out = open(copy->redir.out1, O_CREAT | O_RDWR | O_APPEND, 0644);
	//shell_pack.std_error = open(copy->redir.out2, O_CREAT | O_RDWR | O_APPEND, 0644);
	control();
	line = NULL;
	while (1)
	{
		line = readline( "mshell> " );
		if (check_line(&line) == NULL || all_pipe_cmd(&mpipe, line) == NULL)
			exit(0);
		set_struct(&line, mpipe, &prompt);
	//	minishell(&shell_pack);
		clean_manage(&mpipe, &prompt);
		free(line);
	}
	free(line);
	return (0);
}