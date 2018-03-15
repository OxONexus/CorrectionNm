/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:03:04 by apaget            #+#    #+#             */
/*   Updated: 2018/02/11 12:03:36 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

unsigned long long	llendian_read(t_program *prog, unsigned long long x)
{
	if (prog->endian == FAT_CIGAM || prog->endian == MH_CIGAM_64
			|| prog->endian == MH_CIGAM)
		return (llendian_swap(x));
	return (x);
}

unsigned long		endian_swap(unsigned long x)
{
	x = (x >> 24) | (x >> 8 & 0x0000FF00) | (x << 8 & 0x00FF0000) | (x << 24);
	return (x);
}

unsigned long		endian_read(t_program *prog, unsigned long x)
{
	if (prog->endian == FAT_CIGAM || prog->endian == MH_CIGAM_64
			|| prog->endian == MH_CIGAM)
		return (endian_swap(x));
	return (x);
}

unsigned int		uiendian_swap(unsigned int x)
{
	return ((((uint32_t)(x) & 0xff000000) >> 24) |
			(((uint32_t)(x) & 0x00ff0000) >> 8) |
			(((uint32_t)(x) & 0x0000ff00) << 8) |
			(((uint32_t)(x) & 0x000000ff) << 24));
}

unsigned int		uiendian_read(t_program *prog, unsigned int x)
{
	if (prog->endian == FAT_CIGAM || prog->endian == MH_CIGAM_64
			|| prog->endian == MH_CIGAM)
		return (uiendian_swap(x));
	return (x);
}
