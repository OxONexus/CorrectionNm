/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oread_header3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 18:21:00 by apaget            #+#    #+#             */
/*   Updated: 2018/03/15 14:34:06 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void				*find_load_command(t_program *prog, char *ptr, int nb_loadcmds,
		unsigned int cmd)
{
	int						i;
	struct load_command		*loadcmd;

	i = 0;
	loadcmd = (struct load_command *)ptr;
	while (i < nb_loadcmds)
	{
		if (loadcmd->cmd == cmd)
			return (loadcmd);
		loadcmd = (void*)loadcmd + loadcmd->cmdsize;
		i++;
	}
	return (NULL);
}

void				*jerecherche(char *ptr, int nsect, char *name)
{
	int					i;
	struct section_64	*tmp;

	i = 0;
	tmp = (struct section_64 *)ptr;
	while (i < nsect)
	{
		if (strnstr(tmp->segname, name, ft_strlen(name)))
			return (tmp);
		tmp = (void*)tmp + sizeof(struct section_64);
		i++;
	}
	return (NULL);
}

void				*find_load_commandseg(char *ptr, int nb_loadcmds,
		unsigned int cmd, char *name)
{
	int							i;
	struct load_command			*loadcmd;
	struct segment_command_64	*sec;

	i = 0;
	loadcmd = (struct load_command *)ptr;
	while (i < nb_loadcmds)
	{
		if (loadcmd->cmd == cmd)
		{
			sec = (struct segment_command_64 *)loadcmd;
			if (ft_strlen(sec->segname) == 0)
			{
				if (jerecherche((void*)sec + sizeof(struct segment_command_64),
							sec->nsects, name) != NULL)
					return (sec);
				return (NULL);
			}
			if (strnstr(sec->segname, name, ft_strlen(name)))
				return (sec);
		}
		loadcmd = (void*)loadcmd + loadcmd->cmdsize;
		i++;
	}
	return (NULL);
}

void				*find_load_commandseg32(char *ptr, int nb_loadcmds,
		unsigned int cmd, char *name)
{
	int						i;
	struct load_command		*loadcmd;
	struct segment_command	*sec;

	i = 0;
	loadcmd = (struct load_command *)ptr;
	while (i < nb_loadcmds)
	{
		if (loadcmd->cmd == cmd)
		{
			sec = (struct segment_command *)loadcmd;
			if (strnstr(sec->segname, name, ft_strlen(name)))
				return (sec);
		}
		loadcmd = (void*)loadcmd + loadcmd->cmdsize;
		i++;
	}
	return (NULL);
}

void				print_code(char *ptr, uint64_t offset[2],
		unsigned int size, int type)
{
	unsigned int i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0 && type == 64)
			long_print(offset[1] + i, 16);
		else if (i % 16 == 0 && type == 32)
			long_print((unsigned)offset[1] + i, 8);
		long_print2(*(ptr + (unsigned)offset[0] + i) & 0xFF, 2);
		ft_putchar(' ');
		i++;
	}
	ft_putstr("\n");
}
