/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:39:12 by avaures           #+#    #+#             */
/*   Updated: 2022/05/16 18:25:22 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
int	which_redirection(char c, int len_token)
{
	if (len == 1)
	{
		if (c == '>')
			return (TOKEN_OUTPUT_REDIRECTION);
		else
			return (TOKEN_INTPUT_REDIRECTION);
	}
	else
	{
		if (c == '>')
			return (TOKEN_OUTPUT_ERROR_EDIRECTION);
		else
			return (TOKEN_INTPUT_DELIMITER_REDIRECTION);
	}
	return (0);
}
void	*determine_type(t_pipe *prompt)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < prompt->nb_token)
	{
		if (i == 0 && !is_redirection(prompt->scmd[i]->value[j]))
			prompt->scmd[i]->type = TOKEN_CMD;

		else if (i == 0)
			prompt->scmd[i]->type = which_redirection(prompt->scmd[i]->value[j]);

	}

	
}
