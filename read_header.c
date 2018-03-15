/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 18:05:05 by apaget            #+#    #+#             */
/*   Updated: 2018/03/15 17:36:42 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	read_header_64(t_program *prog, char *ptr)
{
	struct mach_header_64	*header;
	void					*ptr2;
	t_list					*c;

	header = (struct mach_header_64 *)ptr;
	prog->nb_loadcmds = header->ncmds;
	prog->header = header;
	prog->loadcmd = (void*)ptr + sizeof(struct mach_header_64);
	ptr2 = find_load_command(prog, (char*)prog->loadcmd, header->ncmds,
			LC_SYMTAB);
	create_seg_list64(prog, find_load_command(prog, (char*)prog->loadcmd,
				header->ncmds, LC_SEGMENT_64));
	c = get_sym_list(prog, ptr2);
	print_list(prog, c, 64, header->filetype == MH_OBJECT);
}

void	init_sec(t_program *prog, int n)
{
	prog->section = (struct section**)malloc(sizeof(struct section*) * n);
	ft_bzero(prog->section, n * sizeof(struct section*));
	prog->nbsection = n;
}

void	add_to_prog(t_program *prog, struct section *ptr, int n)
{
	int		i;
	int		u;
	void	*tmp;

	u = -1;
	i = 0;
	if (prog->section == NULL)
		init_sec(prog, n);
	else
	{
		tmp = (struct section**)malloc(sizeof(struct section*)
				* (prog->nbsection + n));
		memcpy(tmp, prog->section, sizeof(struct section*) * prog->nbsection);
		prog->nbsection += n;
		free(prog->section);
		prog->section = tmp;
	}
	while (prog->section[i])
		i++;
	while (++u < n)
	{
		prog->section[i + u] = ptr;
		ptr = (struct section*)((char*)ptr + sizeof(struct section));
	}
}

void	create_seg_list(t_program *prog, struct segment_command *ptr)
{
	if (!ptr)
		return ;
	prog->section = 0;
	while (ptr->cmd == LC_SEGMENT)
	{
		if (ptr->nsects != 0)
			add_to_prog(prog, (struct section*)((char*)ptr +
						sizeof(struct segment_command)), ptr->nsects);
		ptr = (struct segment_command *)((char*)ptr + ptr->cmdsize);
	}
}

void	read_header_32(t_program *prog, char *ptr)
{
	struct mach_header	*header;
	void				*ptr2;
	t_list				*c;

	header = (struct mach_header *)ptr;
	prog->nb_loadcmds = header->ncmds;
	prog->header = header;
	prog->loadcmd = (void*)ptr + sizeof(struct mach_header);
	ptr2 = find_load_command(prog, (char*)prog->loadcmd,
			header->ncmds, LC_SYMTAB);
	create_seg_list(prog, find_load_command(prog, (char*)prog->loadcmd,
				header->ncmds, LC_SEGMENT));
	c = get_sym_list_32(prog, ptr2);
	print_list(prog, c, 32, header->filetype == MH_OBJECT);
}
