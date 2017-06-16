/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cost.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 12:31:40 by kzeng             #+#    #+#             */
/*   Updated: 2017/04/15 12:31:41 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_set_cost_helper(t_list *list, int i)
{
	int		next;
	int		j;

	j = 0;
	while (list->links[i][j][0] != '\0')
	{
		next = 0;
		while (ft_strcmp(list->rooms[next], list->links[i][j]) != 0)
			next++;
		if (list->cost_map[next] == -1 ||
			(list->cost_map[next] > list->cost_map[i] + 2))
			list->cost_map[next] = list->cost_map[i] + 2;
		else if (list->cost_map[next] == list->cost_map[i] && j > 1)
		{
			list->cost_map[next] += 2;
			list->cost_map[i] += 2;
		}
		j++;
	}
	return (1);
}

void	ft_set_cost(t_list *list, int i, int m)
{
	int	updated_rooms;

	list->cost = 0;
	updated_rooms = 0;
	while (updated_rooms != list->total_rooms)
	{
		i = -1;
		m = 0;
		updated_rooms = 0;
		while (++i < list->total_rooms)
		{
			if (list->cost_map[i] != -1)
				updated_rooms++;
			if (list->cost_map[i] == list->cost)
				m = ft_set_cost_helper(list, i);
		}
		if (m == 1)
			list->cost += 2;
		if (m != 1 && list->cost_map[list->start] == -1)
			list->error = -10;
		if (m != 1)
			return ;
	}
}

void	ft_update_helper(t_list *list, int i, char *before, char *next)
{
	int		j;

	while (++i < list->total_rooms)
	{
		if (list->cost_map[i] == list->cost)
		{
			j = 0;
			while (list->links[i][j][0] != '\0')
				j++;
			if (j == 2)
			{
				if (ft_strcmp(list->links[i][0], next) == 0 &&
					ft_strcmp(list->links[i][1], before) == 0 &&
					ft_strcmp(next, list->end_room) != 0)
					list->cost_map[i] += 100;
				else if (ft_strcmp(list->links[i][1], next) == 0 &&
					ft_strcmp(list->links[i][0], before) == 0 &&
					ft_strcmp(next, list->end_room) != 0)
					list->cost_map[i] += 100;
			}
		}
	}
}

void	ft_get_link(t_list *list, int i, char **before, char **next)
{
	int		m;

	m = -1;
	while (++m < list->total_rooms)
	{
		if (ft_strcmp(list->rooms[m], list->links[i][0]) == 0)
		{
			if (list->cost_map[m] < list->cost_map[i])
			{
				*next = list->links[i][0];
				*before = list->links[i][1];
			}
			else
			{
				*before = list->links[i][0];
				*next = list->links[i][1];
			}
			break ;
		}
	}
}

void	ft_update_cost(t_list *list)
{
	int		i;
	int		j;
	char	*before;
	char	*next;

	list->cost = list->cost_map[list->start];
	while (list->cost > 0)
	{
		list->cost -= 2;
		i = -1;
		while (++i < list->total_rooms)
		{
			j = 0;
			while (list->cost_map[i] != list->cost && i < list->total_rooms)
				i++;
			if (i == list->total_rooms)
				break ;
			while (list->links[i][j][0] != '\0')
				j++;
			if (j == 2)
				ft_get_link(list, i, &before, &next);
			if (j == 2)
				ft_update_helper(list, i, before, next);
		}
	}
}
