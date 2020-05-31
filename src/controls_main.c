/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:25:51 by student           #+#    #+#             */
/*   Updated: 2020/05/28 09:25:54 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_press(int keycode, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;

	if (keycode == 53)
		exit(0);

	if (keycode == 12)
	{
		sys->scale += 10;
		fill_screen(sys);
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
	}

	if (keycode == 13)
	{
		if (!sys->scale)
			return (0);
		fill_screen(sys);
		sys->scale -= 10;
		if (sys->scale <= 0)
		{
			sys->scale = 0;
			sys->imgout[sys->imgvol / 2 + (WIDTH - MENU_W) / 2] = 0xFF0000;
			mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
			return (0);
		}
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
	}

	if (change_fractal(keycode, sys))
		return (0);

	if (keycode == 50)
	{
		sys->bitset ^= 0b10000000;
		fill_screen(sys);
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
	}

	return (0);
}

char	change_fractal(int keycode, t_sys *sys)
{
	if (keycode == 18)
	{
		sys->bitset &= 0b10000000;
		sys->bitset |= 0b00000001;
		fill_screen(sys);
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
		return (1);
	}

	if (keycode == 19)
	{
		sys->bitset &= 0b10000000;
		sys->bitset |= 0b00000010;
		fill_screen(sys);
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
		return (1);
	}

	if (keycode == 20)
	{
		sys->bitset &= 0b10000000;
		sys->bitset |= 0b00000100;
		fill_screen(sys);
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
		return (1);
	}

	if (keycode == 21)
	{
		sys->bitset &= 0b10000000;
		sys->bitset |= 0b00001000;
		fill_screen(sys);
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
		return (1);
	}

	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;
	
	if (!(sys->bitset & 0b01000000))
		return (0);

	// sys->c = init_comp((double)(x - (WIDTH - MENU_W) / 2) / (sys->scale * 2), (double)(y - HEIGHT / 2) / (sys->scale * 2));
	sys->k = init_comp((double)(x - (WIDTH - MENU_W) / 2) / 400, (double)(y - HEIGHT / 2) / 400);
	fill_screen(sys);
	calc_fractal(sys);
	mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);

	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;

	
	if (button == 1)
	{
		sys->k = init_comp((double)(x - (WIDTH - MENU_W) / 2) / 400, (double)(y - HEIGHT / 2) / 400);
		fill_screen(sys);
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
		sys->bitset ^= 0b01000000;
		return (0);
	}




	if (button == 2)
	{
		if (sys->k.real == 0 && sys->k.img == 0)
			return (0);
		sys->k.real = 0;
		sys->k.img = 0;
		fill_screen(sys);
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
		return (0);
	} 


	// if (!(sys->bitset & 0b00000011) || button != 1)
	// 	return (0);


	// sys->c = init_comp((double)(x - (WIDTH - MENU_W) / 2) / 400, (double)(y - HEIGHT / 2) / 400);


	// fill_screen(sys);
	// calc_fractal(sys);
	// mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);

	// sys->bitset ^= 0b01000000;

	// if ((sys->bitset & 0b00000010) && button == 1)
	// 	sys->bitset ^= 0b01000000;



	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_sys		*sys;

	x = 0;
	y = 0;
	sys = (t_sys *)param;

	if (button == 1)
		sys->bitset ^= 0b01000000;
	
	return (0);
}





























