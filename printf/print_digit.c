/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 02:00:45 by trosinsk          #+#    #+#             */
/*   Updated: 2023/11/26 16:31:33 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	min_conv(long nbr, int base, t_format *f)
{
	int	c;
	int	i;
	int	h;

	i = 0;
	h = 1;
	if (nbr < 0 || (f ->plus == 1 && nbr >= 0))
		h = 2;
	while (nbr / base != 0)
	{
		h++;
		nbr /= base;
	}
	c = f ->width - h;
	f->width = 0;
	f -> type = 0;
	while (i < c)
		i += write(1, " ", 1);
	return (i);
}

int	minus_nbr(long nbr, int base, t_format *f)
{
	int	i;

	i = 0;
	i += write (1, "-", 1);
	if (i == -1)
		return (-1);
	f -> plus = 0;
	f -> space = 0;
	return (print_digit(-nbr, base, f) + 1);
}

int	plus_conv(long nbr, int base, t_format *f)
{
	int	i;

	i = 0;
	i += write(1, "+", 1);
	if (i == -1)
		return (-1);
	f ->plus = 0;
	return (i + print_digit(nbr, base, f));
}

int	space_conv(long nbr, int base, t_format *f)
{
	int	i;

	i = 0;
	i += write(1, " ", 1);
	if (i == -1)
		return (-1);
	f ->space = 0;
	return (i + print_digit(nbr, base, f));
}

int	print_digit(long nbr, int base, t_format *f)
{
	int		i;
	char	*low_base;

	i = 0;
	low_base = "0123456789abcdef";
	if (f->width > i && f->minus == 0)
		i += (min_conv(nbr, base, f));
	if (nbr < 0)
		i += minus_nbr(nbr, base, f);
	else if ((f ->plus == 1 && nbr >= 0) && f->minus == 0)
		i += plus_conv(nbr, base, f);
	else if (f ->space == 1 && nbr >= 0 && f->minus == 0)
		i += space_conv(nbr, base, f);
	else if (nbr < base)
		i += ft_putchar_fd(low_base[nbr]);
	else
	{
		i += print_digit(nbr / base, base, f);
		if (i == -1)
			return (-1);
		i += print_digit(nbr % base, base, f);
	}
	if (f->width > i && f->minus == 1)
		i += (min_conv(nbr, base, f));
	return (i);
}
