/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_key_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 19:12:41 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/14 23:29:41 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mlx_key_handler(int keycode, t_handle *handy)
{
	if (keycode == KEY_ESC)
		mlx_key_close(handy->data);
	else if (keycode == KEY_UP || keycode == KEY_W || \
		keycode == KEY_DOWN || keycode == KEY_S)
		mlx_key_vertz(keycode, handy);
	else if (keycode == KEY_LEFT || keycode == KEY_A || \
		keycode == KEY_RIGHT || keycode == KEY_D)
		mlx_key_horz(keycode, handy);
	else if (keycode == KEY_SQBC || keycode == KEY_SQBO)
		mlx_key_scale(keycode, handy);
	else if (keycode == KEY_MINUS || keycode == KEY_PLUS)
		mlx_key_zoom(keycode, handy);
	else if (keycode == KEY_SEMI || keycode == KEY_QUOTE)
		mlx_key_project(keycode, handy);
	else if (keycode == KEY_SPACE)
		mlx_reset(handy);
	else if (keycode == KEY_Q || keycode == KEY_E)
		mlx_key_rot_yaw(keycode, handy);
	else
		mlx_key_handler2(keycode, handy);
	mlx_re_draw(handy);
	return (0);
}

int	mlx_key_handler2(int keycode, t_handle *handy)
{
	if (keycode == KEY_P)
		mlx_key_parallel(handy);
	else if (keycode == KEY_O)
		mlx_key_noniso(handy);
	else if (keycode == KEY_R || keycode == KEY_F)
		mlx_key_rot_roll(keycode, handy);
	else if (keycode == KEY_Z || keycode == KEY_C)
		mlx_key_rot_pitch(keycode, handy);
	return (0);
}

void	mlx_re_draw(t_handle *handy)
{
	mlx_destroy_image(handy->data->mlx, handy->data->img.img);
	handy->data->img.img = mlx_new_image(handy->data->mlx, WIDTH, HEIGHT);
	handy->data->img.addr = mlx_get_data_addr(handy->data->img.img, \
		&handy->data->img.bits_per_pixel, \
		&handy->data->img.line_length, &handy->data->img.endian);
	coord_assign(handy->meta);
	coord_assign_prime(handy->meta);
	fdf_rotate_map_roll(handy->meta);
	fdf_rotate_map_pitch(handy->meta);
	fdf_rotate_map_yaw(handy->meta);
	mlx_clear_window(handy->data->mlx, handy->data->win);
	fdf_draw(handy->data, handy->draw, handy->meta);
}

void	mlx_key_close(t_vars *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	data->mlx = NULL;
	exit (0);
}
