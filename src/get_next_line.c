/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:43:14 by kzeng             #+#    #+#             */
/*   Updated: 2017/03/23 17:43:16 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ft_check_for_n(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_line(char **str)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
	char	*line;

	i = 0;
	len = ft_strlen(*str);
	tmp = *str;
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	line = ft_strsub(*str, 0, i);
	if (tmp[i] != '\0')
	{
		j = ft_strlen(tmp);
		tmp = ft_strsub(*str, i + 1, j - i - 1);
	}
	else
		tmp = ft_strnew(1);
	if (*str != NULL)
		free(*str);
	*str = ft_strdup(tmp);
	free(tmp);
	return (line);
}

static int	ft_new_input(int fd, char **line, char **text)
{
	int		r;
	char	*buf;
	char	*tmp;

	r = 1;
	MALLOC_CHECK((buf = ft_strnew(BUFF_SIZE)));
	READ_CHECK((r = read(fd, buf, BUFF_SIZE)));
	if ((*text = ft_strdup(buf)) == NULL)
	{
		free(buf);
		return (-1);
	}
	while (ft_check_for_n(*text) != 1 && r != 0)
	{
		MALLOC_CHECK((tmp = ft_strnew(ft_strlen(*text) + r)));
		ft_strcpy(tmp, *text);
		READ_CHECK((r = read(fd, buf, BUFF_SIZE)));
		ft_strncat(tmp, buf, r);
		free(*text);
		MALLOC_CHECK((*text = ft_strdup(tmp)));
		free(tmp);
	}
	*line = ft_line(text);
	free(buf);
	return ((*line[0] == '\0' && r == 0) ? 0 : 1);
}

static int	ft_existing_input(int fd, char **line, char **text)
{
	int		r;
	char	*buf;
	char	*tmp;

	r = 1;
	MALLOC_CHECK((buf = ft_strnew(BUFF_SIZE)));
	while (ft_check_for_n(*text) != 1)
	{
		READ_CHECK((r = read(fd, buf, BUFF_SIZE)));
		if (r == 0)
			break ;
		MALLOC_CHECK((tmp = ft_strnew(ft_strlen(*text) + r)));
		ft_strcpy(tmp, *text);
		ft_strncat(tmp, buf, r);
		*text = ft_strdup(tmp);
		free(tmp);
	}
	*line = ft_line(text);
	free(buf);
	return ((*line[0] == '\0' && r == 0) ? 0 : 1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*text[MAX_FD];

	if (fd < 0 || fd >= MAX_FD || BUFF_SIZE <= 0)
		return (-1);
	if (text[fd] == NULL)
		return (ft_new_input(fd, line, &text[fd]));
	else
		return (ft_existing_input(fd, line, &text[fd]));
	return (0);
}
