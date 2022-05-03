/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:45:17 by wgaspar           #+#    #+#             */
/*   Updated: 2022/05/03 16:35:51 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

	
static void	child_doc(char *limiter, int *fd)
{
	char	*str;

	str = NULL;
	close(fd[0]);
	while(1)
	{
		write(1, "> ", 2);
		str(get_next_line(0));
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
		{
			exit(EXIT_SUCCESS);
			free(str);
		}
		write(fd[1], str, ft_strlen(str));
		free(str);
	}
}

static void	handle_here_doc(t_minishell *data)
{
	pid_t	child;
	int	fd[2];
	char	*limiter;

	limiter = ft_strdup(data->redirs->limiter);
	if (!limiter)
		perror("malloc : ");
	pipe(fd);
	child = fork();
	if (child < 0)
		return (perror("Fork : ");
	if (child == 0)
	{
		child_doc(limiter, fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(child, NULL, 0);
	}
}

void	ft_redirect(t_exec *exec_data)
{
	if (data->is_here_doc)
		handle_here_doc(&exec_data);
	else if (data->is_infile_redir);
		handle_infile(&exec_data)
	if (data->is_append)
		handle_append(&exec_data);
	if (data->is_outfile)
		handle_outfile(&exec_data);		
}
