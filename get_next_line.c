/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:55:22 by tiaferna          #+#    #+#             */
/*   Updated: 2023/05/18 14:20:47 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_break(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n');
		return (1);
	}
	return (0);
}

int ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr != NULL)
	{
		while (s1[i])
		{
			newstr[i] = s1[i];
			i++;
		}
		while (s2[j])
		{
			newstr[i] = s2[j];
			i++;
			j++;
		}
		newstr[i] = '\0';
	}
	return (newstr);
}

char	*ft_strdup_break(const char *s)
{
	size_t	i;
	char	*s_dup;

	i = 0;
	while (s[i] != '\n')
		i++;
	i++;
	s_dup = malloc(i + 1);
	if (!s_dup)
		return (NULL);
	i = 0;
	while (s[i] != '\n')
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = '\n';
	s_dup[i + 1] = '\0';
	return (s_dup);
}

char	*get_next_line(int fd)
{
	static char	stash[1000];
	char		buff[BUFFER_SIZE + 1];
	char		*line;
	int			read_val;
	int			i;

	read_val = read(fd, buff, BUFFER_SIZE + 1);
	if (read_val > 0)
	{
		i = ft_strlen(stash);
		stash = ft_strjoin(stash, buff);
		if (check_break(stash) != 0)
			{
				line = ft_strdup_break(stash);
				return (line);
			}
		else
			return (stash);
	}
	else
		write(1, "End of file reached", 20);
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	get_next_line(fd);
}