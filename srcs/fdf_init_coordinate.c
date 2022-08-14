/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_coordinate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:27:48 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/14 22:46:18 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	coord_assign(t_map_meta *meta)
{
	int	height;
	int	width;

	height = -1;
	while (++height < meta->height)
	{
		width = -1;
		while (++width < meta->width)
		{
			meta->coor_x[height][width] = width * meta->zoom;
			meta->coor_y[height][width] = height * meta->zoom;
		}
	}
}

void	coord_assign_prime(t_map_meta *meta)
{
	int		height;
	int		width;
	float	x;
	float	y;
	float	z;

	height = -1;
	while (++height < meta->height)
	{
		width = -1;
		while (++width < meta->width)
		{
			x = meta->coor_x[height][width] - (meta->width * meta->zoom / 2);
			y = meta->coor_y[height][width] - (meta->height * meta->zoom / 2);
			z = 0;
			if (meta->is_iso)
				z = meta->map[height][width] * meta->scale * meta->zoom;
			// meta->coor_xp[height][width] = (x - y) * cos(meta->angle);
			// meta->coor_yp[height][width] = (x + y) * sin(meta->angle) - z;
			meta->coor_xp[height][width] = (x * cos(meta->angle)) - \
				(y * sin(meta->angle));
			meta->coor_yp[height][width] = (x * sin(meta->angle)) + \
				(y * sin(meta->angle)) - z;
		}
	}
}
