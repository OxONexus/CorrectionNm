/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:45:36 by apaget            #+#    #+#             */
/*   Updated: 2017/06/21 16:32:21 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		odirect(t_program *prog, char *ptr, char *name)
{
	unsigned int magic;

	prog->start_prog = (void*)ptr;
	magic = *(unsigned int*)ptr;
	prog->endian = *(unsigned int*)ptr;
	if (ft_strncmp(ptr, "!<arch>", 7) == 0)
		oread_lib(prog, ptr, name);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
	{
		print_name(name);
		oread_header_64(prog, ptr);
	}
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
	{
		print_name(name);
		oread_header_32(prog, ptr);
	}
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
	{
		print_name(name);
		oread_fat_head(prog, ptr);
	}
	else
		ft_putstr("Bad input file formatn\n");
}

int			read_file(char *file)
{
	int				fd;
	struct stat		buf;
	char			*ptr;
	t_program		prog;

	fd = open(file, O_RDONLY);
	fstat(fd, &buf);
	if (buf.st_size == 0)
	{
		ft_putstr("failed to open this file\n");
		exit(0);
	}
	ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
		exit(0);
	prog.start_prog = ptr;
	prog.load_size = buf.st_size;
	odirect(&prog, ptr, file);
	return (0);
}

int			main(int argc, char *argv[])
{
	int i;

	i = 1;
	while (i < argc)
	{
		read_file(argv[i]);
		i++;
	}
	return (0);
}
