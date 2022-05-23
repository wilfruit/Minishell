/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:53:16 by avaures           #+#    #+#             */
/*   Updated: 2022/05/09 15:04:18 by avaures          ###   ########.fr       */
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

int	size_cmd_tab(char *line)
{
	int	i;
	int	size;

	i = 0;
	size = 1;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			while (line[++i] == ' ')
			{}
			if (line[i] == '\0')
				return (0);
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
		}
		if (line[i] == '|')
			size++;
		if (line[i])
			i++;
	}
	return (size);
}

t_envi    *init_our_env(char **env)
{
    t_envi    *cursor;

    cursor = malloc(sizeof(t_envi));
    cursor->str = ft_strdup(env[0]);
    cursor->next = NULL;
    return (cursor);
}

int    download_env_one(t_shell *our_shell, char **env)
{
    int    i;
    t_envi    *temp;
    t_envi    *cursor;

    if (!env || !env[0])
        return (1);
    i = 1;
    cursor = init_our_env(env);
    our_shell->env = cursor;
    while (env[i])
    {
        temp = malloc(sizeof(t_envi));
        if (!temp)
            return (1);
        temp->str = ft_strdup(env[i]);
        temp->next = NULL;
        cursor->next = temp;
        cursor = temp;
        i++;
    }
    return (0);
}

int    download_env_two(t_shell *our_shell, char **env)
{
    int    i;
    t_envi    *temp;
    t_envi    *cursor;

    if (!env || !env[0])
        return (1);
    i = 1;
    cursor = init_our_env(env);
    our_shell->exports = cursor;
    while (env[i])
    {
        temp = malloc(sizeof(t_envi));
        if (!temp)
            return (1);
        temp->str = ft_strdup(env[i]);
        temp->next = NULL;
        cursor->next = temp;
        cursor = temp;
        i++;
    }
    return (0);
}