/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:24:12 by avaures           #+#    #+#             */
/*   Updated: 2022/05/27 15:10:44 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    *cpt_pipe(int *r, int *cmd, t_manage_pipe *mpipe, char *line)
{
		(*mpipe).size_cmd[*cmd] = (*mpipe).size;
		mpipe->size = 0;
		*cmd += 1;
		*r += 1;
}
void	*len_redir(int *r, t_manage_pipe *mpipe, char *line)
{
	mpipe->size += 1;
	*r += 1;
	if (is_redirection(line[*r]) == 1)
	{
		if (line[*r - 1] != line[*r] || line[*r + 1] == line[*r])
			return (write(1, "syntax error near unexpected token\n", 35), \
			NULL);
		mpipe->size += 1;
		*r += 1;
	}	
}

void	*len_d_quote(int *r, t_manage_pipe *mpipe, char *line)
{
	if (line[*r] == '\"')
    {
        *r += 1;
	    mpipe->size += 1;
	    while (line[*r] && line[*r] != '\"')
	    {
		    mpipe->size += 1;
	    	*r += 1;
	    }
	    if (line[*r] != '\"')
	    	return (write(1, "invalid syntax\n", 15), NULL);
	    mpipe->size += 1;
	    *r += 1;
    }
    else
    {
        *r += 1;
	    mpipe->size += 1;
	    while (line[*r] && line[*r] != '\'')
	    {
		    mpipe->size += 1;
	    	*r += 1;
	    }
	    if (line[*r] != '\'')
	    	return (write(1, "invalid syntax\n", 15), NULL);
	    mpipe->size += 1;
	    *r += 1;
    }
}