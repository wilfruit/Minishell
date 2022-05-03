/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:13:13 by wgaspar           #+#    #+#             */
/*   Updated: 2022/05/03 14:45:02 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_operator(t_minishell *data)
{
	t_exec	exec_data;

	ft_init_data(&exec_data);
	if (token_exists('<') || token_exists('>') || token_exists('<<') || token_exists('>>'))
		ft_redirect(&exec_data);
	if (token_exists('SINGLE_COMMAND'))
		ft_single_cmd(&exec_data);
	if (token_exists('|'))
		pipe_executionner(&exec_data);
	exit(EXIT_SUCCESS);
}
