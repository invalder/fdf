/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_key_handler4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:44:02 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/14 23:24:07 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_key_rot_roll(int keycode, t_handle *handy)
{
	if (keycode == KEY_F)
		handy->meta->rot_roll -= PI / 180;
	else
		handy->meta->rot_roll += PI / 180;
}

void	mlx_key_rot_pitch(int keycode, t_handle *handy)
{
	if (keycode == KEY_Z)
		handy->meta->rot_pitch -= PI / 180;
	else
		handy->meta->rot_pitch += PI / 180;
}

void	mlx_key_rot_yaw(int keycode, t_handle *handy)
{
	if (keycode == KEY_Q)
		handy->meta->rot_yaw -= PI / 180;
	else
		handy->meta->rot_yaw += PI / 180;
}
