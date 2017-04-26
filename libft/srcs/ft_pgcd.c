/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pgcd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:24:26 by abonneca          #+#    #+#             */
/*   Updated: 2016/11/07 13:32:47 by abonneca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_pgcd(int a, int b)
{
	int i;
	int pgcd;

	i = 1;
	while (i <= a || i <= b)
	{
		if (a % i == 0 && b % i == 0)
			pgcd = i;
		i++;
	}
	return (pgcd);
}
