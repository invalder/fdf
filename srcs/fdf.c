/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:39:01 by nnakarac          #+#    #+#             */
/*   Updated: 2022/07/24 15:30:06 by nnakarac         ###   ########.fr       */
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

int	mlx_key_close(int keycode, t_vars *vars)
{
	if (keycode == 53 || keycode == 27)
	{
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
		vars->mlx = NULL;
		exit (0);
	}
	return (1);
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
		my_mlx_pixel_put(&data->img, pix_x, pix_y, draw->color);
		if (pix_x + dx > 0)
			pix_x += dx;
		if (pix_y + dy > 0)
			pix_y += dy;
		--pixs;
	}
	return (0);
}

int	render(t_vars *data)
{
	if (data->win == NULL)
	{
		printf("win = %p\n", data->win);
		return (1);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars		data;
	t_draw		draw;
	t_map_meta	meta;

	if (argc != 2)
		return (fdf_no_file());
	meta = fdf_input_check(argv[1]);
	ft_printf("line num = %d\nwidth = %d\n", meta.height, meta.width);

	data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, 17, 1L<<0, mlx_close, &data);
	mlx_hook(data.win, 2, 1L<<0, mlx_key_close, &data);
	data.img.img = mlx_new_image(data.mlx, 1920, 1080);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, \
		&data.img.line_length, &data.img.endian);
	draw.begin_x = 1919;
	draw.begin_y = 1079;
	draw.end_x = 0;
	draw.end_y = 0;
	draw.color = 0x0000FF;
	draw_line_img(&data, &draw);
	draw.begin_x = 0;
	draw.begin_y = 1079;
	draw.end_x = 1919;
	draw.end_y = 0;
	draw.color = 0x00FF00;
	draw_line_img(&data, &draw);
    mlx_loop(data.mlx);
	printf("end \n");
	free(data.mlx);
	free(data.win);

	return (0);
}
