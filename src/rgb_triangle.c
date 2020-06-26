/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 20:59:50 by student           #+#    #+#             */
/*   Updated: 2020/06/04 21:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_rgbtriangle(t_sys *sys, int x0, int offset_x)
{
	int		width;
	int		height;
	int		tris[3][3];

	width = MENU_W - 2 * offset_x;
	height = lround(width * sqrt(3) / 2);
	sys->rgbtris_y[1] = sys->rgbtris_y[0] + height;
	width /= 2;
	tris[0][0] = x0;
	tris[0][1] = sys->rgbtris_y[0];
	tris[0][2] = 0xFF0000;
	tris[1][0] = x0 - width;
	tris[1][1] = sys->rgbtris_y[1];
	tris[1][2] = 0xFF00;
	tris[2][0] = x0 + width;
	tris[2][1] = tris[1][1];
	tris[2][2] = 0xFF;
	fill_triangle(sys, &tris[0][0], height, width);
}

void	fill_triangle(t_sys *sys, int *tris, int height, int widthhalf)
{
	int		cursor[2][3];
	double	int_endvert;
	char	rgb_set[2][6];

	def_rgbset(&rgb_set[0][0], tris[2], tris[5]);
	def_rgbset(&rgb_set[1][0], tris[2], tris[8]);
	cursor[0][0] = tris[0];
	cursor[0][1] = tris[1];
	cursor[0][2] = tris[2];
	cursor[1][0] = tris[0];
	cursor[1][2] = tris[2];
	sys->mnuout[cursor[0][0] + MENU_W * cursor[0][1]] = cursor[0][2];
	cursor[0][1] += 1;
	while (cursor[0][1] != tris[7])
	{
		int_endvert = (double)(cursor[0][1] - tris[1]) / height;
		cursor[0][0] = tris[0] - lround(widthhalf * int_endvert);
		cursor[0][2] = set_color(&rgb_set[0][0], tris[2], int_endvert);
		cursor[1][0] = tris[0] + lround(widthhalf * int_endvert);
		cursor[1][2] = set_color(&rgb_set[1][0], tris[2], int_endvert);
		draw_horline(sys, &cursor[0][0], &cursor[1][0]);
		cursor[0][1] += 1;
	}
	draw_horline(sys, &tris[3], &tris[6]);
}

void	def_rgbset(char *rgb_set, int color0, int color1)
{
	unsigned char	*rgb[2];
	char			i;

	rgb[0] = (unsigned char *)&color0;
	rgb[1] = (unsigned char *)&color1;
	i = 0;
	while (i < 3)
	{
		rgb_set[(int)i] = rgb[1][(int)i] > rgb[0][(int)i] ? 1 : -1;
		i += 1;
	}
	while (i < 6)
	{
		rgb_set[(int)i] = abs(rgb[1][(int)i - 3] - rgb[0][(int)i - 3]);
		i += 1;
	}
}

int		set_color(char *rgb_set, int color0, double int_xc)
{
	unsigned char	*rgb0;
	int				color;

	rgb0 = (unsigned char *)&color0;
	color = (rgb0[0] +
		lround((unsigned char)rgb_set[3] * int_xc) * rgb_set[0]) +
		((rgb0[1] +
		lround((unsigned char)rgb_set[4] * int_xc) * rgb_set[1]) << 8) +
		((rgb0[2] +
		lround((unsigned char)rgb_set[5] * int_xc) * rgb_set[2]) << 16);
	return (color);
}

void	draw_horline(t_sys *sys, int *v0, int *v1)
{
	char	rgb_set[6];
	int		width;
	int		cursor_x;
	double	int_v1;

	def_rgbset(&rgb_set[0], v0[2], v1[2]);
	width = v1[0] - v0[0];
	sys->mnuout[v0[0] + MENU_W * v0[1]] = v0[2];
	cursor_x = v0[0] + 1;
	while (cursor_x != v1[0])
	{
		int_v1 = (double)(cursor_x - v0[0]) / width;
		sys->mnuout[cursor_x + MENU_W * v0[1]] =
		set_color(rgb_set, v0[2], int_v1);
		cursor_x += 1;
	}
	sys->mnuout[v1[0] + MENU_W * v0[1]] = v1[2];
}
