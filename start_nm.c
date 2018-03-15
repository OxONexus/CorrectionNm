/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 18:28:43 by apaget            #+#    #+#             */
/*   Updated: 2018/02/11 14:53:07 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#define FAT_MAGIC   0xcafebabe
#define FAT_CIGAM   0xbebafeca

void			direct(t_program *prog, char *ptr, char *name)
{
	unsigned int	magic;

	prog->start_prog = (void*)ptr;
	magic = *(unsigned int*)ptr;
	prog->endian = *(unsigned int*)ptr;
	if (ft_strncmp(ptr, "!<arch>", 7) == 0)
		read_lib(prog, ptr, name);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
	{
		if (name)
			print_name(name);
		read_header_64(prog, ptr);
	}
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
	{
		if (name)
			print_name(name);
		read_header_32(prog, ptr);
	}
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
	{
		if (name)
			print_name(name);
		read_fat_head(prog, ptr);
	}
}

int				read_file2(char *file, int isprint)
{
	int				fd;
	struct stat		buf;
	char			*ptr;
	t_program		prog;

	ft_bzero(&prog, sizeof(prog));
	fd = open(file, O_RDONLY);
	fstat(fd, &buf);
	if (buf.st_size < 8200 || fd < 0)
		return (0);
	ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
	{
		ft_putstr("map failed\n");
		exit(0);
	}
	prog.start_prog = ptr;
	prog.load_size = buf.st_size;
	if (isprint || strncmp(ptr, "!<arch>", 7) == 0)
		direct(&prog, ptr, file);
	else
		direct(&prog, ptr, NULL);
	close(fd);
	munmap(ptr, buf.st_size);
	return (0);
}

int				main(int argc, char *argv[])
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (argc != 2)
			ft_putstr("\n");
		read_file2(argv[i], argc > 2 ? 1 : 0);
		i++;
	}
	return (0);
}
