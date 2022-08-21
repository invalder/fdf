/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:33:00 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/21 16:51:13 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			z = meta->coor_zp[height][width];
			z = (y * sin(meta->rot_roll)) + (z * cos(meta->rot_roll));
			meta->coor_zp[height][width] = z;
			// meta->coor_yp[height][width] = (y * cos(meta->rot_roll)) - \
			// (z * sin(meta->rot_roll));
			meta->coor_yp[height][width] = (y * cos(meta->rot_roll));
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
			z = meta->coor_zp[height][width];
			z = (z * cos(meta->rot_pitch)) - (x * sin(meta->rot_roll));
			meta->coor_zp[height][width] = z;
			// meta->coor_xp[height][width] = (x * cos(meta->rot_pitch)) + \
			// 	(z * sin(meta->rot_pitch));
			meta->coor_xp[height][width] = (x * cos(meta->rot_pitch));
		}
	}
}
