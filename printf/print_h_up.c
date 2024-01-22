/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_h_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 02:01:21 by trosinsk          #+#    #+#             */
/*   Updated: 2023/11/23 16:40:11 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long	print_h_up(unsigned long nbr, unsigned int base, t_format *f)
{
	int		i;
	char	*upp_base;

	i = 0;
	if (f ->hash == 1 && nbr != 0)
	{
		write(1, "0X", 2);
		f->hash = 0;
		i = 2;
		return (i + print_h_up(nbr, base, f));
	}
	upp_base = "0123456789ABCDEF";
	if (nbr < base)
		return (ft_putchar_fd(upp_base[nbr]));
	else
	{
		i += print_h_up(nbr / base, base, f);
		if (i == -1)
			return (-1);
		return (i + print_h_up(nbr % base, base, f));
	}
	return (i);
}
