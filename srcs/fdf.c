/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:39:01 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/21 11:04:52 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_handle(t_handle *handy, t_vars *data, \
	t_draw *draw, t_map_meta *meta)
{
	handy->data = data;
	handy->draw = draw;
	handy->meta = meta;
}

int	main(int argc, char **argv)
{
	t_vars			data;
	t_draw			draw;
	t_map_meta		meta;
	static t_handle	handy;

	if (argc != 2)
		return (fdf_no_file());
	fdf_input_check(&meta, argv[1]);
	fdf_init_map(&meta, argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "FDF");
	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, \
		&data.img.line_length, &data.img.endian);
	init_handle(&handy, &data, &draw, &meta);
	fdf_draw(&data, &draw, &meta);
	mlx_hook(data.win, ON_DESTROY, 1L << 0, mlx_close, &data);
	mlx_hook(data.win, ON_KEYDOWN, 1L << 0, mlx_key_handler, &handy);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);
	return (0);
}
