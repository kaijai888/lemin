/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:31:40 by kzeng             #+#    #+#             */
/*   Updated: 2017/03/23 17:31:41 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Error list
**	-1: Invalid ant input (non-integer, 0)
**	-3: Invalid room definition ('L')
**	-4: Invalid room x/y
**	-5: Invalid link definition (room not found in link)
**	-6:	No start/end room defined
**	-7:	No ##start/##end
**	-8:	Empty line
**	-9:	No rooms or links
**	-10: No valid path
*/

void	ft_free(t_list *list, int i, int j)
{
	while (++i < list->total_rooms)
		free(list->rooms[i]);
	free(list->rooms);
	i = -1;
	while (++i < list->ants)
		free(list->ant_location[i]);
	i = -1;
	while (++i < list->total_rooms)
	{
		j = 0;
		while (list->links[i][j][0] != '\0')
			free(list->links[i][j++]);
		free(list->links[i][j]);
		free(list->links[i]);
	}
	free(list->links);
	free(list->ant_location);
	free(list->room_x);
	free(list->room_y);
	free(list->start_room);
	free(list->end_room);
	free(list->ant_number);
	free(list->cost_map);
	free(list->filled_room);
}

void	ft_solve(t_list *list)
{
	ft_setup(list, 0);
	if (list->error >= 0)
		ft_set_cost(list, 0, 0);
	if (list->error >= 0)
		list->error = 42;
	if (list->error >= 0)
		ft_update_cost(list);
	if (list->error >= 0)
		ft_move_ants_helper(list);
}

int		main(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	ft_initialize_list(&list);
	ft_read_input(list);
	if ((list->total_rooms == 0 || list->total_links == 0) && list->error >= 0)
		list->error = -8;
	if (list->error >= 0)
		ft_solve(list);
	if (list->error < 0)
		ft_printf("Error:%d\n", list->error);
	if (list->error == 42)
		ft_free(list, -1, -1);
	free(list);
	return (0);
}
