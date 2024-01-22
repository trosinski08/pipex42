/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 06:16:22 by trosinsk          #+#    #+#             */
/*   Updated: 2023/11/25 15:38:05 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long	min_conv(unsigned long nbr, t_format *f)
{
	int	c;
	int	i;

	i = 0;
	c = f ->width - 10;
	f->width = 0;
	f -> type = 0;
	if (nbr == -ULONG_MAX)
		c = 11;
	while (i < c)
		i += write(1, " ", 1);
	return (i);
}

unsigned long	print_h(unsigned long nbr, unsigned int base, t_format *f)
{
	int		i;
	char	*low_base;

	i = 0;
	low_base = "0123456789abcdef";
	if (nbr < base)
		i += ft_putchar_fd(low_base[nbr]);
	else
	{
		i += print_h(nbr / base, base, f);
		if (i == -1)
			return (-1);
		i += print_h(nbr % base, base, f);
	}
	return (i);
}

unsigned long	print_point(unsigned long nbr, unsigned int base, t_format *f)
{
	int		i;
	char	*low_base;

	i = 0;
	if (f->width > i && f->minus == 0)
		i += (min_conv(nbr, f));
	i += ft_putchar_fd('0');
	if (i == -1)
		return (-1);
	i += ft_putchar_fd('x');
	low_base = "0123456789abcdef";
	if (nbr < base)
		i += ft_putchar_fd(low_base[nbr]);
	else
	{
		i += print_h(nbr / base, base, f);
		if (i == -1)
			return (-1);
		i += print_h(nbr % base, base, f);
	}
	if (f->width > i && f->minus == 1 && nbr != 0)
		i += (min_conv(nbr, f));
	return (i);
}
