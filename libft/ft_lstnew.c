/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:25:28 by amathias          #+#    #+#             */
/*   Updated: 2017/05/13 16:36:45 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *list;

	list = NULL;
	if ((list = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content)
	{
		if ((list->content = malloc(content_size)) == NULL)
			return (NULL);
		list->content = ft_memcpy(list->content, content, content_size);
		list->content_size = content_size;
		list->next = NULL;
	}
	else
	{
		list->content = NULL;
		list->content_size = 0;
		list->next = NULL;
	}
	return (list);
}
