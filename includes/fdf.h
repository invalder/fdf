/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:39:48 by nnakarac          #+#    #+#             */
/*   Updated: 2022/07/29 21:31:20 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define _GNU_SOURCE

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"

# define EXIT_SUCCEED		0
# define EXIT_FAILURE		1
# define ERROR_MLX 			1
# define ERROR_WIN			2
# define ERROR_FILE_OPEN	10
# define ERROR_FILE_TYPE	11

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_data	img;
}	t_vars;

typedef struct s_draw
{
	int		begin_x;
	int		begin_y;
	int		end_x;
	int		end_y;
	int		color;
}	t_draw;

typedef struct s_map_meta
{
	int	width;
	int	height;
	int	read_width;
	int	**map;
	int **map_color;
}	t_map_meta;

int			mlx_close(t_vars *vars);
int			mlx_key_close(int keycode, t_vars *vars);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			draw_line_img(t_vars *data, t_draw *draw);
int			render(t_vars *data);

int			ft_arr_range(char **arr);
void		ft_free_split(char **str_arr, int len);

int			fdf_no_file(void);

void		fdf_free_read(t_map_meta *meta, char **arr_str, char *ptr, int err);
char		**fdf_trim_split(char *ptr);
void		fdf_input_check(t_map_meta *meta, char *path);

void		fdf_init_map(t_map_meta *meta, char *path);

#endif
