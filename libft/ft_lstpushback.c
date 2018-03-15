/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 16:27:00 by amathias          #+#    #+#             */
/*   Updated: 2017/05/13 17:10:50 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list *begin, t_list *new)
{
	t_list *list;

	list = begin;
	while (list->next)
		list = list->next;
	list->next = new;
}
