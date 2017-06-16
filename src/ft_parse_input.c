/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:07:09 by kzeng             #+#    #+#             */
/*   Updated: 2017/03/23 18:07:10 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_read_input(t_list *list)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(0, &line) > 0)
	{
		i++;
		ft_printf("%s\n", line);
		if (ft_strcmp(line, "") == 0)
		{
			list->error = -8;
			break ;
		}
		if ((list->error = ft_parse_line(line, list, i)) < 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
	ft_printf("\n");
	if (list->error == 0 && (list->start == 0 || list->end == 0))
		list->error = -7;
	return (list->error);
}

int		ft_add_first_room(t_list *list, char **split)
{
	list->rooms = (char **)malloc(sizeof(char *));
	list->room_x = (int *)malloc(sizeof(int));
	list->room_y = (int *)malloc(sizeof(int));
	list->rooms[0] = ft_strdup(split[0]);
	if (list->rooms[0][0] == 'L')
	{
		free(list->rooms[0]);
		free(list->rooms);
		return (-3);
	}
	list->room_x[0] = ft_atoi(list, split[1]);
	if (list->room_x[0] == -1 && list->error == -1)
	{
		free(list->room_x);
		return (-4);
	}
	list->room_y[0] = ft_atoi(list, split[2]);
	if (list->room_y[0] == -1 && list->error == -1)
	{
		free(list->room_y);
		return (-4);
	}
	return (0);
}

int		ft_add_room_helper(t_list *list, char **split)
{
	int		i;
	char	**room_copy;
	int		*x_copy;
	int		*y_copy;

	i = -1;
	room_copy = list->rooms;
	x_copy = list->room_x;
	y_copy = list->room_y;
	list->rooms = (char **)malloc(sizeof(char *) * list->total_rooms);
	list->room_x = (int *)malloc(sizeof(int) * list->total_rooms);
	list->room_y = (int *)malloc(sizeof(int) * list->total_rooms);
	while (++i < list->total_rooms - 1)
	{
		list->rooms[i] = ft_strdup(room_copy[i]);
		list->room_x[i] = x_copy[i];
		list->room_y[i] = y_copy[i];
	}
	list->rooms[i] = ft_strdup(split[0]);
	list->room_x[i] = ft_atoi(list, split[1]);
	list->room_y[i] = ft_atoi(list, split[2]);
	if ((list->room_x[i] == -1 || list->room_y[i] == -1) && list->error == -1)
		return (-4);
	return (0);
}

int		ft_add_room(t_list *list, char *line)
{
	int		i;
	int		z;
	char	**split;

	z = 0;
	if ((split = ft_strsplit(line, ' ')) == NULL)
		return (-42);
	else if (list->total_rooms == 1)
		z = ft_add_first_room(list, split);
	else
		z = ft_add_room_helper(list, split);
	if (list->start == 1)
	{
		list->start = 2;
		list->start_room = ft_strdup(split[0]);
	}
	if (list->end == 1)
	{
		list->end = 2;
		list->end_room = ft_strdup(split[0]);
	}
	i = 0;
	while (split[i] != '\0')
		free(split[i++]);
	return (z);
}

int		ft_parse_line(char *ln, t_list *list, int i)
{
	if (i == 1 && ft_atoi(list, ln) <= 0)
		return (-1);
	else if (i == 1 && ft_atoi(list, ln) > 0)
		list->ants = list->num;
	if (ft_strcmp("##start", ln) == 0 && list->start == 0 && list->end != 1)
		return (list->start = 1);
	else if (ft_strcmp("##end", ln) == 0 && list->end == 0 && list->start != 1)
		return (list->end = 1);
	if ((list->start == 1 || list->end == 1) && ft_nwords(ln, ' ', 0) != 3)
		return (-6);
	if (ln[0] == '#')
		return (0);
	else if (ft_nwords(ln, ' ', 0) == 3)
	{
		list->total_rooms++;
		return (ft_add_room(list, ln));
	}
	else if (ft_nwords(ln, '-', 0) == 2)
	{
		list->total_links++;
		if (list->total_links == 1)
			ft_setup_link(list);
		return (ft_add_link(list, ln));
	}
	return (0);
}
