/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lib3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 16:01:45 by apaget            #+#    #+#             */
/*   Updated: 2018/02/11 16:02:52 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char			*construct_name(char *n1, char *n2)
{
	char *tmp1;
	char *tmp2;
	char *tmp3;

	tmp1 = ft_strjoin(n1, "(");
	tmp2 = ft_strjoin(tmp1, n2);
	tmp3 = ft_strjoin(tmp2, ")");
	free(tmp1);
	free(tmp2);
	return (tmp3);
}

void			read_32symtab(t_program *prog, char *ptr, char *filename)
{
	int					n;
	t_program			tmp;
	char				*f;
	int					sizetab;
	int					*tab;

	n = 4;
	sizetab = 0;
	tab = 0;
	while (n < *(int*)ptr)
	{
		f = construct_name(filename, (char*)prog->start_prog +
				((struct ranlib*)(ptr + n))->ran_off + 0x3c);
		if (check_tab(&tab, &sizetab,
					((struct ranlib*)(ptr + n))->ran_off) == 0)
		{
			ft_bzero(&tmp, sizeof(tmp));
			direct(&tmp, get_ptr_header(prog->start_prog +
						((struct ranlib*)(ptr + n))->ran_off + 0x3c), f);
		}
		free(f);
		n += sizeof(struct ranlib);
	}
}

int				not_in_tab(t_list *list, char *name)
{
	t_symbol	*tmp;

	if (!list)
		return (1);
	while (list)
	{
		tmp = list->content;
		if (ft_strcmp(tmp->name, name) == 0)
			return (0);
		list = list->next;
	}
	return (1);
}
