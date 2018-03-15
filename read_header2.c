/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 15:56:40 by apaget            #+#    #+#             */
/*   Updated: 2018/03/15 17:40:01 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	read_fat_head(t_program *prog, char *ptr)
{
	struct fat_header	*fat_header;
	struct fat_arch		*arch;
	int					i;
	int					nb_arch;
	t_program			new;

	prog->endian = *(int*)ptr;
	i = -1;
	fat_header = (struct fat_header*)ptr;
	nb_arch = uiendian_read(prog, (unsigned)fat_header->nfat_arch);
	arch = (struct fat_arch*)((void*)ptr + sizeof(struct fat_header));
	while (++i < nb_arch)
	{
		ft_bzero(&new, sizeof(new));
		if (uiendian_read(prog, (unsigned)arch->cputype) ==
				CPU_TYPE_X86_64)
		{
			new.load_size = (unsigned)prog->load_size -
				uiendian_read(prog, (unsigned)arch->offset);
			direct(&new, (void*)ptr + uiendian_read(prog,
						(unsigned)arch->offset), NULL);
			break ;
		}
		arch = (void*)arch + sizeof(struct fat_arch);
	}
}

void	*find_load_command(t_program *prog, char *ptr, int nb_loadcmds, unsigned int cmd)
{
	int						i;
	struct load_command		*loadcmd;

	i = 0;
	loadcmd = (struct load_command *)ptr;
	check_ptr(prog, (unsigned int)ptr);
	if (nb_loadcmds < 0 || nb_loadcmds > 9999)
		exit(0);
	while (i < nb_loadcmds)
	{
		check_ptr(prog, (unsigned int)loadcmd);
		if (loadcmd->cmd == cmd)
			return (loadcmd);
		loadcmd = (void*)loadcmd + loadcmd->cmdsize;
		i++;
	}
	return (NULL);
}

void	free_nbsection64(t_program *prog, int n)
{
	prog->section_64 = (struct section_64**)malloc(
			sizeof(struct section_64*) * n);
	ft_bzero(prog->section_64, n * sizeof(
				struct section_64*));
	prog->nbsection_64 = n;
}

void	add_to_prog64(t_program *prog, struct section_64 *ptr, int n)
{
	int		i;
	int		u;
	void	*tmp;

	i = -1;
	u = -1;
	if ((unsigned int)ptr < (unsigned int)prog->start_prog || (unsigned int)ptr > (unsigned int)prog->start_prog + prog->load_size)
		exit(0);
	if (prog->section_64 == NULL)
		free_nbsection64(prog, n);
	else
	{
		tmp = (struct section_64**)malloc(
				sizeof(struct section_64*) * (prog->nbsection_64 + n));
		memcpy(tmp, prog->section_64, sizeof(struct section_64*) *
				prog->nbsection_64);
		prog->nbsection_64 += n;
		free(prog->section_64);
		prog->section_64 = tmp;
	}
	i = prog->nbsection_64 - n;
	while (++u < n)
	{
		prog->section_64[i + u] = ptr;
		ptr = (struct section_64*)((char*)ptr + sizeof(struct section_64));
	}
}

void	create_seg_list64(t_program *prog, struct segment_command_64 *ptr)
{
	if (!ptr)
		return ;
	prog->section_64 = 0;
	if ((unsigned int)ptr < (unsigned int)prog->start_prog || (unsigned int)ptr > (unsigned int)prog->start_prog + prog->load_size)
		exit(0);
	while (ptr->cmd == LC_SEGMENT_64)
	{
		if (ptr->nsects != 0)
			add_to_prog64(prog, (struct section_64*)((char*)ptr +
						sizeof(struct segment_command_64)), ptr->nsects);
		ptr = (struct segment_command_64 *)((char*)ptr + ptr->cmdsize);
	}
}
