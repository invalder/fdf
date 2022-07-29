/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:03:16 by nnakarac          #+#    #+#             */
/*   Updated: 2022/07/29 21:32:45 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	map_init(t_map_meta *meta)
{
	int	height;

	height = 0;
	meta->map = malloc(sizeof(int *) * meta->height);
	meta->map_color = malloc(sizeof(int *) * meta->height);
	while (height < meta->height)
	{
		meta->map[height] = malloc(sizeof(int) * meta->width);
		meta->map_color[height] = malloc(sizeof(int) * meta->width);
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
			meta->map_color[height][width] = ft_atoi_base("0XFFFFFF");
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

void	fdf_init_map(t_map_meta *meta, char *path)
{
	map_init(meta);
	map_assign(meta, path);
}
