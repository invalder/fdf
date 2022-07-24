/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 01:14:25 by nnakarac          #+#    #+#             */
/*   Updated: 2022/07/24 15:31:41 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_arr_range(char **arr)
{
	int	len;

	len = 0;
	while (*arr)
	{
		len++;
		arr++;
	}
	return (len);
}

void	ft_free_split(char **str_arr, int len)
{
	int	cnt;

	cnt = 0;
	while (cnt <= len)
	{
		free(str_arr[cnt++]);
	}
	free(str_arr);
}
