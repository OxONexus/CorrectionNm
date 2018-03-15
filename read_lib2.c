/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lib2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 14:34:05 by apaget            #+#    #+#             */
/*   Updated: 2018/02/11 14:36:10 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		check_tab(int **tab, int *size, int nb)
{
	int i;

	i = 0;
	if (*tab == NULL)
	{
		*size = *size + 1;
		*tab = malloc(sizeof(int) * *size);
		(*tab)[*size - 1] = nb;
		return (0);
	}
	while (i < *size)
	{
		if ((*tab)[i] == nb)
			return (1);
		i++;
	}
	*size = *size + 1;
	*tab = realloc(*tab, sizeof(int) * *size);
	(*tab)[*size - 1] = nb;
	return (0);
}

int		ismagic(unsigned int c)
{
	if (c == MH_MAGIC || c == MH_CIGAM || c == MH_MAGIC_64 ||
			c == MH_CIGAM_64 || c == FAT_MAGIC || c == FAT_CIGAM)
		return (1);
	return (0);
}

char	*get_ptr_header(char *ptr)
{
	while (*ptr != 0)
		ptr++;
	while (*ptr == 0)
		ptr++;
	return (ptr);
}
