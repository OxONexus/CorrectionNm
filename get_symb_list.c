/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symb_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:09:01 by apaget            #+#    #+#             */
/*   Updated: 2018/03/15 16:08:51 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void			check_data(t_program *prog)
{
	if (((char*)prog->start_stringtable - (char*)prog->start_prog >
				(unsigned int)((char *)(prog->start_prog + 38)) &&
				ft_strncmp(prog->start_prog, "!<arch>", 7) != 0))
		exit(0);
	if (prog->load_size < prog->start_stringtable - (char*)prog->start_prog)
		exit(0);
}

t_list			*get_sym_list(t_program *prog, char *ptr)
{
	t_list				*list;
	t_symbol			*tmp;
	unsigned int		i;

	i = 0;
	prog->symtabcmds = (struct symtab_command*)ptr;
	prog->symtab_array = (void*)prog->start_prog + endian_read(prog,
			prog->symtabcmds->symoff);
	prog->nb_symtabcmds = endian_read(prog, prog->symtabcmds->nsyms);
	prog->start_stringtable = (void*)prog->start_prog +
		endian_read(prog, prog->symtabcmds->stroff);
	list = NULL;
	check_data(prog);
	while (i < prog->symtabcmds->nsyms)
	{
		if((tmp = (t_symbol*)malloc(sizeof(t_symbol))) == NULL)
			exit (0);
		tmp->name = prog->start_stringtable +
			endian_read(prog, prog->symtab_array[i].n_un.n_strx);
		tmp->symb = get_symb(prog, i);
		tmp->addr = endian_read(prog, prog->symtab_array[i].n_value);
		if (!(prog->symtab_array[i].n_type & N_STAB))
			lst_add(&list, tmp, sizeof(t_symbol));
		i++;
	}
	return (list);
}

t_list			*get_sym_list_32(t_program *prog, char *ptr)
{
	t_list			*list;
	t_symbol		*tmp;
	unsigned int	i;

	i = 0;
	prog->symtabcmds = (struct symtab_command*)ptr;
	prog->symtab_array2 = (void*)prog->start_prog + prog->symtabcmds->symoff;
	prog->nb_symtabcmds = prog->symtabcmds->nsyms;
	prog->start_stringtable = (void*)prog->start_prog +
		prog->symtabcmds->stroff;
	check_data(prog);
	list = NULL;
	while (i < prog->symtabcmds->nsyms)
	{
		tmp = (t_symbol*)malloc(sizeof(t_symbol));
		tmp->name = prog->start_stringtable +
			prog->symtab_array2[i].n_un.n_strx;
		tmp->symb = get_symb32(prog, i);
		tmp->addr = prog->symtab_array2[i].n_value;
		lst_add(&list, tmp, sizeof(t_symbol));
		i++;
	}
	return (list);
}
