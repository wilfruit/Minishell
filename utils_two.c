/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:43:39 by avaures           #+#    #+#             */
/*   Updated: 2022/05/24 18:24:09 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_envi	*init_our_env(char **env)
{
	t_envi	*cursor;

	cursor = malloc(sizeof(t_envi));
	cursor->str = ft_strdup(env[0]);
	cursor->next = NULL;
	return (cursor);
}

int	download_env_one(t_shell *our_shell, char **env)
{
	int		i;
	t_envi	*temp;
	t_envi	*cursor;

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

int	download_env_two(t_shell *our_shell, char **env)
{
	int		i;
	t_envi	*temp;
	t_envi	*cursor;

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
