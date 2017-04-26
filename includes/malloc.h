/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 12:05:12 by abonneca          #+#    #+#             */
/*   Updated: 2017/04/26 19:35:09 by abonneca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include "../libft/includes/libft.h"
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <string.h>

# define N 1024
# define M 6 * 1024
# define NBR_ALLOCS 128

typedef struct		s_zone
{
	size_t			size;
	struct s_zone	*map;
	struct s_zone	*next;
	struct s_zone	*prev;
	char			free:1;
	char			is_new:1;
}					t_zone;

typedef struct		s_zones
{
	size_t			tiny_sizes;
	size_t			small_sizes;
	void			*tiny_zones;
	void			*small_zones;
	void			*large_zones;
}					t_zones;

extern		t_zones g_zones;

void				*malloc(size_t size);
void				free(void *ptr);
size_t				get_page_size(size_t size);
void				*new_page(t_zone *zone_ptr, size_t size, t_zone *prev);
void				*get_page_start(t_zone *ptr);
t_zone				*is_valid_zone(t_zone *zone_ptr, void *ptr);
char				valid_offset(t_zone *ptr, size_t size);
void				hex_min(uintmax_t v, unsigned int b);
void				show_alloc_mem(void);

#endif
