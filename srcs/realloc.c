/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:47:42 by abonneca          #+#    #+#             */
/*   Updated: 2017/04/26 19:14:24 by abonneca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*realloc_zone(t_zone *zone_ptr, void *ptr, size_t size)
{
	t_zone	*zone_src;
	t_zone	*page_ptr;
	t_zone	*dest;
	char	large;

	large = g_zones.large_zones == zone_ptr ? 1 : 0;
	if (!(zone_src = is_valid_zone(zone_ptr, ptr)))
		return (malloc(size));
	page_ptr = get_page_start(zone_src);
	if (!large && valid_offset(zone_src, size))
	{
		zone_src->size = size;
		zone_src->free = 0;
		return ((void *)zone_src + sizeof(t_zone));
	}
	else
	{
		dest = malloc(size);
		size = size < ((t_zone *)(ptr - sizeof(t_zone)))->size ? size : ((t_zone *)(ptr - sizeof(t_zone)))->size;
		ft_memcpy((void *)dest, (void *)zone_src, size);
		free((void *)zone_src);
		return ((void *)dest);
	}
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));
	if (size > 0)
	{
		if (size < N)
			return (realloc_zone(g_zones.tiny_zones, ptr, size));
		else if (size < M)
			return (realloc_zone(g_zones.small_zones, ptr, size));
		else
			return (realloc_zone(g_zones.large_zones, ptr, size));
	}
	return (NULL);
}
