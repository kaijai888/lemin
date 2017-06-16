/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 12:58:40 by kzeng             #+#    #+#             */
/*   Updated: 2017/04/15 12:58:41 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
		ft_putchar(s[i++]);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (nb < 0)
		{
			ft_putchar('-');
			nb = -nb;
		}
		if (nb >= 10)
		{
			ft_putnbr(nb / 10);
			ft_putnbr(nb % 10);
		}
		else
			ft_putchar((char)('0' + nb));
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;

	va_start(args, format);
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == 's')
				ft_putstr(va_arg(args, char *));
			else if (format[i + 1] == 'd')
				ft_putnbr(va_arg(args, int));
			if (format[i + 1] == 's' || format[i + 1] == 'd')
				i++;
		}
		else
			ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (0);
}
