/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:53:22 by avaures           #+#    #+#             */
/*   Updated: 2022/05/02 14:53:51 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	valid_arg(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	if (str[i] == '-')
		return (1);
	while (str[i])
	{
		if (str[i] >= '0' && '9' >= str[i])
			++i;
		else
			return (1);
	}
	return (0);
}

int	check_overflow(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 11)
		return (1);
	if (ft_strlen(str) == 11)
	{
		if (str[0] != '-')
			return (1);
		if (ft_strcmp(&str[1], "2147483648") != 0)
			return (1);
	}
	if (ft_strlen(str) == 10)
		if (ft_strcmp(str, "2147483647") > 0)
			return (1);
	return (0);
}

int	init_value(char **arg, int nb_arg)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (nb_arg < 5 || nb_arg > 6)
		return (1);
	while (i < nb_arg - 1)
	{
		if (valid_arg(arg[j]) == 1 || check_overflow(arg[j]) == 1)
			return (1);
		i++;
		j++;
	}
	return (0);
}

/*
int main(int argc, char **argv)
{

	int	*tab;

	if (argc == 1)
		return (ft_printf("invalid number of argument\n"));
	if (argc == 2)
		tab = get_tab_long(argv, argc);
	else
		tab = get_tab(argv, argc);
	if (!tab)
		return (1);
	return (0);
}
*/
