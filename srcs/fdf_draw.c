/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:03:52 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/07 19:44:08 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static float fdf_absf(float val)
// {
// 	if (val < 0)
// 		return (-val);
// 	return (val);
// }

static void	fdf_draw_horz(t_vars *data, t_draw *draw, \
	t_map_meta *meta, t_cursor *cursor)
{
	int	sx;
	int	sy;

	sx = meta->shift_x;
	sy = meta->shift_y;
	if (cursor->width < meta->width - 1)
	{
		draw->begin_x = meta->coor_xp[cursor->height][cursor->width] + sx;
		draw->begin_y = meta->coor_yp[cursor->height][cursor->width] + sy;
		draw->end_x = meta->coor_xp[cursor->height][cursor->width + 1] + sx;
		draw->end_y = meta->coor_yp[cursor->height][cursor->width + 1] + sy;
		draw->color = meta->map_color[cursor->height][cursor->width];
		draw_line_img(data, draw);
	}
}

static void	fdf_draw_vertz(t_vars *data, t_draw *draw, \
	t_map_meta *meta, t_cursor *cursor)
{
	int	sx;
	int	sy;

	sx = meta->shift_x;
	sy = meta->shift_y;
	if (cursor->height < meta->height - 1)
	{
		draw->begin_x = meta->coor_xp[cursor->height][cursor->width] + sx;
		draw->begin_y = meta->coor_yp[cursor->height][cursor->width] + sy;
		draw->end_x = meta->coor_xp[cursor->height + 1][cursor->width] + sx;
		draw->end_y = meta->coor_yp[cursor->height + 1][cursor->width] + sy;
		draw->color = meta->map_color[cursor->height][cursor->width];
		draw_line_img(data, draw);
	}
}

void	fdf_draw(t_vars *data, t_draw *draw, t_map_meta *meta)
{
	int			width;
	int			height;
	t_cursor	cursor;

	height = -1;
	while (++height < meta->height)
	{
		width = -1;
		while (++width < meta->width)
		{
			cursor.height = height;
			cursor.width = width;
			fdf_draw_horz(data, draw, meta, &cursor);
			fdf_draw_vertz(data, draw, meta, &cursor);
		}
	}

}
