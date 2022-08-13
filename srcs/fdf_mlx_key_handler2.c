/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_key_handler2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:58:42 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/14 02:26:45 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_key_scale(int keycode, t_handle *handy)
{
	if (keycode == KEY_SQBC)
	{
		if (handy->meta->scale > 0)
		{
			if (handy->meta->scale >= 10)
				handy->meta->scale -= 1;
			else if (handy->meta->scale >= 1)
				handy->meta->scale -= 0.1;
			else
				handy->meta->scale -= 0.01;
		}
	}
	else
	{
		if (handy->meta->scale < 100)
		{
			if (handy->meta->scale <= 1)
				handy->meta->scale += 0.01;
			else if (handy->meta->scale <= 10)
				handy->meta->scale += 0.1;
			else
				handy->meta->scale += 1;
		}
		else
			handy->meta->scale += 10;
	}
	mlx_re_draw(handy);
}

void	mlx_key_zoom(int keycode, t_handle *handy)
{
	if (keycode == KEY_MINUS)
	{
		if (handy->meta->zoom > 0)
		{
			if (handy->meta->zoom >= 10)
				handy->meta->zoom -= 1;
			else if (handy->meta->zoom >= 1)
				handy->meta->zoom -= 0.1;
			else
				handy->meta->zoom -= 0.01;
		}
	}
	else
	{
		if (handy->meta->zoom < 100)
		{
			if (handy->meta->zoom <= 1)
				handy->meta->zoom += 0.01;
			else if (handy->meta->zoom <= 10)
				handy->meta->zoom += 0.1;
			else
				handy->meta->zoom += 1;
		}
		else
			handy->meta->zoom += 10;
	}
	mlx_re_draw(handy);
}

void	mlx_key_project(int keycode, t_handle *handy)
{
	if (keycode == KEY_SEMI)
		handy->meta->angle -= PI / 180;
	else
		handy->meta->angle += PI / 180;
	mlx_re_draw(handy);
}

void	mlx_reset(t_handle *handy)
{
	handy->meta->angle = 0.615472907;
	handy->meta->scale = 1;
	init_zoom(handy->meta);
	handy->meta->shift_x = (WIDTH / 2) - (handy->meta->width * \
		handy->meta->scale * cos(handy->meta->angle) / 4);
	handy->meta->shift_y = (HEIGHT / 4) - (handy->meta->height * \
		handy->meta->scale * sin(handy->meta->angle) / 2);
	mlx_re_draw(handy);
}
