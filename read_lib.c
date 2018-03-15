/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 14:56:02 by apaget            #+#    #+#             */
/*   Updated: 2018/03/15 17:37:12 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_list			*get_32symtab(t_program *prog, char *ptr, char *filename)
{
	struct ranlib	*t;
	int				n;
	t_program		tmp;
	t_list			*list;
	t_symbol		*symb;

	list = NULL;
	n = 4;
	while (n < *(int*)ptr)
	{
		ft_bzero(&tmp, sizeof(tmp));
		t = (struct ranlib*)(ptr + n);
		symb = (t_symbol*)malloc(sizeof(t_symbol));
		symb->name = construct_name(filename,
				(char*)prog->start_prog + t->ran_off + 0x3c);
		symb->addr = (unsigned long long)(char*)prog->start_prog + t->ran_off;
		if (not_in_tab(list, symb->name))
			lst_add(&list, symb, sizeof(t_symbol));
		n += sizeof(struct ranlib);
	}
	return (list);
}

t_list			*get_64symtab(t_program *prog, char *ptr, char *filename)
{
	struct ranlib_64	*t;
	int					n;
	t_program			tmp;
	t_list				*list;
	t_symbol			*symb;

	list = NULL;
	n = 4;
	while (n < *(int*)ptr)
	{
		ft_bzero(&tmp, sizeof(tmp));
		t = (struct ranlib_64*)(ptr + n);
		symb = (t_symbol*)malloc(sizeof(t_symbol));
		symb->name = construct_name(filename,
				(char*)prog->start_prog + t->ran_off + 0x3c);
		symb->addr = (unsigned long long)(char*)prog->start_prog + t->ran_off;
		if (not_in_tab(list, symb->name))
			lst_add(&list, symb, sizeof(t_symbol));
		n += sizeof(struct ranlib_64);
	}
	return (list);
}

void			read_64symtab(t_program *prog, char *ptr, char *filename)
{
	struct ranlib_64	*t;
	int					n;
	t_program			tmp;
	char				*f;

	n = 4;
	while (n < *(int*)ptr)
	{
		ft_bzero(&tmp, sizeof(tmp));
		t = (struct ranlib_64*)(ptr + n);
		f = construct_name(filename,
				(char*)prog->start_prog + t->ran_off + 0x3c);
		tmp.load_size = prog->load_size;
		direct(&tmp, (char*)prog->start_prog + t->ran_off + 0x50, f);
		free(f);
		n += sizeof(struct ranlib_64);
	}
}

void			read_lib_symtab(t_list *list, t_program *prog)
{
	char		*name;
	t_symbol	*tmp;
	t_program	nw;

	tmp = list->content;
	name = "asjfbcajskbdfaskjfbdsalj";
	(void)prog;
	while (list)
	{
		tmp = list->content;
		if (strcmp(name, tmp->name) != 0)
		{
			if (list)
				ft_putchar('\n');
			nw.load_size = prog->load_size;
			direct(&nw, (char*)tmp->addr + 0x50, tmp->name);
			name = tmp->name;
		}
		list = list->next;
	}
}

void			read_lib(t_program *prog, char *ptr, char *filename)
{
	t_list *list;

	list = NULL;
	prog->start_prog = (void*)ptr;
	prog->endian = *(unsigned int*)ptr;
	if ((unsigned int)*(ptr + 0x38) > (unsigned)prog->load_size)
		exit(0);
	if (strncmp(ptr + 0x44, "__.SYMDEF", 9) == 0)
	{
		list = get_32symtab(prog, ptr + 0x58, filename);
		sorte_list_offset(prog, list);
		read_lib_symtab(list, prog);
	}
	else if (strncmp(ptr + 0x44, "__.SYMDEF_64", 12) == 0)
	{
		list = get_64symtab(prog, ptr + 0x58, filename);
		sorte_list_offset(prog, list);
		read_lib_symtab(list, prog);
	}
}
