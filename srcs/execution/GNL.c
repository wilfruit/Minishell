#include "../inc/minishell.h"

static char	*ft_substr_storage(char *stored, char *temp, int i, int j)
{
	i++;
	while (stored[i] != '\0')
	{
		temp[j] = stored[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

static char	*update_storage(char *stored)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (stored[i] != '\n' && stored[i] != '\0')
		i++;
	if (stored[i] == '\0')
	{
		free(stored);
		return (NULL);
	}
	temp = malloc((ft_strlen(stored) - i + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	temp = ft_substr_storage(stored, temp, i, j);
	free(stored);
	return (temp);
}

static char	*ft_checkstorage(int fd, char *stored)
{
	char	*buf;
	int		lus;

	lus = 1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (((lus != 0) && !my_strchr(stored, '\n')))
	{
		lus = read(fd, buf, BUFFER_SIZE);
		if (lus == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[lus] = '\0';
		stored = gnl_strjoin(stored, buf);
	}
	free (buf);
	return (stored);
}

static char	*ft_allocandfeelline(char *stored, int i, int j)
{
	char	*retline;

	if (!stored[0])
		return (NULL);
	while (stored[j] != '\0' && stored[j] != '\n')
		j++;
	if (stored[j] == '\n')
		retline = malloc((j + 2) * sizeof(char));
	else
		retline = malloc((j + 1) * sizeof(char));
	if (!retline)
		return (NULL);
	while (stored[i] != '\n' && stored[i] != '\0')
	{
		retline[i] = stored[i];
		i++;
	}
	if (stored[i] == '\n')
		retline[i++] = '\n';
	retline[i] = '\0';
	return (retline);
}

char	*get_next_line(int fd)
{
	static char		*stored = NULL;
	char			*retline;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stored = ft_checkstorage(fd, stored);
	if (!stored)
		return (NULL);
	retline = ft_allocandfeelline(stored, i, j);
	stored = update_storage(stored);
	return (retline);
}