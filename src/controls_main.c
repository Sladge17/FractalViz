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
		draw_image(sys);
		return (0);
	}

	if (keycode == 13)
	{
		if (!sys->scale)
			return (0);
		sys->scale -= 10;
		if (sys->scale <= 0)
		{
			sys->scale = 0;
			clear_screen(sys);
			sys->imgout[sys->imgvol / 2 + (WIDTH - MENU_W) / 2] = 0xFF0000;
			mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
			return (0);
		}
		draw_image(sys);
		return (0);
	}

	if (change_fractal(keycode, sys))
		return (0);

	if (keycode == 50)
	{
		sys->bitset ^= 0b00001000;
		draw_image(sys);
		return (0);
	}

	if (keycode == 48)
	{
		sys->bitset ^= 0b00010000;
		draw_image(sys);
		return (0);
	}

	return (0);
}

char	change_fractal(int keycode, t_sys *sys)
{
	if (keycode == 18)
	{
		if (sys->fract == 0)
			return (1);
		sys->fract = 0;
		draw_image(sys);
		return (1);
	}

	if (keycode == 19)
	{
		if (sys->fract == 1)
			return (1);
		sys->fract = 1;
		draw_image(sys);
		return (1);
	}

	if (keycode == 20)
	{
		if (sys->fract == 2)
			return (1);
		sys->fract = 2;
		draw_image(sys);
		return (1);
	}

	if (keycode == 21)
	{
		if (sys->fract == 3)
			return (1);
		sys->fract = 3;
		draw_image(sys);
		return (1);
	}

	if (keycode == 23)
	{
		if (sys->fract == 4)
			return (1);
		sys->fract = 4;
		draw_image(sys);
		return (1);
	}

	if (keycode == 22)
	{
		if (sys->fract == 5)
			return (1);
		sys->fract = 5;
		draw_image(sys);
		return (1);
	}

	if (keycode == 26)
	{
		if (sys->fract == 6)
			return (1);
		sys->fract = 6;
		draw_image(sys);
		return (1);
	}

	if (keycode == 28)
	{
		if (sys->fract == 7)
			return (1);
		sys->fract = 7;
		draw_image(sys);
		return (1);
	}

	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;
	
	if (!(sys->bitset & 0b00000001))
		return (0);

	sys->k[(int)sys->fract] = init_comp((double)(x - (WIDTH - MENU_W) / 2) / 400, (double)(y - HEIGHT / 2) / 400);
	draw_image(sys);

	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;

	if (button == 1)
	{
		sys->k[(int)sys->fract] = init_comp((double)(x - (WIDTH - MENU_W) / 2) / 400, (double)(y - HEIGHT / 2) / 400);
		draw_image(sys);
		sys->bitset ^= 0b00000001;
		return (0);
	}

	if (button == 2)
	{

		if (sys->k[(int)sys->fract].real == 0 && sys->k[(int)sys->fract].img == 0)
			return (0);	
		sys->k[(int)sys->fract].real = 0;
		sys->k[(int)sys->fract].img = 0;
		draw_image(sys);
		return (0);
	} 

	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_sys		*sys;

	x = 0;
	y = 0;
	sys = (t_sys *)param;

	if (button == 1)
		sys->bitset ^= 0b00000001;
	
	return (0);
}





























