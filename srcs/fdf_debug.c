/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:37:33 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/14 23:24:33 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	**to_print(t_map_meta *meta, int selector)
{
	if (selector == 1)
		return (meta->map);
	else if (selector == 2)
		return (meta->map_color);
	else if (selector == 3)
		return (meta->coor_x);
	else if (selector == 4)
		return (meta->coor_y);
	else
		return (NULL);
}

static float	**to_print_prime(t_map_meta *meta, int selector)
{
	if (selector == 5)
		return (meta->coor_xp);
	else if (selector == 6)
		return (meta->coor_yp);
	else
		return (NULL);
}

void	meta_map_print(t_map_meta *meta, int selector)
{
	int	height;
	int	width;
	int	**print;

	height = 0;
	print = to_print(meta, selector);
	ft_printf("BOD\n");
	if (print)
	{
		while (height < meta->height)
		{
			width = 0;
			while (width < meta->width)
			{
				if (selector == 2)
					ft_printf("%X\t", print[height][width]);
				else
					ft_printf("%d\t", print[height][width]);
				width++;
			}
			ft_printf("\n");
			height++;
		}
	}
	ft_printf("EOD\n");
}

void	meta_map_print_prime(t_map_meta *meta, int selector)
{
	int		height;
	int		width;
	float	**print;

	height = 0;
	print = to_print_prime(meta, selector);
	printf("BOD\n");
	if (print)
	{
		while (height < meta->height)
		{
			width = 0;
			while (width < meta->width)
			{
				printf("%f\t", print[height][width]);
				width++;
			}
			printf("\n");
			height++;
		}
	}
	printf("EOD\n");
}
