/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:33:00 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/14 23:15:41 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
Rotating X
x' = x'
y' = (y' * cos(meta->rot_roll)) - (z * sin(meta->rot_roll));
z = (z * sin(meta->rot_roll) * meta->scale * meta->zoom) + \
	(z * cos(meta->rot_roll) * meta->scale * meta->zoom);

Rotating Y
// meta->map[height][width] = (cos(meta->rot_roll) * meta->scale * meta->zoom);
// meta->coor_yp[height][width] = (y * cos(meta->rot_roll)) - \
// 	(z * sin(meta->rot_roll));
// meta->map[height][width] = (z * sin(meta->rot_roll) * meta->scale * meta->zoom) + \
// 	(z * cos(meta->rot_roll) * meta->scale * meta->zoom);

Rotating Z
meta->coor_xp[height][width] = (x * cos(meta->rot_yaw)) - \
	(y * sin(meta->rot_yaw));
meta->coor_yp[height][width] = (x * sin(meta->rot_yaw)) + \
	(y * cos(meta->rot_yaw));
*/

void	fdf_rotate_map_yaw(t_map_meta *meta)
{
	int		height;
	int		width;
	float	x;
	float	y;

	height = -1;
	while (++height < meta->height)
	{
		width = -1;
		while (++width < meta->width)
		{
			x = meta->coor_xp[height][width];
			y = meta->coor_yp[height][width];
			meta->coor_xp[height][width] = (x * cos(meta->rot_yaw)) - \
				(y * sin(meta->rot_yaw));
			meta->coor_yp[height][width] = (x * sin(meta->rot_yaw)) + \
				(y * cos(meta->rot_yaw));
		}
	}
}

void	fdf_rotate_map_roll(t_map_meta *meta)
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
			x = meta->coor_xp[height][width];
			y = meta->coor_yp[height][width];
			z = meta->map[height][width] * meta->scale * meta->zoom;
			meta->coor_yp[height][width] = (y * cos(meta->rot_roll)) - (z * sin(meta->rot_roll));
			// meta->map[height][width] = (cos(meta->rot_roll) * meta->scale * meta->zoom);
			// meta->coor_yp[height][width] = (y * cos(meta->rot_roll)) - \
			// 	(z * sin(meta->rot_roll));
			// meta->map[height][width] = (z * sin(meta->rot_roll) * meta->scale * meta->zoom) + \
			// 	(z * cos(meta->rot_roll) * meta->scale * meta->zoom);
		}
	}
}

void	fdf_rotate_map_pitch(t_map_meta *meta)
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
			x = meta->coor_xp[height][width];
			y = meta->coor_yp[height][width];
			z = meta->map[height][width] * meta->scale * meta->zoom;
			meta->coor_xp[height][width] = (x * cos(meta->rot_pitch)) + (z * sin(meta->rot_pitch));
			// meta->map[height][width] = (cos(meta->rot_roll) * meta->scale * meta->zoom);
			// meta->coor_yp[height][width] = (y * cos(meta->rot_roll)) - \
			// 	(z * sin(meta->rot_roll));
			// meta->map[height][width] = (z * sin(meta->rot_roll) * meta->scale * meta->zoom) + \
			// 	(z * cos(meta->rot_roll) * meta->scale * meta->zoom);
		}
	}
}
