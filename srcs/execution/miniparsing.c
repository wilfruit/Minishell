#include "../inc/minishell.h"

void	parsing_cmd_bonus(t_exec *data, char *current_cmd)
{
	data->cmdargs = ft_split(current_cmd, ' ');
	data->cmdstat = data->cmdargs[0];
	data->cmdstat = ft_strjoin("/", data->cmdstat);
}