/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:10:10 by abonneca          #+#    #+#             */
/*   Updated: 2017/04/22 17:15:59 by abonneca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdio.h>

void	show_full_alloc_zone(t_zone *ptr, size_t *i)
{
	hex_min((intmax_t)ptr, 16);
	ft_putchar('\n');
	while (ptr)
	{
		ft_putstr("0x");
		hex_min((intmax_t)((char *)ptr + sizeof(t_zone)), 16);
		ft_putstr(" - 0x");
		hex_min((intmax_t)((char *)ptr + sizeof(t_zone) + ptr->size), 16);
		ft_putstr(" : ");
		ft_putnbr(ptr->size);
		ft_putstr(" octets\n");
		ft_putstr("ptr->next: 0x");
		hex_min((intmax_t)((char *)ptr->next), 16);
		ft_putstr("\nptr->prev: 0x");
		hex_min((intmax_t)((char *)ptr->prev), 16);
		ft_putstr("\nptr->free: ");
		ft_putnbr(ptr->free);
		ft_putstr("\nptr->is_new: ");
		ft_putnbr(ptr->is_new);
		ft_putchar('\n');
		*i += ptr->size;
		ptr = ptr->next;
	}
}

void	show_alloc_mem_ex(void)
{
	size_t i;

	i = 0;
	if (g_zones.tiny_zones)
	{
		ft_putstr("TINY : 0x");
		show_full_alloc_zone(g_zones.tiny_zones, &i);
	}
	if (g_zones.small_zones)
	{
		ft_putstr("SMALL : 0x");
		show_full_alloc_zone(g_zones.small_zones, &i);
	}
	if (g_zones.large_zones)
	{
		ft_putstr("LARGE : 0x");
		show_full_alloc_zone(g_zones.large_zones, &i);
	}
	ft_putstr("Total : ");
	ft_putnbr(i);
	ft_putchar('\n');
}

void	show_alloc_zone(t_zone *ptr, size_t *i)
{
	hex_min((intmax_t)ptr, 16);
	ft_putchar('\n');
	while (ptr)
	{
		ft_putstr("0x");
		hex_min((intmax_t)((char *)ptr + sizeof(t_zone)), 16);
		ft_putstr(" - 0x");
		hex_min((intmax_t)((char *)ptr + sizeof(t_zone) + ptr->size), 16);
		ft_putstr(" : ");
		ft_putnbr(ptr->size);
		ft_putstr(" octets\n");
		*i += ptr->size;
		ptr = ptr->next;
	}
}

void	show_alloc_mem(void)
{
	size_t i;

	i = 0;
	if (g_zones.tiny_zones)
	{
		ft_putstr("TINY : 0x");
		show_alloc_zone(g_zones.tiny_zones, &i);
	}
	if (g_zones.small_zones)
	{
		ft_putstr("SMALL : 0x");
		show_alloc_zone(g_zones.small_zones, &i);
	}
	if (g_zones.large_zones)
	{
		ft_putstr("LARGE : 0x");
		show_alloc_zone(g_zones.large_zones, &i);
	}
	printf("Total : %zu", i);
}
