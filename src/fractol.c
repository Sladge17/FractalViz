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
	mlx_string_put(MLX, WINMAIN, STR_X, 10, TITLE_C, "Main settings");
	mlx_string_put(MLX, WINMAIN, STR_X, 40, STR_C, "1 - 8 - choose fractal");
	mlx_string_put(MLX, WINMAIN, STR_X, 70, STR_C, "LMB - transform fractal");
	mlx_string_put(MLX, WINMAIN, STR_X, 90, STR_C, "RMB - reset transform");
	mlx_string_put(MLX, WINMAIN, STR_X, 120, STR_C, "SMB - scale fractal");
	mlx_string_put(MLX, WINMAIN, STR_X, 140, STR_C, "MMB - reset scale");
	mlx_string_put(MLX, WINMAIN, STR_X, 170, STR_C, "ARROWS - shift fractal");
	mlx_string_put(MLX, WINMAIN, STR_X, 190, STR_C, "C - centred fractal");
	mlx_string_put(MLX, WINMAIN, STR_X, 220, STR_C, "Choose fractal color:");
	mlx_string_put(MLX, WINMAIN, STR_X, 400, STR_C, "SPACE - more settings");
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








