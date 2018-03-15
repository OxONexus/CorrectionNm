/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:09:01 by apaget            #+#    #+#             */
/*   Updated: 2018/03/15 17:05:37 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		print_empty(char c, char *s, int size)
{
	int i;

	i = -1;
	while (++i < size + 1)
		ft_putchar(' ');
	ft_putchar(c);
	ft_putchar(' ');
	ft_putstr(s);
	ft_putchar('\n');
}

void		print_empty2(unsigned long a, char c, char *s, int size)
{
	long_print2(a, size);
	ft_putchar(' ');
	ft_putchar(c);
	ft_putchar(' ');
	ft_putstr(s);
	ft_putchar('\n');
}

void		print_list(t_program *prog, t_list *list, int type, int print0)
{
	t_symbol	*tmp;

	sorte_list(prog, list);
	while (list)
	{
		tmp = list->content;
		if (!strstr(tmp->name, "radr://") && type == 32)
		{
			if ((print0 && (tmp->symb == 'T' || tmp->symb == 't')
						&& tmp->addr == 0) || tmp->addr)
				print_empty2((unsigned long)tmp->addr,
						tmp->symb, tmp->name, 8);
			else
				print_empty(tmp->symb, tmp->name, 8);
		}
		else if (!strstr(tmp->name, "radr://"))
		{
			if ((print0 && (tmp->symb == 'T' || tmp->symb == 't')
						&& tmp->addr == 0) || tmp->addr)
				print_empty2(tmp->addr, tmp->symb, tmp->name, 16);
			else
				print_empty(tmp->symb, tmp->name, 16);
		}
		list = list->next;
	}
}
