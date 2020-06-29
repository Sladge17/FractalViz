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

void	fractol_discr()
{
	puts(TEXT_TITLE);
	puts(TEXT_MAIN);
	puts(TEXT_FRACTALS);
	exit(0);
}








