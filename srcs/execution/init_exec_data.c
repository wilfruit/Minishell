#include "../inc/minishell.h"

static void	malloc_childs(t_exec *data)
{
	data->c_pid = (pid_t *)malloc(sizeof(pid_t) * data->cmdcount);
	if (!data->c_pid)
		wrap_strerror();
}

static void	malloc_pipes(t_exec *data)
{
	int	i;

	i = 0;
	data->pipe_fd = (int **)malloc(sizeof(int *) * (data->cmdcount - 1));
	if (!data->pipe_fd)
		wrap_strerror();
	while (i < data->cmdcount - 1)
	{
		data->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipe_fd[i])
			wrap_strerror();
		i++;
	}	
}

void    ft_init_data(t_exec *data, t_minishell *var)
{
    exec_data = malloc(sizeof(t_exec *));
    if (!exec_data)
        wrap_strerror();
    data->cmdcount = var->cell_nb;
    data->infile = 0;
    data->outfile = 0;
    data->cmddyn = NULL;
    data->cmdstat = NULL;
    data->env = var->env;
    if(data->cmdcount > 1)
    {
        malloc_childs(data);
        malloc_pipes(data);
    }
    data->allpaths = ft_split(data->path_in_env, ":");
    data->cells = var->cells;
    //free quelque chose ?
}
