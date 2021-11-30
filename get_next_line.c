/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:23:12 by omeslall          #+#    #+#             */
/*   Updated: 2021/11/28 12:14:57 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

void	ft_get_line(char **str, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_substr(*str, 0, ++i);
		temp = *str;
		*str = ft_strdup(*str + i);
		ft_free(&temp);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_free(str);
	}
	if ((*line)[0] == '\0')
		ft_free(line);
}

void	ft_read(int fd, char **str, char **line, char **buffer)
{
	ssize_t	ret;
	char	*temp;

	ret = 1;
	while (ret && !ft_strchr(*str, '\n'))
	{
		ret = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[ret] = '\0';
		temp = *str;
		*str = ft_strjoin(temp, *buffer);
		ft_free(&temp);
	}
	ft_free(buffer);
	ft_get_line(str, line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		ft_free(&buffer);
		return (NULL);
	}
	if (!str)
		str = ft_strdup("");
	ft_read(fd, &str, &line, &buffer);
	return (line);
}
