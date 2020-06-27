/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_axis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 23:53:57 by student           #+#    #+#             */
/*   Updated: 2020/06/26 23:54:01 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_axis(t_sys *sys)
{
	int		curcrd;
	int		endcrd;
	int		k[2];

	curcrd = IMAGE_CENTRX;
	while (curcrd < IMAGE_VOL)
	{
		sys->mlxset->imgout[curcrd] = AXIS_C[F_ID];
		curcrd += IMAGE_W;
	}	
	curcrd = IMAGE_W * IMAGE_CENTRY;
	endcrd = curcrd + IMAGE_W;
	while (curcrd < endcrd)
	{
		sys->mlxset->imgout[curcrd] = AXIS_C[F_ID];
		curcrd += 1;
	}
	draw_realstroks(sys, &curcrd, &endcrd, &k[0]);
	draw_imgstroks(sys, &curcrd, &endcrd, &k[0]);
	mlx_put_image_to_window(MLX, WINMAIN, IMAGE, 0, 0);
	draw_axtitle(sys);
}

void	draw_realstroks(t_sys *sys, int *startcrd, int *numbpxl, int *k)
{
	*startcrd = (IMAGE_CENTRY - 3) * IMAGE_W + IMAGE_CENTRX;	
	k[0] = sys->scale[1][F_ID];
	while (k[0] < IMAGE_CENTRX)
	{
		*numbpxl = 0;
		while(*numbpxl < 7)
		{
			k[1] = *numbpxl * IMAGE_W + *startcrd;
			sys->mlxset->imgout[k[1] + k[0]] = AXIS_C[F_ID];
			sys->mlxset->imgout[k[1] - k[0]] = AXIS_C[F_ID];
			*numbpxl += 1;
		}
		k[0] += sys->scale[1][F_ID];
	}
}

void	draw_imgstroks(t_sys *sys, int *startcrd, int *numbpxl, int *k)
{
	*startcrd = IMAGE_W * IMAGE_CENTRY + IMAGE_CENTRX - 3;
	k[0] = IMAGE_W * sys->scale[1][F_ID];
	while (*startcrd + k[0] < IMAGE_VOL)
	{
		*numbpxl = 0;
		while(*numbpxl < 7)
		{
			k[1] = *startcrd + *numbpxl;
			sys->mlxset->imgout[k[1] + k[0]] = AXIS_C[F_ID];
			sys->mlxset->imgout[k[1] - k[0]] = AXIS_C[F_ID];
			*numbpxl += 1;
		}
		k[0] += IMAGE_W * sys->scale[1][F_ID];
	}
}

void	draw_axtitle(t_sys *sys)
{
	mlx_string_put(MLX, WINMAIN, 5, IMAGE_CENTRY - 24,
		AXIS_C[F_ID], "-real");
	mlx_string_put(MLX, WINMAIN, IMAGE_W - 45, IMAGE_CENTRY - 24,
		AXIS_C[F_ID], "real");
	mlx_string_put(MLX, WINMAIN, IMAGE_CENTRX + 5, 2,
		AXIS_C[F_ID], "img");
	mlx_string_put(MLX, WINMAIN, IMAGE_CENTRX + 5, MAIN_H - 26,
		AXIS_C[F_ID], "-img");
}























