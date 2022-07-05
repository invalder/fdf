/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:39:01 by nnakarac          #+#    #+#             */
/*   Updated: 2022/07/05 17:13:43 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int	mlx_close(int keycode, t_vars *vars, t_data *img)
int	mlx_close(t_vars *vars)
{
	// mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit (0);
}

// int mlx_key_close(int keycode, t_vars *vars, t_data *img)
int mlx_key_close(int keycode, t_vars *vars)
{
	// (void)img;
	if (keycode == 53 || keycode == 27)
	{
		// mlx_destroy_image(vars->mlx, vars->img.img);
		// ft_bzero(img->addr, sizeof(img->addr));
		// ft_bzero(img->img, sizeof(img->img));
		mlx_destroy_window(vars->mlx, vars->win);
		// mlx_destroy_image(vars->mlx, img);
		exit (0);
	}
	return (1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	// (void)color;
	// printf("color = %d\n", color);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));  
	*(unsigned int*)dst = color;
}

// int	main(void)
// {
// 	t_vars	data;
// 	// t_data	img;
// 	int		x;
// 	int		y;

// 	x = 0;
// 	y = 0;
// 	data.mlx = mlx_init();
// 	data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");\
// 	// if (!data.win)
// 	// 	error_map(data, ERROR_MLX, NULL);
// 	mlx_hook(data.win, 17, 1L<<5, mlx_close, &data);
// 	mlx_hook(data.win, 2, 1L<<0, mlx_key_close, &data);
// 	data.img.img = mlx_new_image(data.mlx, 1920, 1080);
// 	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, \
// 		&data.img.line_length, &data.img.endian);

// 	while(x < 1920 && y < 1080)
// 	{
// 		my_mlx_pixel_put(&data.img, x, y, 0x00FF0000);
// 		if (x < 1920)
// 			x++;
// 		if (y < 1080)
// 			y++;
// 	}

// 	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
// 	mlx_loop(data.mlx);
// 	return (0);
// }

// int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
// {
// 	double	deltaX;
// 	double	deltaY;
// 	double	pixelX;
// 	double	pixelY;
// 	int		pixels;

// 	pixelX = beginX;
// 	pixelY = beginY;
// 	deltaX = endX - beginX;
// 	deltaY = endY - beginY;
// 	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
// 	deltaX /= pixels;
// 	deltaY /= pixels;
// 	while (pixels)
// 	{
// 		mlx_pixel_put(mlx, win, pixelX, pixelY, color);
// 		pixelX += deltaX;
// 		pixelY += deltaY;
// 		--pixels;
// 	}
// 	return (0);
// }

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
	// printf("pixs = %d\n", pixs);
	dx /= (double)pixs;
	dy /= (double)pixs;
	// printf("dx = %.4f\tdy = %.4f\n", dx, dy);
	while (pixs)
	{
		// printf("1. pix_x = %.4f\tpix_y = %.4f\n", pix_x, pix_y);
		my_mlx_pixel_put(&data->img, pix_x, pix_y, draw->color);
		if (pix_x + dx > 0)
			pix_x += dx;
		if (pix_y + dy > 0)
			pix_y += dy;
		// printf("2. pix_x = %.4f\tpix_y = %.4f\n", pix_x, pix_y);
		--pixs;
	}
	return (0);
}

int main()
{
    t_vars	data;
	t_draw	draw;

	data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
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
    // draw_line(data.mlx, data.win, 1920, 1080, 0, 0, 0xFFFFFF);
	// draw_line(data.mlx, data.win, 0, 1080, 1920, 0, 0xFFFFFF);

	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
    mlx_loop(data.mlx);
}
