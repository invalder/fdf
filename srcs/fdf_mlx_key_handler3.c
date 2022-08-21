/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_key_handler3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:19:47 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/21 17:06:17 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_key_vertz(int keycode, t_handle *handy)
{
	if (keycode == KEY_UP || keycode == KEY_W)
		handy->meta->shift_y -= 10;
	else
		handy->meta->shift_y += 10;
}

void	mlx_key_horz(int keycode, t_handle *handy)
{
	if (keycode == KEY_LEFT || keycode == KEY_A)
		handy->meta->shift_x -= 10;
	else
		handy->meta->shift_x += 10;
}

void	mlx_key_parallel(t_handle *handy)
{
	handy->meta->scale = 0.1;
	handy->meta->angle = 45 * PI / 180;
	handy->meta->rot_yaw = -45 * PI / 180;
	handy->meta->rot_roll = 0;
	handy->meta->rot_pitch = 0;
	handy->meta->is_iso = 0;
	init_zoom(handy->meta);
	handy->meta->shift_x = (WIDTH / 2);
	handy->meta->shift_y = (HEIGHT / 2);
}

void	mlx_key_noniso(t_handle *handy)
{
	handy->meta->rot_roll = 0.615472907;
	handy->meta->rot_pitch = 0;
	handy->meta->rot_yaw = 0;
	handy->meta->is_iso = 0;
}

void	mlx_reset(t_handle *handy)
{
	handy->meta->angle = 0.615472907;
	handy->meta->scale = 0.1;
	handy->meta->rot_yaw = 0;
	handy->meta->rot_roll = 0;
	handy->meta->rot_pitch = 0;
	init_zoom(handy->meta);
	handy->meta->shift_x = (WIDTH / 2);
	handy->meta->shift_y = (HEIGHT / 2);
	handy->meta->is_iso = 1;
}
