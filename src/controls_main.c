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
	if (change_fractal(keycode, sys))
		return (0);
	if (turn_multythreading(keycode, sys))
		return (0);
	if (shift_fractal_k(keycode, sys))
		return (0);
	if (scale_fractal_k(keycode, sys))
		return (0);
	if (isolation_mode(keycode, sys))
		return (0);
	if (complex_axis(keycode, sys))
		return (0);
	if (open_winsett(keycode, sys))
		return (0);
	return (0);
}

int		key_release(int keycode, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;

	if (keycode == 12 || keycode == 13)
	{
		set_deltazero(sys);
		return (0);
	}
	if (check_unshiftfractal(keycode, sys))
		return (0);
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;
	if (click_lmb(sys, button, x, y))
		return (0);
	if (click_rmb(sys, button, x, y))
		return (0);
	if (click_mmb(sys, button, x, y))
		return (0);
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;
	if (button == 1 && sys->bitset & 0b00000001)
	{
		sys->bitset ^= 0b00000001;
		if (!(x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H))
			cursor_outside(sys);
	}
	
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;
	sys->cursor[0] = x;
	sys->cursor[1] = y;
	if (sys->bitset & 0b00000001)
	{
		cursor_inttocomp(sys, x, y);
		sys->k[F_ID] = sys->cursorcomp;
		draw_image(sys);
		write_cursor(sys, 0);
		write_k(sys);
		return (0);
	}
	if (x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H)
	{
		sys->bitset |= 0b100000000;
		cursor_inttocomp(sys, x, y);
		write_cursor(sys, 1);
		return (0);
	}
	if (sys->bitset & 0b100000000)
		cursor_outside(sys);
	return (0);
}
