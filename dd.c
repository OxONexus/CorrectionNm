/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:58:32 by apaget            #+#    #+#             */
/*   Updated: 2018/02/11 11:59:03 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void			print_hex(unsigned long hex)
{
	if (hex >= 16)
	{
		print_hex(hex / 16);
		print_hex(hex % 16);
	}
	else
	{
		if (hex > 9)
			ft_putchar('a' + hex % 10);
		else
			ft_putchar('0' + hex);
	}
}

void			print_name(char *name)
{
	ft_putstr(name);
	ft_putstr(":\n");
}

void			long_print2(unsigned long hex, int size)
{
	int nbz;
	int i;

	i = -1;
	nbz = size - counthex(hex);
	while (++i < nbz)
		ft_putchar('0');
	print_hex(hex);
}

void			long_print(unsigned long hex, int size)
{
	int nbz;
	int i;

	i = -1;
	nbz = size - counthex(hex);
	ft_putchar('\n');
	while (++i < nbz)
		ft_putchar('0');
	print_hex(hex);
	ft_putstr("\t");
}

int				counthex(unsigned long hex)
{
	if (hex < 16)
		return (1);
	return (counthex(hex / 16) + 1);
}
