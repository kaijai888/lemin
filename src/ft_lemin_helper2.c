/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin_helper2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:44:40 by kzeng             #+#    #+#             */
/*   Updated: 2017/03/23 17:44:41 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	*ft_strsub(char *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	k;

	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL || sub == NULL)
		return (NULL);
	i = ft_strlen(s);
	k = 0;
	while (start < i && k < len)
	{
		sub[k] = s[start];
		k++;
		start++;
	}
	while (k < len + 1)
		sub[k++] = '\0';
	return (sub);
}

char	*ft_strnew(size_t size)
{
	char			*str;
	size_t			i;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(char *s1)
{
	char			*str;
	int				len;

	len = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[len] != '\0')
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
	{
		str[len] = s1[len];
		len++;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_strcpy(char *dst, char *src)
{
	int				i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strncat(char *s1, char *s2, size_t n)
{
	int				i;
	int				k;

	i = 0;
	k = 0;
	if (n == 0)
		return (s1);
	while (s1[i] != '\0')
		i++;
	while (s2[k] != '\0' && n > 0)
	{
		s1[i] = s2[k];
		i++;
		k++;
		n--;
	}
	s1[i] = '\0';
	return (s1);
}
