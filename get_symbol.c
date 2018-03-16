/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:09:01 by apaget            #+#    #+#             */
/*   Updated: 2018/02/11 14:10:51 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		get_32sec(t_program *prog, int i, char *tmp)
{
	struct section		*a;
	int					n_ext;

	n_ext = (prog->symtab_array2[i].n_type & N_EXT);
	a = 0;
	if (prog->symtab_array2[i].n_sect < 1 ||
			prog->symtab_array2[i].n_sect >= prog->nbsection)
		*tmp = n_ext ? 'S' : 's';
	a = prog->section[prog->symtab_array2[i].n_sect - 1];
	check_ptr(prog, (unsigned long)a->segname);
	check_ptr(prog, (unsigned long)a->segname);
	if (a && ft_strcmp(a->segname, "__DATA") == 0)
		if (ft_strcmp(a->sectname, "__data") == 0)
			*tmp = n_ext ? 'D' : 'd';
		else if (a && ft_strcmp(a->sectname, "__bss") == 0)
			*tmp = n_ext ? 'B' : 'b';
		else
			*tmp = n_ext ? 'S' : 's';
	else if (a && ft_strcmp(a->segname, "__TEXT") == 0)
	{
		if (a && ft_strcmp(a->sectname, "__text") == 0)
			*tmp = n_ext ? 'T' : 't';
		else
			*tmp = n_ext ? 'S' : 's';
	}
	else
		*tmp = n_ext ? 'S' : 's';
}

char		get_symb32(t_program *prog, int i)
{
	char				tmp;
	struct section		*a;

	a = 0;
	tmp = 0;
	if ((prog->symtab_array2[i].n_type & N_TYPE) == N_UNDF)
		tmp = 'U';
	else if ((prog->symtab_array2[i].n_type & N_TYPE) == N_ABS)
		tmp = 'A';
	else if ((prog->symtab_array2[i].n_type & N_TYPE) == N_INDR)
		tmp = 'I';
	else if (prog->symtab_array2[i].n_sect == 0)
		tmp = '2';
	else if ((prog->symtab_array2[i].n_type & N_TYPE) == N_SECT)
		get_32sec(prog, i, &tmp);
	return (tmp);
}

void		get_sec(t_program *prog, int i, char *tmp)
{
	int					n_ext;
	struct section_64	*a;

	a = 0;
	n_ext = (prog->symtab_array[i].n_type & N_EXT);
	if (prog->symtab_array[i].n_sect < 1 ||
			prog->symtab_array[i].n_sect >= prog->nbsection_64)
		*tmp = n_ext ? 'S' : 's';
	a = prog->section_64[prog->symtab_array[i].n_sect - 1];
	check_ptr(prog, (unsigned long)a->segname);
	check_ptr(prog, (unsigned long)a->segname);
	if (a && ft_strcmp(a->segname, "__DATA") == 0)
		if (ft_strcmp(a->sectname, "__data") == 0)
			*tmp = n_ext ? 'D' : 'd';
		else if (a && ft_strcmp(a->sectname, "__bss") == 0)
			*tmp = n_ext ? 'B' : 'b';
		else
			*tmp = n_ext ? 'S' : 's';
	else if (a && ft_strcmp(a->segname, "__TEXT") == 0)
		if (a && ft_strcmp(a->sectname, "__text") == 0)
			*tmp = n_ext ? 'T' : 't';
		else
			*tmp = n_ext ? 'S' : 's';
	else
		*tmp = n_ext ? 'S' : 's';
}

char		get_symb(t_program *prog, int i)
{
	char tmp;

	tmp = 0;
	if ((prog->symtab_array[i].n_type & N_STAB) == 0)
		tmp = 'w';
	if ((prog->symtab_array[i].n_type & N_TYPE) == N_UNDF)
		tmp = 'U';
	else if ((prog->symtab_array[i].n_type & N_TYPE) == N_ABS)
		tmp = 'A';
	if ((prog->symtab_array[i].n_type & N_TYPE) == N_SECT)
		get_sec(prog, i, &tmp);
	if ((prog->symtab_array[i].n_type & N_TYPE) == N_INDR)
		tmp = 'I';
	return (tmp);
}
