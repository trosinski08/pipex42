/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 03:32:30 by trosinsk          #+#    #+#             */
/*   Updated: 2023/11/26 14:44:34 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_spec(char fspec, t_format *flags)
{
	if (ft_strchr("0123456789", fspec) && flags -> zero == 0)
		flags->type = flags->type * 10 + (fspec - '0');
	flags->width = flags->type;
	flags->prec = flags->type;
	if (fspec == '-')
		flags->minus = 1;
	else if (fspec == '.')
	{
		flags->dot = 1;
		flags->type = 0;
	}
	else if (fspec == '0' && flags ->type == 0)
		flags->zero = 1;
	else if (fspec == '+')
		flags->plus = 1;
	else if (fspec == ' ')
		flags->space = 1;
	else if (fspec == '#')
		flags->hash = 1;
}
