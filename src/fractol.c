/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 16:35:15 by student           #+#    #+#             */
/*   Updated: 2020/05/27 16:35:18 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char **argv)
{
	t_sys	*sys;

	if (argc > 2)
		fractol_discr();
	if (!(sys = (t_sys *)malloc(sizeof(t_sys))))
		exit(0);

	if (!(sys->consts = (t_consts *)malloc(sizeof(t_consts))))
		exit(0);
	sys->consts->image_w = MAIN_W - MENU_W;
	sys->consts->menu_xoffset = IMAGE_W + 10;

	firstdraw_image(sys, argc, argv[1]);
	draw_menu(sys);
	draw_stat(sys);
	clear_settings(sys);
	mlx_hook(sys->win_main, 2, 0, key_press, sys);
	mlx_hook(sys->win_main, 3, 0, key_release, sys);
	mlx_hook(sys->win_main, 4, 0, mouse_press, sys);
	mlx_hook(sys->win_main, 5, 0, mouse_release, sys);
	mlx_hook(sys->win_main, 6, 0, mouse_move, sys);
	mlx_hook(sys->win_main, 17, 0, close_fractol, sys);
	mlx_loop(sys->mlx);
	return (0);
}

char	*set_fractname(t_sys *sys)
{
	if (sys->index == 0)
		return ("name: Zulia");
	if (sys->index == 1)
		return ("name: Mandelbrot");
	if (sys->index == 2)
		return ("name: BurningShip");
	if (sys->index == 3)
		return ("name: Mandelbar");
	if (sys->index == 4)
		return ("name: AbsReal");
	if (sys->index == 5)
		return ("name: AbsImg");
	if (sys->index == 6)
		return ("name: Power3");
	return ("name: AbsRealP4");
}

void	set_system(t_sys *sys)
{
	sys->mlx = mlx_init();
	sys->win_main = mlx_new_window(sys->mlx, MAIN_W, MAIN_H, "fractol");
	
	sys->imgvol = (MAIN_W - MENU_W) * MAIN_H;
	sys->img = mlx_new_image(sys->mlx, MAIN_W - MENU_W, MAIN_H);
	sys->imgout = (int *)mlx_get_data_addr(sys->img,
		&sys->img_s[0], &sys->img_s[1], &sys->img_s[2]);

	sys->mnuvol = MENU_W * MAIN_H;
	sys->mnu = mlx_new_image(sys->mlx, MENU_W, MAIN_H);
	sys->mnuout = (int *)mlx_get_data_addr(sys->mnu,
		&sys->mnu_s[0], &sys->mnu_s[1], &sys->mnu_s[2]);

	sys->statvol = MENU_W * STAT_H;
	sys->stat = mlx_new_image(sys->mlx, MENU_W, STAT_H);
	sys->statout = (int *)mlx_get_data_addr(sys->stat,
		&sys->stat_s[0], &sys->stat_s[1], &sys->stat_s[2]);

	sys->setvol = SET_W * SET_H;
	sys->set = mlx_new_image(sys->mlx, SET_W, SET_H);
	sys->setout = (int *)mlx_get_data_addr(sys->set,
		&sys->set_s[0], &sys->set_s[1], &sys->set_s[2]);
	
	sys->bitset = 0;
	
	sys->color = 0xFF0000;


	sys->cursor[0] = 0;
	sys->cursor[1] = 0;

	sys->cursorstr[0] = ft_strnew(7);
	sys->cursorstr[1] = ft_strnew(7);

	sys->str_cursor[0] = ft_strnew(14);
	sys->str_cursor[0] = ft_strcat(sys->str_cursor[0], "real = not def");
	sys->str_cursor[1] = ft_strnew(14);
	sys->str_cursor[1] = ft_strcat(sys->str_cursor[1], "img = not def");

	// MAYBE NEED INCREASE !!!!!!!!
	sys->scalestr = ft_strnew(6);

	sys->hexnumbs = ft_strnew(16);
	sys->hexnumbs = ft_strcat(sys->hexnumbs, "0123456789ABCDEF");
	sys->str_color = ft_strnew(21);
	sys->str_color = ft_strcat(sys->str_color, "fractal color: FF0000");

	set_tabparam(sys);
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
		sys->str_k[(int)i] = ft_strnew(23);
		sys->str_k[(int)i] = ft_strcat(sys->str_k[(int)i], "k = 0.000 + 0.000i");

		// MAYBE NEED INCREASE !!!!!!!!
		sys->str_scale[(int)i] = ft_strnew(14);
		sys->str_scale[(int)i] = ft_strcat(sys->str_scale[(int)i], "scale = 1.000");
		i += 1;
	}
}

void	clear_image(t_sys *sys)
{
	int		i;
	
	i = 0;
	while (i < sys->imgvol)
	{
		sys->imgout[i] = IMAGE_C;
		i += 1;
	}
}

void	clear_stat(t_sys *sys)
{
	int		i;
	
	i = 0;
	while (i < sys->statvol)
	{
		sys->statout[i] = 0;
		i += 1;
	}
}

// // FOR 1920 x 1080
// void	draw_menu(t_sys *sys)
// {
// 	int		i;

// 	i = 0;
// 	while (i < sys->mnuvol)
// 	{
// 		sys->mnuout[i] = MENU_C;
// 		i += 1;
// 	}
// 	sys->rgbtris_y[0] = 325;
// 	draw_rgbtriangle(sys, MENU_W / 2, 10);
// 	mlx_put_image_to_window(sys->mlx, sys->win_main, sys->mnu, MAIN_W - MENU_W, 0);
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, 20, TITLE_C, "Main settings");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, 60, TEXT_C, "1 - 8 - choose fractal");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, 100, TEXT_C, "LMB - transform fractal");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, 125, TEXT_C, "RMB - reset transform");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, 165, TEXT_C, "SMB - scale fractal");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, 190, TEXT_C, "MMB - reset scale");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, 230, TEXT_C, "ARROWS - shift fractal");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, 255, TEXT_C, "C - centred fractal");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, 295, TEXT_C, "Choose fractal color:");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, 550, TEXT_C, "SPACE - more settings");
// }

// FOR 1280 x 720
void	draw_menu(t_sys *sys)
{
	int		i;

	i = 0;
	while (i < sys->mnuvol)
	{
		sys->mnuout[i] = MENU_C;
		i += 1;
	}
	sys->rgbtris_y[0] = 245;
	draw_rgbtriangle(sys, MENU_W / 2, 40);
	mlx_put_image_to_window(sys->mlx, sys->win_main, sys->mnu, IMAGE_W, 0);
	mlx_string_put(sys->mlx, sys->win_main, MENU_XSTR, 10, TITLE_C, "Main settings");
	mlx_string_put(sys->mlx, sys->win_main, MENU_XSTR, 40, TEXT_C, "1 - 8 - choose fractal");
	mlx_string_put(sys->mlx, sys->win_main, MENU_XSTR, 70, TEXT_C, "LMB - transform fractal");
	mlx_string_put(sys->mlx, sys->win_main, MENU_XSTR, 90, TEXT_C, "RMB - reset transform");
	mlx_string_put(sys->mlx, sys->win_main, MENU_XSTR, 120, TEXT_C, "SMB - scale fractal");
	mlx_string_put(sys->mlx, sys->win_main, MENU_XSTR, 140, TEXT_C, "MMB - reset scale");
	mlx_string_put(sys->mlx, sys->win_main, MENU_XSTR, 170, TEXT_C, "ARROWS - shift fractal");
	mlx_string_put(sys->mlx, sys->win_main, MENU_XSTR, 190, TEXT_C, "C - centred fractal");
	mlx_string_put(sys->mlx, sys->win_main, MENU_XSTR, 220, TEXT_C, "Choose fractal color:");
	mlx_string_put(sys->mlx, sys->win_main, MENU_XSTR, 400, TEXT_C, "SPACE - more settings");

}


void	clear_settings(t_sys *sys)
{
	int		i;

	i = 0;
	while (i < sys->setvol)
	{
		sys->setout[i] = MENU_C;
		i += 1;
	}
}

int		close_fractol(void *param)
{
	(void)param;
	exit(0);
}

int		close_setting(void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;
	sys->bitset ^= 0b00000010;
	return (0);
}

// // // NOT NEED UNCOMMENT !!!!!!!!!!!!!
// t_comp	int_to_comp(t_sys *sys, int id)
// {
// 	t_comp	complex;

// 	complex.real = id % (MAIN_W - MENU_W);
// 	complex.img = -id / (MAIN_W - MENU_W);
// 	complex.real -= (MAIN_W - MENU_W) / 2 + sys->shift[(int)sys->index][0];
// 	complex.img += MAIN_H / 2 + sys->shift[(int)sys->index][1];
// 	complex.real /= sys->scale;
// 	complex.img /= sys->scale;
// 	return (complex);
// }





// //--------------STAR_TESTINGVERSION------------------
// t_comp	int_to_comp(t_sys *sys, int id)
// {
// 	// static int i = 0;
// 	// sys->cursor[0] -= (MAIN_W - MENU_W) / 2;
// 	// sys->cursor[1] -=  MAIN_H / 2;

// 	t_comp	scalecomp;
// 	scalecomp.real = sys->cursor[0] / (double)sys->scale0;
// 	scalecomp.real += sys->delta0[0] / (double)sys->scale0;

// 	scalecomp.img = sys->cursor[1] / (double)sys->scale0;
// 	scalecomp.img += sys->delta0[1] / (double)sys->scale0;

// 	t_comp	curscomp;
// 	curscomp.real = sys->cursor[0] / (double)sys->scale;
// 	curscomp.real += sys->delta0[0] / (double)sys->scale;

// 	curscomp.img = sys->cursor[1] / (double)sys->scale;
// 	curscomp.img += sys->delta0[1] / (double)sys->scale;

// 	t_comp	shiftcomp;
// 	shiftcomp.real = scalecomp.real - curscomp.real;
// 	shiftcomp.img = scalecomp.img - curscomp.img;

// 	shiftcomp.real = shiftcomp.real * sys->scale;
// 	shiftcomp.img = shiftcomp.img * sys->scale;

// 	// sys->scale0 = sys->scale;

// 	// int		shift_1d;
// 	// int		offset_x;
// 	// int		offset_y;
// 	// offset_x = 0; // "-" is right offset
// 	// offset_y = 0; // "-" is down offset

// 	// offset_x = lround(shiftcomp.real) + sys->delta0[0];
// 	// offset_y = lround(shiftcomp.img) + sys->delta0[1];
// 	// shift_1d = offset_x + (MAIN_W - MENU_W) * offset_y;


// 	// int		shift_1d;
// 	// sys->delta[0] = sys->delta0[0];
// 	// sys->delta[1] = sys->delta0[1];	
// 	// sys->delta[0] = lround(shiftcomp.real);
// 	// sys->delta[1] = lround(shiftcomp.img);
// 	// shift_1d = sys->delta[0] + (MAIN_W - MENU_W) * sys->delta[1];

// 	// id += shift_1d;

// 	// if (sys->scale0 != sys->scale)
// 	// 	id += sys->cursor[0] + (MAIN_W - MENU_W) * sys->cursor[1];

// 	sys->delta[0] = lround(shiftcomp.real);
// 	sys->delta[1] = lround(shiftcomp.img);
// 	// sys->delta[0] += sys->delta0[0];
// 	// sys->delta[1] += sys->delta0[1];




// 	t_comp	complex;
// 	complex.real = id % (MAIN_W - MENU_W);
// 	complex.real += sys->delta0[0];
// 	complex.real += sys->delta[0];

// 	complex.img = id / (MAIN_W - MENU_W);
// 	complex.img += sys->delta0[1];
// 	complex.img += sys->delta[1];


// 	complex.real /= (double)sys->scale;
// 	complex.img /= (double)sys->scale;

// 	//-------------------
	
// 	// id -= (MAIN_W - MENU_W) / 2 + (MAIN_W - MENU_W) * MAIN_H / 2;
// 	// // id += shift_1d;

// 	// t_comp	complex;
// 	// if (id < 0 && -id % (MAIN_W - MENU_W) > (MAIN_W - MENU_W) / 2)
// 	// {
// 	// 	complex.real = (MAIN_W - MENU_W) + id % (MAIN_W - MENU_W);
// 	// 	complex.img = id / (MAIN_W - MENU_W) - 1;
// 	// }
// 	// else if (id > 0 && id % (MAIN_W - MENU_W) >= (MAIN_W - MENU_W) / 2)
// 	// {
// 	// 	complex.real = -(MAIN_W - MENU_W) + id % (MAIN_W - MENU_W);
// 	// 	complex.img = id / (MAIN_W - MENU_W) + 1;
// 	// }
// 	// else
// 	// {
// 	// 	complex.real = id % (MAIN_W - MENU_W);
// 	// 	complex.img = id / (MAIN_W - MENU_W);
// 	// }


// 	// int		comp_1d;
// 	// comp_1d = lround((complex.real + (MAIN_W - MENU_W) * complex.img) * sys->scale);

// 	// int		shift_1d;
// 	// int		offset_x;
// 	// int		offset_y;
// 	// offset_x = 10; // "-" is right offset
// 	// offset_y = 10; // "-" is down offset 
// 	// shift_1d = offset_x + (MAIN_W - MENU_W) * offset_y;

// 	// comp_1d += shift_1d;

// 	// complex.real = comp_1d % (MAIN_W - MENU_W) / (double)sys->scale;
// 	// complex.img = comp_1d / (MAIN_W - MENU_W) / (double)sys->scale;
// 	// printf("%f %f\n", complex.real, complex.img);
	
// 	// if (i == 3)
// 	// 	exit(0);
// 	// i += 1;
// 	return (complex);
// }
// //--------------END_TESTINGVERSION------------------

// ------------------------START_WORKINGVERSION----------------------------

t_comp	int_to_comp(t_sys *sys, int id)
{
	t_comp	complex;
	int		id2d[2];
	
	id -= (MAIN_W - MENU_W) / 2 + (MAIN_W - MENU_W) * MAIN_H / 2;

	// id = id + sys->shift[(int)sys->index][0] + (MAIN_W - MENU_W) * sys->shift[(int)sys->index][1];

	
	// sys->delta[0] = sys->delta0[0] + sys->delta[0] - sys->shift[(int)sys->index][0];
	// sys->delta[1] = sys->delta0[1] + sys->delta[1] - sys->shift[(int)sys->index][1];
	conv_1d_2d(sys, id, &id2d[0]);

	// id2d[0] -= sys->shift[(int)sys->index][0];
	// id2d[1] -= sys->shift[(int)sys->index][1];

	complex = init_comp(id2d[0] / (double)sys->scale[1][(int)sys->index], -id2d[1] / (double)sys->scale[1][(int)sys->index]);

	// complex.real -= (MAIN_W - MENU_W) / 2 + sys->shift[(int)sys->index][0];
	// complex.img += MAIN_H / 2 + sys->shift[(int)sys->index][1];

	// complex.real /= (double)sys->scale;
	// complex.img /= (double)sys->scale;
	return (complex);
}

// 	t_comp	complex;
// 	complex.real = id % (MAIN_W - MENU_W);
// 	complex.real += sys->delta0[0];
// 	complex.real += sys->delta[0];


// void	conv_1d_2d(t_sys *sys, int id, int *id2d)
// {
// 	int		halfwidth = (MAIN_W - MENU_W) / 2;

// 	id2d[0] = id % (MAIN_W - MENU_W);
// 	id2d[1] = id / (MAIN_W - MENU_W);
// 	if (id < 0 && -id2d[0] > halfwidth)
// 	{
// 		id2d[0] += sys->delta0[0] + (MAIN_W - MENU_W) + sys->delta[0]
// 			- sys->shift[(int)sys->index][0];
// 		id2d[1] += sys->delta0[1] + -1 + sys->delta[1] - sys->shift[(int)sys->index][1];
// 		return ;
// 	}
// 	if (id > 0 && id2d[0] >= halfwidth)
// 	{
// 		id2d[0] += sys->delta0[0] + -(MAIN_W - MENU_W) + sys->delta[0]
// 			- sys->shift[(int)sys->index][0];
// 		id2d[1] += sys->delta0[1] + 1 + sys->delta[1] - sys->shift[(int)sys->index][1];
// 		return ;
// 	}
// 	id2d[0] += sys->delta0[0] + sys->delta[0] - sys->shift[(int)sys->index][0];
// 	id2d[1] += sys->delta0[1] + sys->delta[1] - sys->shift[(int)sys->index][1];
// }

void	conv_1d_2d(t_sys *sys, int id, int *id2d)
{
	int		halfwidth = (MAIN_W - MENU_W) / 2;

	// int		tmp[2];

	// tmp[0] = sys->delta0[0] + sys->delta[0] - sys->shift[(int)sys->index][0];
	// tmp[1] = sys->delta0[1] + sys->delta[1] - sys->shift[(int)sys->index][1];
	// tmp[0] = sys->delta[0];
	// tmp[1] = sys->delta[1];

	id2d[0] = id % (MAIN_W - MENU_W);
	id2d[1] = id / (MAIN_W - MENU_W);
	if (id < 0 && -id2d[0] > halfwidth)
	{
		id2d[0] += sys->delta[1][(int)sys->index][0] + (MAIN_W - MENU_W);
		id2d[1] += sys->delta[1][(int)sys->index][1] - 1;
		return ;
	}
	if (id > 0 && id2d[0] >= halfwidth)
	{
		id2d[0] += sys->delta[1][(int)sys->index][0] - (MAIN_W - MENU_W);
		id2d[1] += sys->delta[1][(int)sys->index][1] + 1;
		return ;
	}
	id2d[0] += sys->delta[1][(int)sys->index][0];
	id2d[1] += sys->delta[1][(int)sys->index][1];
}

void	def_delta(t_sys *sys)
{
	// t_comp	delta;
	// t_comp	scaler;

	// delta.real = (sys->cursor[0] - (MAIN_W - MENU_W) / 2) / (double)SCALE;
	// delta.img = (sys->cursor[1] - MAIN_H / 2) / (double)SCALE;
	// scaler.real = (sys->cursor[0] - (MAIN_W - MENU_W) / 2) / (double)sys->scale;
	// scaler.img = (sys->cursor[1] - MAIN_H / 2) / (double)sys->scale;
	// delta.real = (delta.real - scaler.real) * sys->scale;
	// delta.img = (delta.img - scaler.img) * sys->scale;

	// sys->delta[0] = sys->cursor[0] - (MAIN_W - MENU_W) / 2;
	// sys->delta[1] = sys->cursor[1] - MAIN_H / 2;
	// scaler = (double)sys->scale / SCALE - 1;
	// sys->delta[0] *= scaler;
	// sys->delta[1] *= scaler;

	// 	t_comp	scalecomp;
	// 	scalecomp.real = sys->cursor[0] / (double)sys->scale0;
	// 	scalecomp.real += sys->delta0[0] / (double)sys->scale0;


	double	scaler;

	scaler = (double)sys->scale[1][(int)sys->index] / sys->scale[0][(int)sys->index] - 1;
	// sys->delta[(int)sys->index][0] = lround((sys->cursor[0] - (MAIN_W - MENU_W) / 2 - sys->shift[(int)sys->index][0]
	// 	+ sys->delta0[(int)sys->index][0]) * scaler);
	sys->delta[1][(int)sys->index][0] = lround((sys->delta[0][(int)sys->index][0] + sys->cursor[0]
		- (MAIN_W - MENU_W) / 2 - sys->shift[(int)sys->index][0]) * scaler);
	sys->delta[1][(int)sys->index][0] += sys->delta[0][(int)sys->index][0] - sys->shift[(int)sys->index][0];

	// sys->delta[(int)sys->index][1] = lround((sys->cursor[1] - MAIN_H / 2 - sys->shift[(int)sys->index][1]
	// 	+ sys->delta0[(int)sys->index][1]) * scaler);
	sys->delta[1][(int)sys->index][1] = lround((sys->delta[0][(int)sys->index][1] + sys->cursor[1]
		- MAIN_H / 2 - sys->shift[(int)sys->index][1]) * scaler);
	sys->delta[1][(int)sys->index][1] += sys->delta[0][(int)sys->index][1] - sys->shift[(int)sys->index][1];

	// double	prevpos[2];
	// double	curpos[2];

	// prevpos[0] =  sys->cursor[0] / (double)sys->scale0;
	// prevpos[0] += sys->delta0[0] / (double)sys->scale0;
	// prevpos[0] -= ((MAIN_W - MENU_W) / 2) / (double)sys->scale0;
	// prevpos[0] -= sys->shift[(int)sys->index][0] / (double)sys->scale0;

	// prevpos[1] =  sys->cursor[1] / (double)sys->scale0;
	// prevpos[1] += sys->delta0[1] / (double)sys->scale0;
	// prevpos[1] -= (MAIN_H / 2) / (double)sys->scale0;
	// prevpos[1] -= sys->shift[(int)sys->index][1] / (double)sys->scale0;


	// curpos[0] =  sys->cursor[0] / (double)sys->scale;
	// curpos[0] += sys->delta0[0] / (double)sys->scale;
	// curpos[0] -= ((MAIN_W - MENU_W) / 2) / (double)sys->scale;
	// curpos[0] -= sys->shift[(int)sys->index][0] / (double)sys->scale;

	// curpos[1] =  sys->cursor[1] / (double)sys->scale;
	// curpos[1] += sys->delta0[1] / (double)sys->scale;
	// curpos[1] -= (MAIN_H / 2) / (double)sys->scale;
	// curpos[1] -= sys->shift[(int)sys->index][1] / (double)sys->scale;

	// double	curdelta[2];

	// curdelta[0] = prevpos[0] - curpos[0];
	// curdelta[0] *= sys->scale;

	// curdelta[1] = prevpos[1] - curpos[1];
	// curdelta[1] *= sys->scale;

	// sys->delta[0] = lround(curdelta[0]);
	// sys->delta[1] = lround(curdelta[1]);

	// sys->delta[0] = sys->delta0[0] + sys->delta[0] - sys->shift[(int)sys->index][0];
	// sys->delta[1] = sys->delta0[1] + sys->delta[1] - sys->shift[(int)sys->index][1];

	// sys->delta[0] += sys->delta0[0] - sys->shift[(int)sys->index][0];
	// sys->delta[1] += sys->delta0[1] - sys->shift[(int)sys->index][1];

	return ;
}


// ------------------------END_WORKINGVERSION----------------------------

void	calc_fractal(t_sys *sys)
{
	if (sys->index == 0)
	{
		calc_Zulia(sys);
		return ;
	}
	if (sys->index == 1)
	{
		calc_Mandelbrot(sys);
		return ;
	}
	if (sys->index == 2)
	{
		calc_BurningShip(sys);
		return ;
	}
	if (sys->index == 3)
	{
		calc_Mandelbar(sys);
		return ;
	}
	calc_fractal_nest(sys);
}

void	calc_fractal_nest(t_sys *sys)
{
	if (sys->index == 4)
	{
		calc_AbsReal(sys);
		return ;
	}
	if (sys->index == 5)
	{
		calc_AbsImg(sys);
		return ;
	}
	if (sys->index == 6)
	{
		calc_Power3(sys);
		return ;
	}
	calc_AbsRealP4(sys);
}

void	fractol_discr()
{
	puts(TEXT_TITLE);
	puts(TEXT_MAIN);
	puts(TEXT_FRACTALS);
	exit(0);
}








