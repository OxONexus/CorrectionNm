/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oread_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 18:21:00 by apaget            #+#    #+#             */
/*   Updated: 2018/02/11 14:32:28 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void				oread_header_64(t_program *prog, char *ptr)
{
	struct mach_header_64		*header;
	struct segment_command_64	*ptr2;
	struct section_64			*ptr3;
	uint64_t					opt[3];
	char 						*arg[2];

	header = (struct mach_header_64 *)ptr;
	prog->nb_loadcmds = header->ncmds;
	prog->header = header;
	prog->loadcmd = (void*)ptr + sizeof(struct mach_header_64);
	arg[0] = (char *)prog->loadcmd;
	arg[1] = "__TEXT";
	ptr2 = find_load_commandseg(prog, arg, header->ncmds,
			LC_SEGMENT_64);
	check_ptr(prog, (unsigned long)ptr2);
	ptr3 = find_sub_segment((void*)ptr2 + sizeof(struct segment_command_64),
			prog, ptr2->nsects, "__text");
	check_ptr(prog, (unsigned long)ptr3);
	ft_putstr("Contents of (__TEXT,__text) section");
	opt[0] = ptr3->offset;
	opt[1] = ptr3->addr;
	opt[2] = ptr3->size;
	print_code(prog, (char*)ptr, opt,64);
}

void				oread_header_32(t_program *prog, char *ptr)
{
	struct mach_header		*header;
	struct segment_command	*ptr2;
	struct section			*ptr3;
	uint64_t				opt[3];

	header = (struct mach_header *)ptr;
	prog->nb_loadcmds = header->ncmds;
	prog->header = header;
	prog->loadcmd = (void*)ptr + sizeof(struct mach_header);
	ptr2 = find_load_commandseg32((char*)prog->loadcmd, header->ncmds,
			LC_SEGMENT, "__TEXT");
	check_ptr(prog, (unsigned long)ptr2);
	ptr3 = find_sub_segment32((void*)ptr2 + sizeof(struct segment_command),
			prog, ptr2->nsects, "__text");

	check_ptr(prog, (unsigned long)ptr3);
	ft_putstr("Contents of (__TEXT,__text) section");
	opt[0] = ptr3->offset;
	opt[1] = ptr3->addr;
	opt[2] = ptr3->size;
	print_code(prog, (char*)ptr, opt, 32);
}
