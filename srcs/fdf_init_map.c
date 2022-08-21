/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:03:16 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/21 16:59:17 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	map_init(t_map_meta *meta)
{
	int	height;

	height = 0;
	meta->map = malloc(sizeof(int *) * meta->height);
	meta->map_color = malloc(sizeof(int *) * meta->height);
	meta->coor_x = malloc(sizeof(int *) * meta->height);
	meta->coor_y = malloc(sizeof(int *) * meta->height);
	meta->coor_xp = malloc(sizeof(float *) * meta->height);
	meta->coor_yp = malloc(sizeof(float *) * meta->height);
	meta->coor_zp = malloc(sizeof(float *) * meta->height);
	while (height < meta->height)
	{
		meta->map[height] = malloc(sizeof(int) * meta->width);
		meta->map_color[height] = malloc(sizeof(int) * meta->width);
		meta->coor_x[height] = malloc(sizeof(int *) * meta->width);
		meta->coor_y[height] = malloc(sizeof(int *) * meta->width);
		meta->coor_xp[height] = malloc(sizeof(float *) * meta->width);
		meta->coor_yp[height] = malloc(sizeof(float *) * meta->width);
		meta->coor_zp[height] = malloc(sizeof(float *) * meta->width);
		height++;
	}
}

static void	map_assign_line(t_map_meta *meta, char **arr_str, int height)
{
	char	**arr_ptr;
	int		width;
	int		len;

	width = 0;
	while (width < meta->width)
	{
		arr_ptr = ft_split(arr_str[width], ',');
		meta->map[height][width] = ft_atoi(arr_ptr[0]);
		len = ft_arr_range(arr_ptr);
		if (len > 1)
			meta->map_color[height][width] = ft_atoi_base(arr_ptr[1]);
		else
		{
			if (!meta->map[height][width])
			{
				meta->map_color[height][width] = ft_atoi_base("0XFFFFFF");
			}
			else
				meta->map_color[height][width] = ft_atoi_base("0XFFFFFF") \
					- ft_atoi_base("0XFFFF00");
		}
		ft_free_split(arr_ptr, len);
		width++;
	}
}

static void	map_assign(t_map_meta *meta, char *path)
{
	char	*ptr;
	char	**arr_str;
	int		fd;
	int		height;

	height = 0;
	fd = open(path, O_RDONLY);
	ptr = get_next_line(fd);
	while (ptr)
	{
		arr_str = fdf_trim_split(ptr);
		map_assign_line(meta, arr_str, height);
		fdf_free_read(meta, arr_str, ptr, 0);
		ptr = get_next_line(fd);
		height++;
	}
	if (ptr)
		free(ptr);
	close(fd);
}

void	init_zoom(t_map_meta *meta)
{
	int	zoom_h;
	int	zoom_w;

	zoom_h = (int)floor((double)HEIGHT / (double)meta->height);
	zoom_w = (int)floor((double)WIDTH / (double)meta->width);
	if (zoom_h > zoom_w)
		meta->zoom = zoom_w / 2;
	else
		meta->zoom = zoom_h / 2;
}

void	fdf_init_map(t_map_meta *meta, char *path)
{
	meta->angle = 30 * PI / 180;
	meta->zoom = 1;
	meta->scale = 0.1;
	meta->rot_yaw = 0 * PI / 180;
	meta->rot_roll = 0 * PI / 180;
	meta->rot_pitch = 0 * PI / 180;
	meta->is_iso = 1;
	map_init(meta);
	map_assign(meta, path);
	init_zoom(meta);
	coord_assign(meta);
	coord_assign_prime(meta);
	fdf_rotate_map_roll(meta);
	fdf_rotate_map_pitch(meta);
	fdf_rotate_map_yaw(meta);
	coord_assign_propagate(meta);
	meta->shift_x = (WIDTH / 2);
	meta->shift_y = (HEIGHT / 2);
}
