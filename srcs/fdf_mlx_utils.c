/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:35:16 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/14 01:56:16 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mlx_close(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	vars->win = NULL;
	vars->mlx = NULL;
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	draw_line_img(t_vars *data, t_draw *draw)
{
	double	dx;
	double	dy;
	double	pix_x;
	double	pix_y;
	int		pixs;

	pix_x = draw->begin_x;
	pix_y = draw->begin_y;
	dx = draw->end_x - draw->begin_x;
	dy = draw->end_y - draw->begin_y;
	pixs = sqrt((dx * dx) + (dy * dy));
	dx /= (double)pixs;
	dy /= (double)pixs;
	while (pixs)
	{
		if (pix_x >= 0 && pix_x < WIDTH \
			&& pix_y >= 0 && pix_y < HEIGHT)
			my_mlx_pixel_put(&data->img, pix_x, pix_y, draw->color);
		if (pix_x + dx > 0)
			pix_x += dx;
		if (pix_y + dy > 0)
			pix_y += dy;
		--pixs;
	}
	return (0);
}

int	render(t_handle *handy)
{
	if (handy->data->win == NULL)
	{
		printf("win = %p\n", handy->data->win);
		return (1);
	}
	mlx_put_image_to_window(handy->data->mlx, handy->data->win, \
		handy->data->img.img, 0, 0);
	return (0);
}
