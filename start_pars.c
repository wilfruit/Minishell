/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:53:16 by avaures           #+#    #+#             */
/*   Updated: 2022/05/24 18:26:28 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*set_path(char **str)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", str[i], 5) != 0)
		i++;
	return (str[i] + 5);
}

int	help_size(int *i, char *line)
{
	while (line[*i] == ' ')
		*i += 1;
	if (line[*i] == '\0')
		return (0);
}

int	help_simple(int *i, char *line)
{
	*i += 1;
	while (line[*i] && line[*i] != '\'')
		*i += 1;
	return (0);
}

int	help_double(int *i, char *line)
{
	*i += 1;
	while (line[*i] && line[*i] != '\"')
		*i += 1;
	return (0);
}

int	size_cmd_tab(char *line)
{
	int	i;
	int	size;

	i = 0;
	size = 1;
	while (line[i])
	{
		if (line[i] == ' ')
			help_size(&i, line);
		if (line[i] == '\0')
			return (0);
		if (line[i] == '\'')
			help_simple(&i, line);
		if (line[i] == '\"')
			help_double(&i, line);
		if (line[i] == '|')
			size++;
		if (line[i])
			i++;
	}
	return (size);
}
