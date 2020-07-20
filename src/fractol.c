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

void	draw_winmain(t_sys *sys, int argc, char *argv)
{
	if (argc == 1)
	{
		sys->index = 1;
		set_system(sys);
		sys->str_name = "name: Mandelbrot";
		KERNEL = clCreateKernel(PROGRAM, "Mandelbrot", NULL);
		calc_mandelbrot(sys);
	}
	else
	{
		if (ft_strlen(argv) != 1 || argv[0] < '1' || argv[0] > '8')
			fractol_discr();
		sys->index = ft_atoi(argv) - 1;
		set_system(sys);
		set_fractsett(sys);
		calc_fractal(sys);
	}
	WINMAIN = mlx_new_window(MLX, MAIN_W, MAIN_H, "fractol");
	mlx_put_image_to_window(MLX, WINMAIN, IMAGE, 0, 0);
	draw_menu(sys);
	draw_stat(sys);
}

void	fractol_discr(void)
{
	puts(TEXT_TITLE);
	puts(TEXT_MAIN);
	puts(TEXT_FRACTALS);
	exit(0);
}

void	set_deltazero(t_sys *sys)
{
	sys->delta[0][F_ID][0] = sys->delta[1][F_ID][0] + sys->shift[F_ID][0];
	sys->delta[0][F_ID][1] = sys->delta[1][F_ID][1] + sys->shift[F_ID][1];
	sys->scale[0][F_ID] = sys->scale[1][F_ID];
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
