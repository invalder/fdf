/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:39:01 by nnakarac          #+#    #+#             */
/*   Updated: 2022/07/16 02:11:13 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int	mlx_close(int keycode, t_vars *vars, t_data *img)
int	mlx_close(t_vars *vars)
{
	// mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	// free(vars->win);
	// vars->mlx = NULL;
	// free(vars->mlx);
	// free(vars->win);
	vars->win = NULL;
	vars->mlx = NULL;
	// mlx_loop_end(vars);
	// vars->end_loop = 0;
	exit (0);
	// exit (0);
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
		// mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
		// mlx_destroy_image(vars->mlx, img);
		// free(vars->mlx);
		// free(vars->win);
		vars->win = NULL;
		vars->mlx = NULL;
		// exit (0);
		// mlx_loop_end(vars);
		// vars->end_loop = 0;
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

int	render(t_vars *data)
{
	/* if window has been destroyed, we don't want to put the pixel ! */
	if (data->win == NULL)
	{
		printf("win = %p\n", data->win);
		return (1);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
    t_vars	data;
	t_draw	draw;
	int		fd;

	int		arr_h;
	int		arr_w;
	char	*ptr;
	char	**arr_str;
	int		tmp_w;


	if (argc != 2)
		return (1);
	arr_h = 0;
	arr_w = 0;
	fd = open(argv[1], O_RDONLY);
	ptr = get_next_line(fd);
	if (ptr)
	{
		arr_str = ft_split(ptr, ' ');
		tmp_w = ft_arr_range(arr_str);
		arr_w = tmp_w;
		ft_free_split(arr_str, tmp_w);
		arr_str = NULL;
		arr_h++;
	}
	while (ptr)
	{
		free(ptr);
		ptr = NULL;
		ptr = get_next_line(fd);
		if (ptr)
		{
			arr_str = ft_split(ptr, ' ');
			tmp_w = ft_arr_range(arr_str);
			if (tmp_w != arr_w)
			{
				ft_free_split(arr_str, tmp_w);
				free(ptr);
				exit(1);
			}
			arr_h++;
		}
	}
	if(ptr)
		free(ptr);
	close(fd);
	printf("line num = %d\nwidth = %d\n", arr_h, arr_w);
	
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
