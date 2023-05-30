/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:49:51 by patatoss          #+#    #+#             */
/*   Updated: 2023/05/22 10:49:52 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_break(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	check_end_file(char *str)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (str[i++] == '\0')
			return (1);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *stash, char *buff)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	i = 0;
	j = 0;
	if (!stash)
	{
		stash = malloc(sizeof(char));
		stash[0] = '\0';
	}
	newstr = malloc(sizeof(char) * (ft_strlen(stash) + BUFFER_SIZE) + 1);
	if (!newstr)
		return (NULL);
	while (stash[i])
	{
		newstr[i] = stash[i];
		i++;
	}
	while (j < BUFFER_SIZE)
	{
		newstr[i] = buff[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	free(stash);
	//free(buff);
	
	return (newstr);
}

char	*ft_strdup_break(const char *stash)
{
	size_t	i;
	char	*s_dup;

	i = 0;
	while (stash[i] != '\n')
		i++;
	s_dup = malloc(sizeof(char) * i + 2);
	if (!s_dup)
		return (NULL);
	i = 0;
	while (stash[i] != '\n')
	{
		s_dup[i] = stash[i];
		i++;
	}
	s_dup[i] = '\n';
	s_dup[i + 1] = '\0';
	return (s_dup);
}

char	*refresh_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	j = i;
	while (stash[j])
		j++;
	new_stash = malloc(sizeof(char) * (j - i) + 1);
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[++i];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

void	*ft_memset(void *stash, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	v;
	size_t			i;

	p = (unsigned char *)stash;
	v = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		*(p + i) = v;
		i++;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*line;
	int			read_val;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (stash != NULL && check_break(stash) == 1)
	{
		line = ft_strdup_break(stash);
		stash = refresh_stash(stash);
		return (line);
	}
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	ft_memset(buff, '\0', BUFFER_SIZE);
	read_val = read(fd, buff, BUFFER_SIZE);
	while (read_val != 0)
	{
		if (read_val == -1)
		{
			free(buff);
			free(stash);
			return (NULL);
		}
		if (check_break(buff) == 1)
		{
			stash = ft_strjoin(stash, buff);
			line = ft_strdup_break(stash);
			stash = refresh_stash(stash);
			return (line);
		}
		else if (check_end_file(buff) == 1)
		{
			line = ft_strjoin(stash, buff);
			return (line);
		}
		else
			stash = ft_strjoin(stash, buff);
		read_val = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (stash);
}
int main()
{
	int i = 0;
	int fd = open("test.txt", O_RDONLY);
	while (i++ < 5)
		printf("%s", get_next_line(fd));
	close(fd);
}
