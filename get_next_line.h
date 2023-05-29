/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:32:44 by patatoss          #+#    #+#             */
/*   Updated: 2023/05/27 22:28:37 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

int		check_break(char *str);
int		check_end_file(char *str);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup_break(const char *s);
char	*refresh_stash(char *stash);
char	*get_next_line(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

#endif