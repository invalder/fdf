/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_chk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 10:32:46 by nnakarac          #+#    #+#             */
/*   Updated: 2022/07/28 16:42:13 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_init_check(t_map_meta *meta, char *ptr, char **arr_str)
{
	meta->height = 0;
	meta->width = 0;
	meta->read_width = 0;
	ptr = NULL;
	arr_str = NULL;
}

static int	fdf_set_width(t_map_meta *meta, int read_w)
{
	meta->read_width = read_w;
	if (!meta->width)
		meta->width = read_w;
	else if (meta->width != read_w)
		return (0);
	return (1);
}

static void	fdf_free_read(t_map_meta *meta, char **arr_str, char *ptr, int err)
{
	free(ptr);
	ptr = NULL;
	if (err)
	{
		ft_free_split(arr_str, meta->read_width);
		exit(1);
	}
	ft_free_split(arr_str, meta->width);
}

static char	**fdf_trim_split(char *ptr)
{
	char	**arr_str;
	char	*str;

	str = ft_strtrim(ptr, " \n");
	arr_str = ft_split(str, ' ');
	if (str)
		free(str);
	return (arr_str);
}

t_map_meta	fdf_input_check(char *path)
{
	t_map_meta	meta;
	char		*ptr;
	char		**arr_str;
	int			fd;

	ptr = NULL;
	arr_str = NULL;
	fdf_init_check(&meta, ptr, arr_str);
	fd = open(path, O_RDONLY);
	ptr = get_next_line(fd);
	while (ptr)
	{
		arr_str = fdf_trim_split(ptr);
		if (!fdf_set_width(&meta, ft_arr_range(arr_str)))
		{
			close(fd);
			fdf_free_read(&meta, arr_str, ptr, 1);
		}
		fdf_free_read(&meta, arr_str, ptr, 0);
		meta.height++;
		ptr = get_next_line(fd);
	}
	if (ptr)
		free(ptr);
	close(fd);
	return (meta);
}
