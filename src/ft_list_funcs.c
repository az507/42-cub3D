/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:38:38 by achak             #+#    #+#             */
/*   Updated: 2024/07/03 13:01:02 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static t_cub_list	*ft_create_elem(void *data)
{
	t_cub_list	*new_elem;

	new_elem = malloc(sizeof(t_cub_list));
	if (!new_elem)
		return (perror("malloc"), NULL);
	new_elem->next = NULL;
	new_elem->data = data;
	return (new_elem);
}

int	ft_list_size(t_cub_list *begin_list)
{
	int	size;

	size = 0;
	while (begin_list)
	{
		size++;
		begin_list = begin_list->next;
	}
	return (size);
}

void	ft_list_clear(t_cub_list *begin_list, void (*free_fct)(void *))
{
	t_cub_list	*temp;

	temp = NULL;
	while (begin_list)
	{
		temp = begin_list->next;
		(*free_fct)(begin_list->data);
		(*free_fct)(begin_list);
		begin_list = temp;
	}
}

void	ft_list_push_back(t_params *params, int fd, t_cub_list **begin_list,
		void *data)
{
	t_cub_list			*new_node;
	static t_cub_list	*tail_ptr = NULL;

	if (!begin_list)
		return ;
	if (params->done_parsing_map == true)
		return (free(data), get_next_line(CLEANUP), close(fd),
			ft_error(params, "Extra newlines in map\n"));
	new_node = ft_create_elem(data);
	if (!new_node)
		return (ft_list_clear(*begin_list, &free), free(data),
			get_next_line(CLEANUP), close(fd), *begin_list = NULL,
			ft_error(params, "List node malloc fail\n"));
	if (!*begin_list)
		*begin_list = new_node;
	else
		tail_ptr->next = new_node;
	tail_ptr = new_node;
}
