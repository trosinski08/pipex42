/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 03:51:09 by trosinsk          #+#    #+#             */
/*   Updated: 2023/11/26 17:01:04 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	minus_menager(int d, t_format *f, char *str, int len)
{
	int	i;

	i = 0;
	if (len > d)
	{
		while (str[i] != '\0')
		{
			i += ft_putchar_fd((int)str[i]);
			if (i == -1)
				return (-1);
			f ->type = 0;
		}
	}
	else
	{
		i += write(1, str, len);
		while (i < d)
			i += write(1, " ", 1);
	}
	return (i);
}

int	d_menager(int d, t_format *f, char *str, int len)
{
	int	i;

	i = 0;
	if (len > d)
	{
		while (str[i] != '\0')
		{
			i += ft_putchar_fd((int)str[i]);
			if (i == -1)
				return (-1);
			f ->type = 0;
		}
	}
	else
	{
		while (i < d - len)
			i += write(1, " ", 1);
		i += write(1, str, len);
	}
	return (i);
}

int	str_menager(char *str, int len, int i)
{
	if (str == NULL)
		i += write(1, "(null)", 6);
	else
		i += write(1, str, len);
	return (i);
}

int	print_string(char *str, t_format *f)
{
	int	i;
	int	d;
	int	len;

	i = 0;
	d = f->width;
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (f->dot == 1 && len > f->prec)
		len = f->prec;
	if (!str && f->space == 1)
		return (-1);
	else if (f->minus && d > 0)
		i = minus_menager(d, f, str, len);
	else if (d > 0)
		i = d_menager(d, f, str, len);
	else
		i += str_menager(str, len, i);
	f ->width = 0;
	f ->type = 0;
	return (i);
}

// int	dot_menager(t_format *f, char *str, int len)
// 	// else if (f->dot == 1)
// 	// 	i = dot_menager(f, str, len);
// {
// 	int	i;
// 	int	d;

// 	i = 0;
// 	d = 0;
// 	while (str[i] != '\0')
// 	{
// 		i += ft_putchar_fd((int)str[i]);
// 		if (i == -1)
// 			return (-1);
// 		f ->type = 0;
// 	}
// 	while (i < d - len)
// 		i += write(1, " ", 1);
// 	i += write(1, str, len);
// 	return (i);
// }