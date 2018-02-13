/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 16:50:10 by abonneca          #+#    #+#             */
/*   Updated: 2017/04/26 19:12:29 by abonneca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdio.h>

t_zones g_zones = {0, 0, NULL, NULL, NULL};

void	*get_page_start(t_zone *ptr)
{
	while (ptr->prev && !ptr->is_new)
		ptr = ptr->prev;
	return (ptr);
}

void	update_ptr(t_zone *ptr, t_zone *prev, char is_new, size_t size)
{
	ptr->prev = prev;
	ptr->is_new = is_new;
	ptr->size = size;
	ptr->free = 0;
	ptr->checksum = calculate_checksum(ptr);
}

char	valid_offset(t_zone *ptr, size_t size)
{
	t_zone	*page_start;
	size_t	offset;

	if (ptr->next && ptr->next->map == ptr->map)
	{
		if ((unsigned long)ptr->next > (unsigned long)ptr)
			offset = (unsigned long)ptr->next - (unsigned long)ptr;
		else
			offset = (unsigned long)ptr - (unsigned long)ptr->next;
		offset -= (16 - offset % 16);
		//test for padding
		if (offset >= sizeof(t_zone) + size)
			return (1);
		return (0);
	}
	else
	{
		page_start = get_page_start(ptr);
		if ((unsigned long)ptr > (unsigned long)page_start)
			offset = (unsigned long)ptr - (unsigned long)page_start;
		else
			offset = (unsigned long)page_start - (unsigned long)ptr;
		offset -= (16 - offset % 16);
		//test for padding
		if (get_page_size(size) > offset && (get_page_size(size) -
					offset >= ptr->size + size + 2 * sizeof(t_zone)))
			return (1);
		return (0);
	}
}

void	*find_zone(t_zone *zone_ptr, size_t size)
{
	void *addr;
	if (zone_ptr)
	{
		while (!checksum(zone_ptr) && zone_ptr->next)
		{
			if (checksum(zone_ptr))
				return(NULL);
			if (zone_ptr->free && valid_offset(zone_ptr, size))
			{
				update_ptr(zone_ptr, zone_ptr->prev, zone_ptr->is_new, size);
				return ((void *)zone_ptr + (16 - ((long int)zone_ptr + sizeof(t_zone))% 16) +sizeof(t_zone));
			}
			zone_ptr = zone_ptr->next;
		}
		if (checksum(zone_ptr))
			return(NULL);
		if (valid_offset(zone_ptr, size))
		{
			zone_ptr->next = (void *)zone_ptr + zone_ptr->size + sizeof(t_zone);
			((t_zone *)zone_ptr)->next->map = get_page_start(zone_ptr);
			//same here for checksum
			update_ptr(zone_ptr->next, zone_ptr, 0, size);
			update_ptr(zone_ptr, zone_ptr->prev, zone_ptr->is_new, zone_ptr->size);
			return ((void *)(zone_ptr->next) + (16 - ((long int)(zone_ptr->next) + sizeof(t_zone)) % 16) + sizeof(t_zone));
		}
		zone_ptr->next = new_page(zone_ptr, size, NULL);
		((t_zone *)zone_ptr)->next->map = ((t_zone *)zone_ptr)->next;
		// interchanged lines to intro checksum
		update_ptr(zone_ptr->next, zone_ptr, 1, size);
		update_ptr(zone_ptr, zone_ptr->prev, zone_ptr->is_new, zone_ptr->size);
		return ((16 - ((long int)(zone_ptr->next) + sizeof(t_zone)) % 16) + (void *)(zone_ptr->next) + sizeof(t_zone));
	}
	else
	{	
		addr = new_page(zone_ptr, size, NULL);
		//update_ptr(zone_ptr, zone_ptr->prev, zone_ptr->is_new, zone_ptr->size);
		return (addr + (16 - ((long int)addr + sizeof(t_zone)) % 16) + sizeof(t_zone));
	}
}

void	*malloc(size_t size)
{
	if (size > 0)
	{
		if (size <= N)
			return (find_zone(g_zones.tiny_zones, size));
		else if (size <= M)
			return (find_zone(g_zones.small_zones, size));
		else
			return (find_zone(g_zones.large_zones, size));
	}
	else
		return (NULL);
}
