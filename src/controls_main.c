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
		// printf("%d %d\n", sys->cursor[0], sys->cursor[1]);
		// printf("1: %d %d\n", sys->delta0[0], sys->delta0[1]);
		// printf("2: %d %d\n", sys->delta[0], sys->delta[1]);
		// sys->scale0 = SCALE;
		sys->scale += ADD_SCALE;
		def_delta(sys); //TO WORKINGVERSION
		draw_image(sys);
		// sys->scale0 = sys->scale;
		return (0);
	}

	if (keycode == 13)
	{
		if (!sys->scale)
			return (0);
		sys->scale -= ADD_SCALE;
		if (sys->scale <= 0)
		{
			sys->scale = 0;
			clear_image(sys);
			sys->imgout[sys->imgvol / 2 + (WIDTH - MENU_W) / 2] = 0xFF0000;
			mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
			return (0);
		}
		def_delta(sys);
		draw_image(sys);
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
		sys->shift[(int)sys->index][0] = 0;
		sys->shift[(int)sys->index][1] = 0;
		draw_image(sys);
		return (0);
	}

	if (keycode == 50)
	{
		sys->bitset ^= 0b00000100;
		draw_image(sys);
		return (0);
	}

	if (keycode == 48)
	{
		sys->bitset ^= 0b00001000;
		draw_image(sys);
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
		// sys->cursor0[0] = sys->cursor[0];
		// sys->cursor0[1] = sys->cursor[1];
		sys->delta0[0] = sys->delta[0] + sys->shift[(int)sys->index][0];
		sys->delta0[1] = sys->delta[1] + sys->shift[(int)sys->index][1];;
		sys->scale0 = sys->scale;
		// sys->shift[(int)sys->index][0] += sys->delta0[0];
		// sys->shift[(int)sys->index][1] += sys->delta0[1];
		// draw_image(sys);

		// sys->flag0 = 1;
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

	if (sys->bitset & 0b00000001)
	{
		sys->cursorcomp.real = (x - (WIDTH - MENU_W) / 2) / (double)sys->scale;
		sys->cursorcomp.img = -(y - HEIGHT / 2) / (double)sys->scale;
		sys->k[(int)sys->index] = sys->cursorcomp;
		draw_image(sys);
		draw_stat(sys);
		return (0);
	}

	if (x >= 0 && x < WIDTH - MENU_W && y >= 0 && y < HEIGHT)
	{
		sys->cursor[0] = x;
		sys->cursor[1] = y;

		sys->cursorcomp.real = (x - (WIDTH - MENU_W) / 2) / (double)sys->scale;
		sys->cursorcomp.img = -(y - HEIGHT / 2) / (double)sys->scale;
		// draw_image(sys);
		draw_stat(sys);
		return (0);
	}


	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;

	if (button == 1)
	{

		if (x >= 0 && x < WIDTH - MENU_W && y >= 0 && y < HEIGHT)
		{
			sys->k[(int)sys->index] = sys->cursorcomp;
			sys->bitset ^= 0b00000001;
			draw_image(sys);
			return (0);
		}

		if (x >= WIDTH - MENU_W && y >= sys->rgbtris_y[0] && y <= sys->rgbtris_y[1] &&
			sys->mnuout[x - (WIDTH - MENU_W) + MENU_W * y] != MENU_C)
		{
			if (!(sys->bitset & 0b00000100))
			{
				redraw_image(sys, x, y);
				return (0);
			}
			sys->color = sys->mnuout[x - (WIDTH - MENU_W) + MENU_W * y];
			draw_image(sys);
			return (0);
		}

		return (0);
	}

	if (button == 2)
	{

		if (sys->k[(int)sys->index].real == 0 && sys->k[(int)sys->index].img == 0)
			return (0);	
		sys->k[(int)sys->index].real = 0;
		sys->k[(int)sys->index].img = 0;
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

	if (button == 1 && sys->bitset & 0b00000001)
		sys->bitset ^= 0b00000001;
	
	return (0);
}

























