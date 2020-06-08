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

	calc_fractal(sys);

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

	sys->scale = 200;
	sys->bitset = 0b00000100;
	sys->name = "Mandelbrot";
	sys->color = 0xFF0000;

	// sys->cursor[0] = (WIDTH - MENU_W) / 2;
	// sys->cursor[1] = HEIGHT / 2;

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

t_comp	int_to_comp(t_sys *sys, int id)
{
	t_comp	complex;

	t_comp	cursor;

	// id -= (WIDTH - MENU_W) / 2 + (WIDTH - MENU_W) * HEIGHT / 2;
	// id += sys->cursor[0] + (WIDTH - MENU_W) * sys->cursor[1];
	complex.real = id % (WIDTH - MENU_W);
	complex.img = id / (WIDTH - MENU_W);

	id += sys->cursor[0] + (WIDTH - MENU_W) * sys->cursor[1];
	cursor.real = id % (WIDTH - MENU_W);
	cursor.img = id / (WIDTH - MENU_W);

	// add_comp(t_comp comp, t_comp comp_add)

	complex = add_comp(complex, cursor);

	// complex.real -=  sys->cursor[0];
	// complex.img -= sys->cursor[1];


	complex.real -= (WIDTH - MENU_W) / 2;
	complex.img -= HEIGHT / 2;

	// complex.real -=  sys->cursor[0];
	// complex.img -= sys->cursor[1];

	complex.real /= sys->scale;
	complex.img /= sys->scale;





	// NEED UNCOMMENT !!!!!!!!!!!!!
	// complex.real = id % (WIDTH - MENU_W);
	// complex.img = -id / (WIDTH - MENU_W);
	// complex.real -= (WIDTH - MENU_W) / 2 + sys->shift[(int)sys->index][0];
	// complex.img += HEIGHT / 2 + sys->shift[(int)sys->index][1];



	// complex.real -= (WIDTH - MENU_W) / 2 + sys->shift[(int)sys->index][0];
	// complex.img -= HEIGHT / 2 + sys->shift[(int)sys->index][1];

	return (complex);
}

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










