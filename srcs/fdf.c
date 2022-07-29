/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:39:01 by nnakarac          #+#    #+#             */
/*   Updated: 2022/07/29 22:37:59 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars		data;
	t_draw		draw;
	t_map_meta	meta;

	if (argc != 2)
		return (fdf_no_file());
	fdf_input_check(&meta, argv[1]);
	ft_printf("line num = %d\nwidth = %d\n", meta.height, meta.width);
	fdf_init_map(&meta, argv[1]);

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "FDF");
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, 17, 1L << 0, mlx_close, &data);
	mlx_hook(data.win, 2, 1L << 0, mlx_key_close, &data);
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
