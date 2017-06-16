/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 12:44:36 by kzeng             #+#    #+#             */
/*   Updated: 2017/04/15 12:44:37 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_setup_link(t_list *list)
{
	int		i;

	i = 0;
	list->links = (char ***)malloc(sizeof(char **) * list->total_rooms);
	while (i < list->total_rooms)
	{
		list->links[i] = (char **)malloc(sizeof(char *));
		list->links[i][0] = ft_strnew(0);
		i++;
	}
}

void	ft_add_link_helper(t_list *list, char **split, int j, int k)
{
	int		i;
	int		z;
	char	**copy;

	i = 0;
	z = j != k ? 1 : 0;
	copy = list->links[j];
	while (copy[i][0] != '\0')
	{
		if (ft_strcmp(copy[i], list->rooms[k]) == 0)
			return ;
		i++;
	}
	list->links[j] = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (copy[i][0] != '\0')
	{
		list->links[j][i] = ft_strdup(copy[i]);
		free(copy[i++]);
	}
	list->links[j][i] = ft_strdup(split[z]);
	list->links[j][i + 1] = ft_strnew(0);
	if (j != k)
		ft_add_link_helper(list, split, k, k);
}

int		ft_add_link(t_list *list, char *line)
{
	char	**split;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = -1;
	if ((split = ft_strsplit(line, '-')) == NULL)
		return (-42);
	while (++i < list->total_rooms)
	{
		if (ft_strcmp(list->rooms[i], split[0]) == 0)
			j = i;
		if (ft_strcmp(list->rooms[i], split[1]) == 0)
			k = i;
	}
	if (j == -1 || k == -1 || j == k)
		return (-5);
	else
		ft_add_link_helper(list, split, j, k);
	free(split[0]);
	free(split[1]);
	return (0);
}
