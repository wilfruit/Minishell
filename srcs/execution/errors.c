/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:27:41 by wgaspar           #+#    #+#             */
/*   Updated: 2022/05/03 15:32:49 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wrap_strerror(void)
{
	char *msg;

	msg = strerror(errno);
	ft_putstr(msg);
	ft_putstr("\n");
	exit(errno);
}
