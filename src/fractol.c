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
	{
		puts("Hello\n");
		exit(0);
	}

	if (!(sys = (t_sys *)malloc(sizeof(t_sys))))
		exit(0);

	if (argc == 1)
		sys->index = 1;
	if (argc == 2)
	{
		if (strlen(argv[1]) != 1 || argv[1][0] < '1' || argv[1][0] > '8')
		{
			puts("Hello\n");
			exit(0);
		}
		sys->index = atoi(argv[1]) - 1;
	}

	set_system(sys);
	clear_image(sys);
	clear_stat(sys);
	draw_menu(sys);

	// printf("%d %d\n", sys->cursor[0], sys->cursor[1]);
	// printf("1: %d %d\n", sys->delta0[0], sys->delta0[1]);
	// printf("2: %d %d\n", sys->delta[0], sys->delta[1]);
	calc_fractal(sys);
	// draw_axis(sys);

	mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
	mlx_put_image_to_window(sys->mlx, sys->win, sys->mnu, WIDTH - MENU_W, 0);
	mlx_put_image_to_window(sys->mlx, sys->win, sys->stat, WIDTH - MENU_W, HEIGHT / 2);

	mlx_string_put(sys->mlx, sys->win, (WIDTH - MENU_W) + 10, (HEIGHT / 2) + 10, 0x00FF00, sys->name);
	// mlx_string_put(sys->mlx, sys->win, 0, 0, 0x00FF00, sys->name);

	mlx_hook(sys->win, 2, 0, key_press, sys);
	mlx_hook(sys->win, 3, 0, key_release, sys);
	mlx_hook(sys->win, 4, 0, mouse_press, sys);
	mlx_hook(sys->win, 5, 0, mouse_release, sys);
	mlx_hook(sys->win, 6, 0, mouse_move, sys);
	mlx_hook(sys->win, 17, 0, close_fractol, sys);
	mlx_loop(sys->mlx);

	return (0);
}

void	set_system(t_sys *sys)
{
	sys->mlx = mlx_init();
	sys->win = mlx_new_window(sys->mlx, WIDTH, HEIGHT, "fractol");
	
	sys->imgvol = (WIDTH - MENU_W) * HEIGHT;
	sys->img = mlx_new_image(sys->mlx, WIDTH - MENU_W, HEIGHT);
	sys->imgout = (int *)mlx_get_data_addr(sys->img,
		&sys->img_s[0], &sys->img_s[1], &sys->img_s[2]);

	sys->mnuvol = MENU_W * HEIGHT / 2;
	sys->mnu = mlx_new_image(sys->mlx, MENU_W, HEIGHT / 2);
	sys->mnuout = (int *)mlx_get_data_addr(sys->mnu,
		&sys->mnu_s[0], &sys->mnu_s[1], &sys->mnu_s[2]);

	sys->statvol = MENU_W * HEIGHT / 2;
	sys->stat = mlx_new_image(sys->mlx, MENU_W, HEIGHT / 2);
	sys->statout = (int *)mlx_get_data_addr(sys->stat,
		&sys->stat_s[0], &sys->stat_s[1], &sys->stat_s[2]);

	
	sys->bitset = 0b00000100;
	sys->name = "Mandelbrot";
	sys->color = 0xFF0000;


	sys->cursor[0] = 0;
	sys->cursor[1] = 0;


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


		sys->k[(int)i] = init_comp(0, 0);
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
		sys->statout[i] = STAT_C;
		i += 1;
	}
}

void	draw_menu(t_sys *sys)
{
	int		i;

	i = 0;
	while (i < sys->mnuvol)
	{
		sys->mnuout[i] = MENU_C;
		i += 1;
	}
	sys->rgbtris_y[0] = 100;
	draw_rgbtriangle(sys, MENU_W / 2, 10);
}

int		close_fractol(void *param)
{
	(void)param;
	exit(0);
}

// // // NOT NEED UNCOMMENT !!!!!!!!!!!!!
// t_comp	int_to_comp(t_sys *sys, int id)
// {
// 	t_comp	complex;

// 	complex.real = id % (WIDTH - MENU_W);
// 	complex.img = -id / (WIDTH - MENU_W);
// 	complex.real -= (WIDTH - MENU_W) / 2 + sys->shift[(int)sys->index][0];
// 	complex.img += HEIGHT / 2 + sys->shift[(int)sys->index][1];
// 	complex.real /= sys->scale;
// 	complex.img /= sys->scale;
// 	return (complex);
// }





// //--------------STAR_TESTINGVERSION------------------
// t_comp	int_to_comp(t_sys *sys, int id)
// {
// 	// static int i = 0;
// 	// sys->cursor[0] -= (WIDTH - MENU_W) / 2;
// 	// sys->cursor[1] -=  HEIGHT / 2;

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
// 	// shift_1d = offset_x + (WIDTH - MENU_W) * offset_y;


// 	// int		shift_1d;
// 	// sys->delta[0] = sys->delta0[0];
// 	// sys->delta[1] = sys->delta0[1];	
// 	// sys->delta[0] = lround(shiftcomp.real);
// 	// sys->delta[1] = lround(shiftcomp.img);
// 	// shift_1d = sys->delta[0] + (WIDTH - MENU_W) * sys->delta[1];

// 	// id += shift_1d;

// 	// if (sys->scale0 != sys->scale)
// 	// 	id += sys->cursor[0] + (WIDTH - MENU_W) * sys->cursor[1];

// 	sys->delta[0] = lround(shiftcomp.real);
// 	sys->delta[1] = lround(shiftcomp.img);
// 	// sys->delta[0] += sys->delta0[0];
// 	// sys->delta[1] += sys->delta0[1];




// 	t_comp	complex;
// 	complex.real = id % (WIDTH - MENU_W);
// 	complex.real += sys->delta0[0];
// 	complex.real += sys->delta[0];

// 	complex.img = id / (WIDTH - MENU_W);
// 	complex.img += sys->delta0[1];
// 	complex.img += sys->delta[1];


// 	complex.real /= (double)sys->scale;
// 	complex.img /= (double)sys->scale;

// 	//-------------------
	
// 	// id -= (WIDTH - MENU_W) / 2 + (WIDTH - MENU_W) * HEIGHT / 2;
// 	// // id += shift_1d;

// 	// t_comp	complex;
// 	// if (id < 0 && -id % (WIDTH - MENU_W) > (WIDTH - MENU_W) / 2)
// 	// {
// 	// 	complex.real = (WIDTH - MENU_W) + id % (WIDTH - MENU_W);
// 	// 	complex.img = id / (WIDTH - MENU_W) - 1;
// 	// }
// 	// else if (id > 0 && id % (WIDTH - MENU_W) >= (WIDTH - MENU_W) / 2)
// 	// {
// 	// 	complex.real = -(WIDTH - MENU_W) + id % (WIDTH - MENU_W);
// 	// 	complex.img = id / (WIDTH - MENU_W) + 1;
// 	// }
// 	// else
// 	// {
// 	// 	complex.real = id % (WIDTH - MENU_W);
// 	// 	complex.img = id / (WIDTH - MENU_W);
// 	// }


// 	// int		comp_1d;
// 	// comp_1d = lround((complex.real + (WIDTH - MENU_W) * complex.img) * sys->scale);

// 	// int		shift_1d;
// 	// int		offset_x;
// 	// int		offset_y;
// 	// offset_x = 10; // "-" is right offset
// 	// offset_y = 10; // "-" is down offset 
// 	// shift_1d = offset_x + (WIDTH - MENU_W) * offset_y;

// 	// comp_1d += shift_1d;

// 	// complex.real = comp_1d % (WIDTH - MENU_W) / (double)sys->scale;
// 	// complex.img = comp_1d / (WIDTH - MENU_W) / (double)sys->scale;
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
	
	id -= (WIDTH - MENU_W) / 2 + (WIDTH - MENU_W) * HEIGHT / 2;

	// id = id + sys->shift[(int)sys->index][0] + (WIDTH - MENU_W) * sys->shift[(int)sys->index][1];

	
	// sys->delta[0] = sys->delta0[0] + sys->delta[0] - sys->shift[(int)sys->index][0];
	// sys->delta[1] = sys->delta0[1] + sys->delta[1] - sys->shift[(int)sys->index][1];
	conv_1d_2d(sys, id, &id2d[0]);

	// id2d[0] -= sys->shift[(int)sys->index][0];
	// id2d[1] -= sys->shift[(int)sys->index][1];

	complex = init_comp(id2d[0] / (double)sys->scale[1][(int)sys->index], -id2d[1] / (double)sys->scale[1][(int)sys->index]);

	// complex.real -= (WIDTH - MENU_W) / 2 + sys->shift[(int)sys->index][0];
	// complex.img += HEIGHT / 2 + sys->shift[(int)sys->index][1];

	// complex.real /= (double)sys->scale;
	// complex.img /= (double)sys->scale;
	return (complex);
}

// 	t_comp	complex;
// 	complex.real = id % (WIDTH - MENU_W);
// 	complex.real += sys->delta0[0];
// 	complex.real += sys->delta[0];


// void	conv_1d_2d(t_sys *sys, int id, int *id2d)
// {
// 	int		halfwidth = (WIDTH - MENU_W) / 2;

// 	id2d[0] = id % (WIDTH - MENU_W);
// 	id2d[1] = id / (WIDTH - MENU_W);
// 	if (id < 0 && -id2d[0] > halfwidth)
// 	{
// 		id2d[0] += sys->delta0[0] + (WIDTH - MENU_W) + sys->delta[0]
// 			- sys->shift[(int)sys->index][0];
// 		id2d[1] += sys->delta0[1] + -1 + sys->delta[1] - sys->shift[(int)sys->index][1];
// 		return ;
// 	}
// 	if (id > 0 && id2d[0] >= halfwidth)
// 	{
// 		id2d[0] += sys->delta0[0] + -(WIDTH - MENU_W) + sys->delta[0]
// 			- sys->shift[(int)sys->index][0];
// 		id2d[1] += sys->delta0[1] + 1 + sys->delta[1] - sys->shift[(int)sys->index][1];
// 		return ;
// 	}
// 	id2d[0] += sys->delta0[0] + sys->delta[0] - sys->shift[(int)sys->index][0];
// 	id2d[1] += sys->delta0[1] + sys->delta[1] - sys->shift[(int)sys->index][1];
// }

void	conv_1d_2d(t_sys *sys, int id, int *id2d)
{
	int		halfwidth = (WIDTH - MENU_W) / 2;

	// int		tmp[2];

	// tmp[0] = sys->delta0[0] + sys->delta[0] - sys->shift[(int)sys->index][0];
	// tmp[1] = sys->delta0[1] + sys->delta[1] - sys->shift[(int)sys->index][1];
	// tmp[0] = sys->delta[0];
	// tmp[1] = sys->delta[1];

	id2d[0] = id % (WIDTH - MENU_W);
	id2d[1] = id / (WIDTH - MENU_W);
	if (id < 0 && -id2d[0] > halfwidth)
	{
		id2d[0] += sys->delta[1][(int)sys->index][0] + (WIDTH - MENU_W);
		id2d[1] += sys->delta[1][(int)sys->index][1] - 1;
		return ;
	}
	if (id > 0 && id2d[0] >= halfwidth)
	{
		id2d[0] += sys->delta[1][(int)sys->index][0] - (WIDTH - MENU_W);
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

	// delta.real = (sys->cursor[0] - (WIDTH - MENU_W) / 2) / (double)SCALE;
	// delta.img = (sys->cursor[1] - HEIGHT / 2) / (double)SCALE;
	// scaler.real = (sys->cursor[0] - (WIDTH - MENU_W) / 2) / (double)sys->scale;
	// scaler.img = (sys->cursor[1] - HEIGHT / 2) / (double)sys->scale;
	// delta.real = (delta.real - scaler.real) * sys->scale;
	// delta.img = (delta.img - scaler.img) * sys->scale;

	// sys->delta[0] = sys->cursor[0] - (WIDTH - MENU_W) / 2;
	// sys->delta[1] = sys->cursor[1] - HEIGHT / 2;
	// scaler = (double)sys->scale / SCALE - 1;
	// sys->delta[0] *= scaler;
	// sys->delta[1] *= scaler;

	// 	t_comp	scalecomp;
	// 	scalecomp.real = sys->cursor[0] / (double)sys->scale0;
	// 	scalecomp.real += sys->delta0[0] / (double)sys->scale0;


	double	scaler;

	scaler = (double)sys->scale[1][(int)sys->index] / sys->scale[0][(int)sys->index] - 1;
	// sys->delta[(int)sys->index][0] = lround((sys->cursor[0] - (WIDTH - MENU_W) / 2 - sys->shift[(int)sys->index][0]
	// 	+ sys->delta0[(int)sys->index][0]) * scaler);
	sys->delta[1][(int)sys->index][0] = lround((sys->delta[0][(int)sys->index][0] + sys->cursor[0]
		- (WIDTH - MENU_W) / 2 - sys->shift[(int)sys->index][0]) * scaler);
	sys->delta[1][(int)sys->index][0] += sys->delta[0][(int)sys->index][0] - sys->shift[(int)sys->index][0];

	// sys->delta[(int)sys->index][1] = lround((sys->cursor[1] - HEIGHT / 2 - sys->shift[(int)sys->index][1]
	// 	+ sys->delta0[(int)sys->index][1]) * scaler);
	sys->delta[1][(int)sys->index][1] = lround((sys->delta[0][(int)sys->index][1] + sys->cursor[1]
		- HEIGHT / 2 - sys->shift[(int)sys->index][1]) * scaler);
	sys->delta[1][(int)sys->index][1] += sys->delta[0][(int)sys->index][1] - sys->shift[(int)sys->index][1];

	// double	prevpos[2];
	// double	curpos[2];

	// prevpos[0] =  sys->cursor[0] / (double)sys->scale0;
	// prevpos[0] += sys->delta0[0] / (double)sys->scale0;
	// prevpos[0] -= ((WIDTH - MENU_W) / 2) / (double)sys->scale0;
	// prevpos[0] -= sys->shift[(int)sys->index][0] / (double)sys->scale0;

	// prevpos[1] =  sys->cursor[1] / (double)sys->scale0;
	// prevpos[1] += sys->delta0[1] / (double)sys->scale0;
	// prevpos[1] -= (HEIGHT / 2) / (double)sys->scale0;
	// prevpos[1] -= sys->shift[(int)sys->index][1] / (double)sys->scale0;


	// curpos[0] =  sys->cursor[0] / (double)sys->scale;
	// curpos[0] += sys->delta0[0] / (double)sys->scale;
	// curpos[0] -= ((WIDTH - MENU_W) / 2) / (double)sys->scale;
	// curpos[0] -= sys->shift[(int)sys->index][0] / (double)sys->scale;

	// curpos[1] =  sys->cursor[1] / (double)sys->scale;
	// curpos[1] += sys->delta0[1] / (double)sys->scale;
	// curpos[1] -= (HEIGHT / 2) / (double)sys->scale;
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
	if (sys->index == 7)
	{
		calc_AbsRealP4(sys);
		return ;
	}
}










