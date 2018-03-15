/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oread_header2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 18:21:00 by apaget            #+#    #+#             */
/*   Updated: 2018/02/11 15:59:28 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void				*find_sub_segment(char *ptr, t_program *prog,
		unsigned int nb_segment, char *seg)
{
	unsigned int			i;
	struct section_64		*tmp;

	(void)prog;
	tmp = (struct section_64*)ptr;
	i = 0;
	while (i < nb_segment)
	{
		if (strnstr(tmp->sectname, seg, ft_strlen(seg)))
			return (tmp);
		tmp++;
		i++;
	}
	return (NULL);
}

void				*find_sub_segment32(char *ptr, t_program *prog,
		unsigned int nb_segment, char *seg)
{
	unsigned int		i;
	struct section		*tmp;

	(void)prog;
	tmp = (struct section*)ptr;
	i = 0;
	while (i < nb_segment)
	{
		if (strnstr(tmp->sectname, seg, ft_strlen(seg)))
			return (tmp);
		tmp++;
		i++;
	}
	return (NULL);
}

void				oread_fat_head(t_program *prog, char *ptr)
{
	struct fat_header	*fat_header;
	struct fat_arch		*arch;
	unsigned int		i;
	unsigned int		nb_arch;
	t_program			new;

	prog->endian = MH_CIGAM;
	i = 0;
	fat_header = (struct fat_header*)ptr;
	nb_arch = llendian_read(prog, fat_header->nfat_arch);
	arch = (struct fat_arch*)((void*)ptr + sizeof(struct fat_header));
	while (i < nb_arch)
	{
		ft_bzero(&new, sizeof(new));
		if (uiendian_read(prog, (unsigned)arch->cputype) == CPU_TYPE_X86_64)
			oread_header_64(&new, (void*)ptr +
					uiendian_read(prog, arch->offset));
		arch = (void*)arch + sizeof(struct fat_arch);
		i++;
	}
}

int					not_in_tab(t_list *list, char *name)
{
	t_symbol	*tmp;

	if (!list)
		return (1);
	while (list)
	{
		tmp = list->content;
		if (ft_strcmp(tmp->name, name) == 0)
			return (0);
		list = list->next;
	}
	return (1);
}
