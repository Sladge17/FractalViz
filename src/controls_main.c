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

	if (open_winsett(keycode, sys))
		return (0);

	if (keycode == 12)
	{
		if (sys->cursor[0] >= 0 && sys->cursor[0] < IMAGE_W && sys->cursor[1] >= 0 && sys->cursor[1] < MAIN_H)
		{
			scale_up(sys);
			write_scale(sys);
		}
		// scale_up(sys);
		// sys->scale[1][F_ID] += ADD_SCALE;
		// def_delta(sys);
		// draw_image(sys);
		return (0);
	}

	if (keycode == 13)
	{
		if (sys->cursor[0] >= 0 && sys->cursor[0] < IMAGE_W && sys->cursor[1] >= 0 && sys->cursor[1] < MAIN_H)
		{
			scale_down(sys);
			write_scale(sys);
		}
		// scale_down(sys);
		// if (sys->scale[1][F_ID] == MIN_SCALE)
		// 	return (0);
		// sys->scale[1][F_ID] -= ADD_SCALE;
		// if (sys->scale[1][F_ID] < MIN_SCALE)
		// 	sys->scale[1][F_ID] = MIN_SCALE;
		// def_delta(sys);
		// draw_image(sys);
		return (0);
	}

	if (change_fractal(keycode, sys))
		return (0);

	if (check_shiftfractal(keycode, sys))
	{
		shift_fractal(sys);
		return (0);
	}

	if (keycode == 8)
	{
		shift_reset(sys);
		// sys->shift[F_ID][0] = 0;
		// sys->shift[F_ID][1] = 0;
		// draw_image(sys);
		return (0);
	}

	if (keycode == 50)
	{
		sys->bitset ^= 0b00000100;
		draw_image(sys);
		draw_stat(sys);
		return (0);
	}

	if (keycode == 48)
	{
		sys->bitset ^= 0b00001000;
		if (sys->bitset & 0b00001000)
			draw_axis(sys);
		else
			draw_image(sys);
		draw_stat(sys);
		return (0);
	}

	return (0);
}

int		key_release(int keycode, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;

	if (keycode == 12 || keycode == 13)
	{
		set_deltazero(sys);
		// sys->delta[0][F_ID][0] = sys->delta[1][F_ID][0] + sys->shift[F_ID][0];
		// sys->delta[0][F_ID][1] = sys->delta[1][F_ID][1] + sys->shift[F_ID][1];
		// sys->scale[0][F_ID] = sys->scale[1][F_ID];
		return (0);
	}

	// keycode = 1;
	if (check_unshiftfractal(keycode, sys))
		return (0);
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
		sys->cursorcomp.real = (x - IMAGE_CENTRX) / (double)sys->scale[1][F_ID];
		sys->cursorcomp.img = -(y - IMAGE_CENTRY) / (double)sys->scale[1][F_ID];
		sys->k[F_ID] = sys->cursorcomp;
		draw_image(sys);
		
		write_cursor(sys, 0);
		write_k(sys);
		return (0);
	}

	if (x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H)
	{
		sys->bitset |= 0b100000000;
		// sys->cursor[0] = x;
		// sys->cursor[1] = y;

		sys->cursorcomp.real = (x - IMAGE_CENTRX) / (double)sys->scale[1][F_ID];
		sys->cursorcomp.img = -(y - IMAGE_CENTRY) / (double)sys->scale[1][F_ID];

		write_cursor(sys, 1);
		// draw_image(sys);
		// draw_stat(sys);
		return (0);
	}
	if (sys->bitset & 0b100000000)
	{
		sys->str_cursor[0][7] = '\0';
		sys->str_cursor[0] = ft_strcat(sys->str_cursor[0], "not def");
		sys->str_cursor[1][6] = '\0';
		sys->str_cursor[1] = ft_strcat(sys->str_cursor[1], "not def");
		draw_stat(sys);
		sys->bitset ^= 0b100000000;
	}

	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;

	if (button == 1)
	{

		if (x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H)
		{
			sys->k[F_ID] = sys->cursorcomp;
			sys->bitset ^= 0b00000001;
			draw_image(sys);

			write_k(sys);

			return (0);
		}

		if (x >= IMAGE_W && y >= sys->rgbtris_y[0] && y <= sys->rgbtris_y[1] &&
			sys->mlxset->mnuout[x - IMAGE_W + MENU_W * y] != MENU_C)
		{
			if (sys->bitset & 0b00000100)
			{
				redraw_image(sys, x, y);
				write_color(sys);
				return (0);
			}
			sys->color = sys->mlxset->mnuout[x - IMAGE_W + MENU_W * y];
			draw_image(sys);
			write_color(sys);
			return (0);
		}

		return (0);
	}

	if (button == 2 && x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H)
	{

		if (sys->k[F_ID].real == 0 && sys->k[F_ID].img == 0)
			return (0);	
		sys->k[F_ID].real = 0;
		sys->k[F_ID].img = 0;
		draw_image(sys);

		sys->str_k[F_ID][4] = '\0';
		sys->str_k[F_ID] = ft_strcat(sys->str_k[F_ID], "0.000 + 0.000i");

		draw_stat(sys);
		return (0);
	}

	if (button == 3 && x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H)
	{
		scale_reset(sys);
		return (0);	
	}

	if (button == 4 && x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H)
	{
		scale_down(sys);
		write_scale(sys);
		set_deltazero(sys);
		return (0);
	}

	if (button == 5 && x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H)
	{
		scale_up(sys);
		write_scale(sys);
		set_deltazero(sys);
		return (0);		
	}

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
		{
			sys->str_cursor[0][7] = '\0';
			sys->str_cursor[0] = ft_strcat(sys->str_cursor[0], "not def");
			sys->str_cursor[1][6] = '\0';
			sys->str_cursor[1] = ft_strcat(sys->str_cursor[1], "not def");
			draw_stat(sys);
			sys->bitset ^= 0b100000000;
		}
	}
	
	return (0);
}



