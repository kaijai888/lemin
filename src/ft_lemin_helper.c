/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:44:36 by kzeng             #+#    #+#             */
/*   Updated: 2017/03/23 17:44:37 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_initialize_list(t_list **list)
{
	(*list)->start = 0;
	(*list)->end = 0;
	(*list)->start_room = NULL;
	(*list)->end_room = NULL;
	(*list)->ants = 0;
	(*list)->ant_number = NULL;
	(*list)->ant_location = NULL;
	(*list)->cost_map = NULL;
	(*list)->cost = 0;
	(*list)->filled_room = NULL;
	(*list)->total_rooms = 0;
	(*list)->rooms = NULL;
	(*list)->room_x = NULL;
	(*list)->room_y = NULL;
	(*list)->total_links = 0;
	(*list)->links = NULL;
	(*list)->error = 0;
	(*list)->line = 0;
	(*list)->current = 0;
	(*list)->next_cost = 0;
	(*list)->reached_end = 0;
	(*list)->num = 0;
	(*list)->len = 0;
	(*list)->neg = 0;
}

int			ft_nwords(char *s, char c, int i)
{
	int		nwords;
	int		begin;
	int		len;

	nwords = 0;
	begin = 0;
	len = ft_strlen(s);
	while (s[i] != '\0')
	{
		if (begin == 0 && s[i] != c)
		{
			begin = 1;
			nwords++;
		}
		if (i <= len - 1)
		{
			if (begin == 1 && s[i + 1] == c)
				begin = 0;
		}
		i++;
	}
	return (nwords);
}

static char	*ft_word(char *s, int startindex, int endindex)
{
	char	*word;
	int		k;

	word = (char *)malloc(sizeof(char) * (endindex - startindex + 1));
	if (word == NULL)
		return (NULL);
	k = 0;
	while (startindex < endindex)
	{
		word[k] = s[startindex];
		k++;
		startindex++;
	}
	word[k] = '\0';
	return (word);
}

char		**ft_strsplit(char *s, char c)
{
	char	**fresh;
	int		i;
	int		startindex;
	int		endindex;
	int		nwords;

	i = 0;
	startindex = 0;
	endindex = 0;
	nwords = ft_nwords(s, c, i);
	if ((fresh = (char **)malloc(sizeof(char *) * (nwords + 1))) == NULL)
		return (NULL);
	while (i < nwords)
	{
		startindex = endindex;
		while (s[startindex] == c)
			startindex++;
		endindex = startindex;
		while (s[endindex] != c && s[endindex] != '\0')
			endindex++;
		if ((fresh[i++] = ft_word(s, startindex, endindex)) == NULL)
			return (NULL);
	}
	fresh[i] = 0;
	return (fresh);
}
