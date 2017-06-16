/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin_helper3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:18:47 by kzeng             #+#    #+#             */
/*   Updated: 2017/03/23 18:18:48 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t		ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int			ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	ft_atoi_helper(t_list *list, char *num, int i)
{
	char	*x;
	int		j;

	x = "2147483648";
	j = i - list->neg;
	if (list->len - list->neg == 10)
	{
		if (num[i] > x[j] && list->neg == 1)
			return (-1);
		else if (list->neg == 0)
		{
			if (i == list->len - 1 && num[i] > '7')
				return (-1);
			else if (num[i] > x[j])
				return (-1);
		}
	}
	return (1);
}

int			ft_atoi(t_list *list, char *num)
{
	int		i;

	list->num = 0;
	list->len = ft_strlen(num);
	list->neg = num[0] == '-' ? 1 : 0;
	i = list->neg;
	if (list->len - list->neg > 10)
		return (list->error = -1);
	while (i < list->len)
	{
		if (ft_isdigit(num[i]) == 0)
			return (list->error = -1);
		else
			list->num = (list->num * 10) + (num[i] - '0');
		if (ft_atoi_helper(list, num, i) == -1)
			return (list->error = -1);
		i++;
	}
	list->num = list->neg == 1 ? list->num *= -1 : list->num;
	return (list->num);
}
