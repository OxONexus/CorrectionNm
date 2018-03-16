/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_what_i_need.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:09:01 by apaget            #+#    #+#             */
/*   Updated: 2018/03/15 17:42:04 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int check_ptr(t_program *prog, unsigned long ptr)
{
	if (ptr < (unsigned long)prog->start_prog ||
			ptr > (unsigned long)prog->start_prog + prog->load_size)
		exit(0);
	return 1;
}


void				lst_add(t_list **begin, void *content, int content_size)
{
	if (*begin == NULL)
		*begin = ft_lstnew(content, content_size);
	else
		ft_lstpushback(*begin, ft_lstnew(content, content_size));
}

void				swap_symb(t_symbol *s1, t_symbol *s2)
{
	t_symbol	tmp;

	tmp.name = s1->name;
	tmp.symb = s1->symb;
	tmp.addr = s1->addr;
	s1->name = s2->name;
	s1->addr = s2->addr;
	s1->symb = s2->symb;
	s2->addr = tmp.addr;
	s2->symb = tmp.symb;
	s2->name = tmp.name;
}

void				sorte_list_offset(t_program *prog, t_list *list)
{
	void		*save;
	t_symbol	*s1;
	t_symbol	*s2;
	int			i;

	i = 0;
	save = list;
	while (list && list->next)
	{
		s1 = list->content;
		s2 = list->next->content;

		if (ft_strncmp(prog->start_prog, "!<arch>", 7) != 0) {
			check_ptr(prog, (unsigned long)s1->name);
			check_ptr(prog, (unsigned long)s2->name);
		}
		if (s1->addr > s2->addr)
		{
			swap_symb(s1, s2);
			list = save;
			i = 0;
		}
		else
		{
			i++;
			list = list->next;
		}
	}
}

void				sorte_list(t_program *prog, t_list *list)
{
	void		*save;
	t_symbol	*s1;
	t_symbol	*s2;
	int			i;

	save = list;
	i = 0;
	while (list && list->next)
	{
		s1 = list->content;
		s2 = list->next->content;
		if (ft_strncmp(prog->start_prog, "!<arch>", 7) != 0) {
			check_ptr(prog, (unsigned long)s1->name);
			check_ptr(prog, (unsigned long)s2->name);
		}
		if (ft_strcmp(s1->name, s2->name) > 0)
		{
			swap_symb(s1, s2);
			list = save;
			i = 0;
		}
		else
		{
			i++;
			list = list->next;
		}
	}
}

struct section		*get_n_sec(t_program *prog, int i)
{
	int					u;
	struct section		*tmp;

	u = 0;
	tmp = *prog->section;
	if (i < 0 || i > prog->nbsection)
		return (NULL);
	while (u < prog->nbsection)
	{
		if (i == u)
			return (tmp);
		u++;
		tmp = (struct section *)((char*)tmp + sizeof(struct section));
	}
	return (NULL);
}
