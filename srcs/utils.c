/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 17:22:03 by abonneca          #+#    #+#             */
/*   Updated: 2017/04/26 19:15:17 by abonneca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	hex_min(uintmax_t v, unsigned int b)
{
	char	*base;

	base = "0123456789abcdef";
	if (v >= b)
		hex_min(v / b, b);
	write(1, &base[v % b], 1);
}

size_t	get_page_size(size_t size)
{
	size_t	rounded_size;
	size_t	pagesize;

	pagesize = getpagesize();
	if (size <= N)
	{
		if ((rounded_size = NBR_ALLOCS * (N + sizeof(t_zone))) % pagesize)
			rounded_size = ((rounded_size / pagesize) + 1) * pagesize;
		if (!g_zones.tiny_sizes)
			g_zones.tiny_sizes = rounded_size;
		return (rounded_size);
	}
	else if (size <= M)
	{
		if ((rounded_size = NBR_ALLOCS * (M + sizeof(t_zone))) % pagesize)
			rounded_size = ((rounded_size / pagesize) + 1) * pagesize;
		if (!g_zones.small_sizes)
			g_zones.small_sizes = rounded_size;
		return (rounded_size);
	}
	else
		return (size + sizeof(t_zone));
}

void	*new_page(t_zone *zone_ptr, size_t size, t_zone *prev)
{
	void	*new_page;
	size_t	size_proj;

	size_proj = get_page_size(size);
	if ((new_page = mmap(0, size_proj, PROT_READ | PROT_WRITE,
					MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	if (!zone_ptr)
	{
		if (size <= N)
			g_zones.tiny_zones = new_page;
		else if (size <= M)
			g_zones.small_zones = new_page;
		else
			g_zones.large_zones = new_page;
	}
	((t_zone *)new_page)->map = new_page;
	((t_zone *)new_page)->size = size;
	((t_zone *)new_page)->next = NULL;
	((t_zone *)new_page)->prev = prev;
	((t_zone *)new_page)->free = 0;
	((t_zone *)new_page)->is_new = 1;
	((t_zone *)new_page)->checksum = 42;
	return (new_page);
}
