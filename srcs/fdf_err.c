/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 10:26:47 by nnakarac          #+#    #+#             */
/*   Updated: 2022/07/24 10:32:00 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int fdf_no_file(void)
{
    ft_putstr_fd("Error, There's no input file or Invalid arguments\n", 1);
    ft_putstr_fd("Using \"./fdf <PATH TO FDF FILE>\"\n", 1);
    ft_putstr_fd("I.E. \"./fdf ./map_dir/map.fdf\"\n", 1);
    return (1);
}