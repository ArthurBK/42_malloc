/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:26:04 by abonneca          #+#    #+#             */
/*   Updated: 2017/04/26 18:25:13 by abonneca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_zone	*is_valid_zone(t_zone *zone_ptr, void *ptr)
{
	if (zone_ptr)
	{
		while (zone_ptr->next)
		{
			if ((void *)zone_ptr + sizeof(t_zone) == ptr)
				return (zone_ptr);
			zone_ptr = zone_ptr->next;
		}
		if ((void *)zone_ptr + sizeof(t_zone) == ptr)
			return (zone_ptr);
	}
	return (NULL);
}

t_zone	*check_prev(t_zone *ptr)
{
	while (ptr->prev)
	{
		if (!ptr->free)
			return (NULL);
		if (ptr->is_new)
			break ;
		ptr = ptr->prev;
	}
	if (!ptr->free)
		return (NULL);
	if (ptr->prev)
		ptr->prev->next = NULL;
	return (ptr);
}

t_zone	*is_last(t_zone *ptr)
{
	t_zone *init_ptr;

	init_ptr = ptr;
	if (ptr)
	{
		while (ptr->next && !ptr->next->is_new)
		{
			if (!ptr->free)
				return (NULL);
			ptr = ptr->next;
		}
		if (!ptr->free)
			return (NULL);
		return (check_prev(init_ptr));
	}
	return (ptr);
}

void	free(void *ptr)
{
	t_zone *zone_ptr;
	t_zone *zone_first;

	if (ptr)
	{
		if ((zone_ptr = is_valid_zone(g_zones.tiny_zones, ptr))
				|| (zone_ptr = is_valid_zone(g_zones.small_zones, ptr))
				|| (zone_ptr = is_valid_zone(g_zones.large_zones, ptr)))
		{
			zone_ptr->free = 1;
			if ((zone_first = is_last(zone_ptr)))
			{
				if (munmap(zone_first, get_page_size(zone_first->size)) < 0)
					return ;
				if (g_zones.tiny_zones == zone_first)
					g_zones.tiny_zones = NULL;
				if (g_zones.small_zones == zone_first)
					g_zones.small_zones = NULL;
			}
		}
	}
}
