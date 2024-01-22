/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:23:17 by trosinsk          #+#    #+#             */
/*   Updated: 2023/11/26 17:01:55 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// static unsigned long	min_conv(unsigned long nbr, t_format *f, int base)
// {
// 	int	c;
// 	int	i;
// 	int	h;

// 	i = 0;
// 	h = 1;
// 	if (f ->hash == 1 && nbr != 0)
// 		h = 3;
// 	while (nbr / base != 0)
// 	{
// 		h++;
// 		nbr /= base;
// 	}
// 	c = f ->width - h;
// 	f->width = 0;
// 	f -> type = 0;
// 	if (nbr == -ULONG_MAX)
// 		c = 11;
// 	while (i < c)
// 		i += write(1, " ", 1);
// 	return (i);
	// if (f->width > i && f->minus == 0)l48
	// 	i += (min_conv(nbr, f, base)); l49
// 	// if (f->width > i && f->minus == 1) l63
// 	// 	i += (min_conv(nbr, f, base)); l64
// }

unsigned long	print_hexa(unsigned long nbr, unsigned int base, t_format *f)
{
	int		i;
	char	*low_base;

	i = 0;
	if (f ->hash == 1 && nbr != 0)
	{
		write(1, "0x", 2);
		f->hash = 0;
		i = 2;
	}
	low_base = "0123456789abcdef";
	if (nbr < base)
		i += ft_putchar_fd(low_base[nbr]);
	else
	{
		i += print_hexa(nbr / base, base, f);
		if (i == -1)
			return (-1);
		i += print_hexa(nbr % base, base, f);
	}
	return (i);
}
