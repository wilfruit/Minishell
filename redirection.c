/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:39:12 by avaures           #+#    #+#             */
/*   Updated: 2022/05/17 09:59:16 by avaures          ###   ########.fr       */
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
	if (len_token == 1)
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

	i = 0;
	while (i < prompt->nb_token)
	{
		if (i == 0 && !is_redirection(prompt->scmd[0].value[0]))
			prompt->scmd[i].type = TOKEN_CMD;

		else if (i == 0)
			prompt->scmd[i].type = which_redirection(prompt->scmd[i].value[0], prompt->scmd[i].len_value);

		if (prompt->scmd[0].type == TOKEN_CMD)
			prompt->scmd[i].type == TOKEN_ARG;
			
		if (is_redirection(prompt->scmd[i - 1].value[0]))
			prompt->scmd[i].type == TOKEN_FILE;
		
	}

	
}
