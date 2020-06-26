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
	draw_winmain(sys, argc, argv[1]);
	clear_settings(sys);
	mlx_hook(WINMAIN, 2, 0, key_press, sys);
	mlx_hook(WINMAIN, 3, 0, key_release, sys);
	mlx_hook(WINMAIN, 4, 0, mouse_press, sys);
	mlx_hook(WINMAIN, 5, 0, mouse_release, sys);
	mlx_hook(WINMAIN, 6, 0, mouse_move, sys);
	mlx_hook(WINMAIN, 17, 0, close_fractol, sys);
	mlx_loop(MLX);
	return (0);
}

void	set_consts(t_sys *sys)
{
	if (!(sys->consts = (t_consts *)malloc(sizeof(t_consts))))
		exit(0);
	IMAGE_W = MAIN_W - MENU_W;
	IMAGE_VOL = IMAGE_W * MAIN_H;
	MENU_VOL = MENU_W * MAIN_H;
	STAT_VOL = MENU_W * STAT_H;
	SETT_VOL = SETT_W * SETT_H;

	IMAGE_CENTRX = IMAGE_W / 2;
	IMAGE_CENTRY = MAIN_H / 2;
	IMAGE_CENTER = IMAGE_CENTRX + IMAGE_W * IMAGE_CENTRY;

	XSTR = IMAGE_W + 10;
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
	sys->mlxset->setout = (int *)mlx_get_data_addr(SETT,
		&sys->mlxset->set_s[0],
		&sys->mlxset->set_s[1],
		&sys->mlxset->set_s[2]);
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
	set_consts(sys);
	set_mlxset(sys);

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
	while (i < IMAGE_VOL)
	{
		sys->mlxset->imgout[i] = IMAGE_C;
		i += 1;
	}
}

void	clear_stat(t_sys *sys)
{
	int		i;
	
	i = 0;
	while (i < STAT_VOL)
	{
		sys->mlxset->statout[i] = 0;
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
	while (i < MENU_VOL)
	{
		sys->mlxset->mnuout[i] = MENU_C;
		i += 1;
	}
	sys->rgbtris_y[0] = 245;
	draw_rgbtriangle(sys, MENU_W / 2, 40);
	mlx_put_image_to_window(MLX, WINMAIN, MENU, IMAGE_W, 0);
	mlx_string_put(MLX, WINMAIN, XSTR, 10, TITLE_C, "Main settings");
	mlx_string_put(MLX, WINMAIN, XSTR, 40, TEXT_C, "1 - 8 - choose fractal");
	mlx_string_put(MLX, WINMAIN, XSTR, 70, TEXT_C, "LMB - transform fractal");
	mlx_string_put(MLX, WINMAIN, XSTR, 90, TEXT_C, "RMB - reset transform");
	mlx_string_put(MLX, WINMAIN, XSTR, 120, TEXT_C, "SMB - scale fractal");
	mlx_string_put(MLX, WINMAIN, XSTR, 140, TEXT_C, "MMB - reset scale");
	mlx_string_put(MLX, WINMAIN, XSTR, 170, TEXT_C, "ARROWS - shift fractal");
	mlx_string_put(MLX, WINMAIN, XSTR, 190, TEXT_C, "C - centred fractal");
	mlx_string_put(MLX, WINMAIN, XSTR, 220, TEXT_C, "Choose fractal color:");
	mlx_string_put(MLX, WINMAIN, XSTR, 400, TEXT_C, "SPACE - more settings");
}


void	clear_settings(t_sys *sys)
{
	int		i;

	i = 0;
	while (i < SETT_VOL)
	{
		sys->mlxset->setout[i] = MENU_C;
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

	id -= IMAGE_CENTER;
	conv_1d_2d(sys, id, &id2d[0]);
	complex = init_comp(id2d[0] / (double)sys->scale[1][F_ID],
		-id2d[1] / (double)sys->scale[1][F_ID]);
	return (complex);
}

void	conv_1d_2d(t_sys *sys, int id, int *id2d)
{
	id2d[0] = id % IMAGE_W;
	id2d[1] = id / IMAGE_W;
	if (id < 0 && -id2d[0] > IMAGE_CENTRX)
	{
		id2d[0] += sys->delta[1][F_ID][0] + IMAGE_W;
		id2d[1] += sys->delta[1][F_ID][1] - 1;
		return ;
	}
	if (id > 0 && id2d[0] >= IMAGE_CENTRX)
	{
		id2d[0] += sys->delta[1][F_ID][0] - IMAGE_W;
		id2d[1] += sys->delta[1][F_ID][1] + 1;
		return ;
	}
	id2d[0] += sys->delta[1][F_ID][0];
	id2d[1] += sys->delta[1][F_ID][1];
}

void	def_delta(t_sys *sys)
{
	double	scaler;

	scaler = (double)sys->scale[1][F_ID]
		/ sys->scale[0][F_ID] - 1;

	sys->delta[1][F_ID][0] = lround((sys->delta[0][F_ID][0] + sys->cursor[0]
		- (MAIN_W - MENU_W) / 2 - sys->shift[F_ID][0]) * scaler);
	sys->delta[1][F_ID][0] += sys->delta[0][F_ID][0] - sys->shift[F_ID][0];

	sys->delta[1][F_ID][1] = lround((sys->delta[0][F_ID][1] + sys->cursor[1]
		- MAIN_H / 2 - sys->shift[F_ID][1]) * scaler);
	sys->delta[1][F_ID][1] += sys->delta[0][F_ID][1] - sys->shift[F_ID][1];
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








