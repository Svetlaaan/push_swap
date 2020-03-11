/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:46:47 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/11 19:07:27 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		gnl_line(char **text, char **line, const int fd)
{
	char			*tmp;
	int				len;

	len = 0;
	while (text[fd][len] != '\0' && text[fd][len] != '\n')
		len++;
	if (text[fd][len] == '\0')
	{
		*line = ft_strdup(text[fd]);
		ft_strdel(&text[fd]);
	}
	else if (text[fd][len] == '\n')
	{
		if (!(*line = ft_strsub(text[fd], 0, len)))
			return (-1); ///
		tmp = ft_strdup(text[fd] + len + 1);
		ft_memdel((void **)&text[fd]);
		text[fd] = tmp;
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char		*text[MAX_FD];
	char			buff[BUFF_SIZE + 1];
	int				read_bytes;
	char			*tmp;

	if (fd < 0 || fd > MAX_FD || BUFF_SIZE < 1 || !line)
		return (-1);
	while ((read_bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[read_bytes] = '\0';
		if (text[fd] == NULL)
			tmp = ft_strdup(buff);
		else
			tmp = ft_strjoin(text[fd], buff);
		ft_memdel((void **)&text[fd]);
		text[fd] = ft_strdup(tmp);
		ft_memdel((void **)&tmp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (read_bytes < 0)
		return (-1);
	else if (read_bytes == 0 && (text[fd] == NULL || !ft_strlen(text[fd])))
		return (0);
	return (gnl_line(text, line, fd));
}
