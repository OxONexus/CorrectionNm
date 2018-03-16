/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oread_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 14:38:04 by apaget            #+#    #+#             */
/*   Updated: 2018/03/15 17:37:34 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_list		*get_32symtab(t_program *prog, char *ptr, char *filename)
{
	struct ranlib		*t;
	int					size;
	int					n;
	t_list				*list;
	t_symbol			*symb;

	n = 4;
	size = *(int*)ptr;
	list = NULL;
	while (n < size)
	{
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

t_list		*get_64symtab(t_program *prog, char *ptr, char *filename)
{
	struct ranlib_64		*t;
	int						size;
	int						n;
	t_list					*list;
	t_symbol				*symb;

	list = NULL;
	n = 4;
	size = *(int*)ptr;
	while (n < size)
	{
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

char		*construct_name(char *n1, char *n2)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_strjoin(n1, "(");
	tmp2 = ft_strjoin(tmp1, n2);
	tmp3 = ft_strjoin(tmp2, ")");
	free(tmp1);
	free(tmp2);
	return (tmp3);
}

void		oread_lib_symtab(t_list *list, t_program *prog)
{
	char		*name;
	t_symbol	*tmp;
	t_program	nw;

	(void)prog;
	tmp = list->content;
	name = "asjfbcajskbdfaskjfbdsalj";
	while (list)
	{
		tmp = list->content;
		if (strcmp(name, tmp->name) != 0)
		{
			nw = *prog;
			odirect(&nw, (char*)tmp->addr + 0x50, tmp->name);
			name = tmp->name;
		}
		list = list->next;
	}
}

void		oread_lib(t_program *prog, char *ptr, char *filename)
{
	t_list *list;

	list = NULL;
	prog->start_prog = (void*)ptr;
	prog->endian = *(unsigned int*)ptr;
	if (filename)
	{
		ft_putstr("Archive : ");
		ft_putendl(filename);
	}
	if ((unsigned int)*(ptr + 0x38) > (unsigned)prog->load_size)
		exit(0);
	if (strncmp(ptr + 0x44, "__.SYMDEF", 9) == 0)
	{
		list = get_32symtab(prog, ptr + 0x58, filename);
		sorte_list_offset(prog, list);
		oread_lib_symtab(list, prog);
	}
	else if (strncmp(ptr + 0x44, "__.SYMDEF_64", 12) == 0)
	{
		list = get_64symtab(prog, ptr + 0x58, filename);
		sorte_list_offset(prog, list);
		oread_lib_symtab(list, prog);
	}
}
