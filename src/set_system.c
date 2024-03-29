/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_system.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 11:34:13 by student           #+#    #+#             */
/*   Updated: 2020/06/29 11:34:17 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_system(t_sys *sys)
{
	set_consts(sys);
	set_mlxset(sys);
	set_cl(sys);
	sys->bitset = 0;
	sys->color = 0xFF0000;
	sys->cursor[0] = 0;
	sys->cursor[1] = 0;
	sys->cursorstr[0] = safe_strnew(7);
	sys->cursorstr[1] = safe_strnew(7);
	sys->str_cursor[0] = safe_strnew(14);
	sys->str_cursor[0] = ft_strcat(sys->str_cursor[0], "real = not def");
	sys->str_cursor[1] = safe_strnew(14);
	sys->str_cursor[1] = ft_strcat(sys->str_cursor[1], "img = not def");
	sys->scalestr = safe_strnew(8);
	sys->hexnumbs = safe_strnew(16);
	sys->hexnumbs = ft_strcat(sys->hexnumbs, "0123456789ABCDEF");
	sys->str_color = safe_strnew(21);
	sys->str_color = ft_strcat(sys->str_color, "fractal color: FF0000");
	set_tabparam(sys);
}

void	set_consts(t_sys *sys)
{
	if (!(sys->consts = (t_consts *)malloc(sizeof(t_consts))))
		exit(0);
	ITER = 100;
	IMAGE_W = MAIN_W - MENU_W;
	IMAGE_VOL = IMAGE_W * MAIN_H;
	MENU_VOL = MENU_W * MAIN_H;
	STAT_VOL = MENU_W * STAT_H;
	SETT_VOL = SETT_W * SETT_H;
	IMAGE_CENTRX = IMAGE_W / 2;
	IMAGE_CENTRY = MAIN_H / 2;
	IMAGE_CENTER = IMAGE_CENTRX + IMAGE_W * IMAGE_CENTRY;
	STR_X = IMAGE_W + 10;
	IMG_INT = sizeof(int) * IMAGE_VOL;
}

void	set_mlxset(t_sys *sys)
{
	if (!(sys->mlxset = (t_mlxset *)malloc(sizeof(t_mlxset))))
		exit(0);
	MLX = mlx_init();
	IMAGE = mlx_new_image(MLX, IMAGE_W, MAIN_H);
	sys->mlxset->imgout = (int *)mlx_get_data_addr(IMAGE,
		&sys->mlxset->img_s[0],
		&sys->mlxset->img_s[1],
		&sys->mlxset->img_s[2]);
	MENU = mlx_new_image(MLX, MENU_W, MAIN_H);
	sys->mlxset->mnuout = (int *)mlx_get_data_addr(MENU,
		&sys->mlxset->mnu_s[0],
		&sys->mlxset->mnu_s[1],
		&sys->mlxset->mnu_s[2]);
	STAT = mlx_new_image(MLX, MENU_W, STAT_H);
	sys->mlxset->statout = (int *)mlx_get_data_addr(STAT,
		&sys->mlxset->stat_s[0],
		&sys->mlxset->stat_s[1],
		&sys->mlxset->stat_s[2]);
	SETT = mlx_new_image(MLX, SETT_W, SETT_H);
	sys->mlxset->settout = (int *)mlx_get_data_addr(SETT,
		&sys->mlxset->sett_s[0],
		&sys->mlxset->sett_s[1],
		&sys->mlxset->sett_s[2]);
}

void	set_tabparam(t_sys *sys)
{
	char	i;

	i = 0;
	while (i < 8)
	{
		sys->shift[(int)i][0] = 0;
		sys->shift[(int)i][1] = 0;
		sys->delta[0][(int)i][0] = 0;
		sys->delta[0][(int)i][1] = 0;
		sys->delta[1][(int)i][0] = 0;
		sys->delta[1][(int)i][1] = 0;
		sys->scale[0][(int)i] = DEF_SCALE;
		sys->scale[1][(int)i] = DEF_SCALE;
		sys->axis_c[(int)i] = AXISF_C;
		sys->k[(int)i] = init_comp(0, 0);
		sys->str_k[(int)i] = safe_strnew(22);
		sys->str_k[(int)i] = ft_strcat(sys->str_k[(int)i],
			"k = 0.000 + 0.000i");
		sys->str_scale[(int)i] = safe_strnew(16);
		sys->str_scale[(int)i] = ft_strcat(sys->str_scale[(int)i],
			"scale = 1.000");
		i += 1;
	}
}
