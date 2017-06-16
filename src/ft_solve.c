/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 13:34:40 by kzeng             #+#    #+#             */
/*   Updated: 2017/03/31 13:34:41 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_setup(t_list *list, int i)
{
	list->ant_location = (char **)malloc(sizeof(char *) * (list->ants + 1));
	list->ant_number = (int *)malloc(sizeof(int) * list->ants);
	list->cost_map = (int *)malloc(sizeof(int) * list->total_rooms);
	list->filled_room = (int *)malloc(sizeof(int) * list->total_rooms);
	i = -1;
	while (++i < list->ants)
		list->ant_location[i] = ft_strdup(list->start_room);
	list->ant_location[i] = ft_strnew(0);
	i = -1;
	while (++i < list->ants)
		list->ant_number[i] = list->ants - i;
	i = -1;
	while (++i < list->total_rooms)
	{
		list->cost_map[i] = -1;
		if (ft_strcmp(list->rooms[i], list->end_room) == 0)
			list->cost_map[i] = 0;
		if (ft_strcmp(list->rooms[i], list->end_room) == 0)
			list->end = i;
		list->filled_room[i] = 0;
		if (ft_strcmp(list->rooms[i], list->start_room) == 0)
			list->filled_room[i] = 1;
		if (ft_strcmp(list->rooms[i], list->start_room) == 0)
			list->start = i;
	}
}

int		ft_next_cost(t_list *list, int i)
{
	int		j;
	int		current_cost;
	int		next_cost;
	int		curr;
	int		next;

	j = 0;
	curr = 0;
	while (ft_strcmp(list->rooms[curr], list->ant_location[i]) != 0)
		curr++;
	list->current = curr;
	current_cost = list->cost_map[curr];
	next_cost = current_cost;
	while (list->links[curr][j][0] != '\0')
	{
		next = 0;
		while (ft_strcmp(list->rooms[next], list->links[curr][j]) != 0)
			next++;
		if (list->cost_map[next] < next_cost)
			next_cost = list->cost_map[next];
		j++;
	}
	return (next_cost);
}

int		ft_ant_helper(t_list *list, int i, int j, int next)
{
	free(list->ant_location[i]);
	list->ant_location[i] = ft_strdup(list->links[list->current][j]);
	if (ft_strcmp(list->ant_location[i], list->end_room) != 0)
		list->filled_room[next] = 1;
	else
		list->reached_end++;
	if (ft_strcmp(list->rooms[list->current], list->start_room) != 0)
		list->filled_room[list->current] = 0;
	list->line++;
	if (list->line > 1)
		ft_printf(" ");
	if (list->ant_number[i] % 3 == 0)
		ft_printf("\x1B[31m");
	else if (list->ant_number[i] % 2 == 0)
		ft_printf("\x1B[32m");
	else
		ft_printf("\x1B[33m");
	ft_printf("L%d-%s", list->ant_number[i], list->ant_location[i]);
	return (0);
}

int		ft_move_ants(t_list *list, int i, int at_start)
{
	int		j;
	int		skip;
	int		next;

	j = 0;
	while (list->links[list->current][j][0] != '\0')
	{
		skip = 0;
		next = 0;
		while (ft_strcmp(list->rooms[next], list->links[list->current][j]) != 0)
			next++;
		if (list->cost_map[next] != list->next_cost && list->next_cost == 0)
			skip = 1;
		if (at_start == 0 && list->cost_map[next] != list->next_cost)
			skip = 1;
		if (skip == 0 && list->filled_room[next] == 0 &&
			((list->cost_map[next] < list->cost_map[list->current]) ||
				(list->cost_map[next] == list->cost_map[list->current] &&
				at_start > 0)))
			return (ft_ant_helper(list, i, j, next));
		j++;
	}
	return (0);
}

void	ft_move_ants_helper(t_list *list)
{
	int	i;
	int	at_start;

	list->reached_end = 0;
	while (list->reached_end != list->ants)
	{
		i = -1;
		at_start = 0;
		while (++i < list->ants)
		{
			if (ft_strcmp(list->ant_location[i], list->start_room) == 0)
				at_start++;
		}
		i = list->ants;
		list->line = 0;
		while (--i >= 0)
		{
			while (ft_strcmp(list->ant_location[i], list->end_room) == 0)
				i--;
			list->next_cost = ft_next_cost(list, i);
			ft_move_ants(list, i, at_start);
		}
		ft_printf("\n");
	}
}
