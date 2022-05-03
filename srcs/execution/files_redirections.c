/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:12:55 by wgaspar           #+#    #+#             */
/*   Updated: 2022/05/03 15:27:34 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_wrongfile(char *file)
{
	ft_putstr("minishell: ");
	ft_putstr(file);
	ft_putstr(": No such file or directory\n");
	return (0);
}

void	handle_append(t_exec *data)
{
	int	outfile_fd;
	
	outfile_fd = open(data->redirs->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (outfile_fd < 0)
	{
		ft_clean_all(data);
		wrap_strerror();
		exit(errno);
	}
}

void	handle_infile(t_exec *data)
{
	int	infile_fd;

	if (access(data->redirs->infile, F_OK) == 0)
		infile_fd = open(data->redirs->infile, O_RDONLY);
	else
		infile_fd = ft_wrongfile(data->redirs->infile);	
	//peut-être faut-il kill le processus si le fichier est mauvais
}

void	handle_outfile(t_exec *data)
{
	int	outfile_fd;

	outfile_fd = open(data->redirs->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		ft_clean_all(data);
		wrap_strerror();
	}
}