#include "../inc/minishell.h"

static void	wait_all(pipex_datab *data)
{
	int	i;

	i = 0;
	while (i < data->cmdcount)
	{
		waitpid(data->c_pid[i], 0, 0);
		i++;
	}
}

static void	child_first(t_exec *data, char **env)
{
	pipe(data->pipe_fd[0]);
	data->c_pid[0] = fork();
	if (data->c_pid[0] < 0)
		return (perror("Fork : ");
	if (data->c_pid[0] == 0)
	{
		close(data->pipe_fd[0][0]);
		if (data->is_here_doc == 0 && data->redir_infile == 1)
			dup2(data->infile, STDIN_FILENO);
		dup2(data->pipe_fd[0][1], STDOUT_FILENO);
		if (data->is_here_doc == 0 && data->redir_infile == 1)
			close(data->infile);
		close(data->pipe_fd[0][1]);
		ft_execve(data, data->cells[0]);
	}
	else
	{
		if (data->is_here_doc == 0)
			close(data->infile);
		close(data->pipe_fd[0][1]);
	}
}

static void	intermediate_child(t_exec *data, char *cmd, char **env, int n)
{
	pipe(data->pipe_fd[n]);
	data->c_pid[n] = fork();
	if (data->c_pid[n] < 0)
		return (perror("Fork : "));
	if (data->c_pid[n] == 0)
	{
		close(data->pipe_fd[n][0]);
		dup2(data->pipe_fd[n - 1][0], STDIN_FILENO);
		dup2(data->pipe_fd[n][1], STDOUT_FILENO);
		close(data->pipe_fd[n - 1][0]);
		close(data->pipe_fd[n][1]);
		ft_execve(data, data->cells[n]);
	}
	else
	{
		close(data->pipe_fd[n - 1][0]);
		close(data->pipe_fd[n][1]);
	}
}

static void	last_child(pipex_datab *data, char *cur_cmd, char **env, int n)
{
	data->c_pid[n] = fork();
	if (data->c_pid[n] < 0)
		return (perror("Fork :"));
	if (data->c_pid[n] == 0)
	{
		close(data->pipe_fd[n - 1][1]);
		dup2(data->pipe_fd[n - 1][0], STDIN_FILENO);
		dup2(data->outfile, STDOUT_FILENO);
		close(data->pipe_fd[n - 1][0]);
		close(data->outfile);
		ft_execve(data, data->cells[n]);
	}
	else
	{
		close(data->outfile);
		close(data->pipe_fd[n - 1][0]);
	}
}

void	pipe_executionner(t_exec *data)
{
	int	pipe_nb;

	i = 1;
	child_first(data);
	while (pipe_nb < data->cmd_count)
	{
		intermediate_child(data, data->cmd[pipe_nb - 1], data->env, pipe_nb);
		pipe_nb++;
	}
	last_child(data, data->cmd[pipe_nb], env, pipe_nb);
	wait_all(data);
}