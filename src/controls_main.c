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

void		*win2;

int		key_press(int keycode, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;

	if (keycode == 53)
		exit(0);

	
	if (keycode == 49)
	{
		sys->bitset ^= 0b00000010;
		if (sys->bitset & 0b00000010)
		{
			sys->win_set = mlx_new_window(sys->mlx, SET_W, SET_H, "settings");
			mlx_put_image_to_window(sys->mlx, sys->win_set, sys->set, 0, 0);
			mlx_string_put(sys->mlx, sys->win_set, 10, 10, 0x00FF00, "Test-test");
			mlx_hook(sys->win_set, 2, 0, key_press, sys);
			mlx_hook(sys->win_set, 17, 0, close_setting, sys);
		}
		else
			mlx_destroy_window(sys->mlx, sys->win_set);
		return (0);
	}


	if (keycode == 12)
	{
		scale_up(sys);
		// sys->scale[1][(int)sys->index] += ADD_SCALE;
		// def_delta(sys);
		// draw_image(sys);
		return (0);
	}

	if (keycode == 13)
	{
		scale_down(sys);
		// if (sys->scale[1][(int)sys->index] == MIN_SCALE)
		// 	return (0);
		// sys->scale[1][(int)sys->index] -= ADD_SCALE;
		// if (sys->scale[1][(int)sys->index] < MIN_SCALE)
		// 	sys->scale[1][(int)sys->index] = MIN_SCALE;
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
		// sys->shift[(int)sys->index][0] = 0;
		// sys->shift[(int)sys->index][1] = 0;
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
		// sys->delta[0][(int)sys->index][0] = sys->delta[1][(int)sys->index][0] + sys->shift[(int)sys->index][0];
		// sys->delta[0][(int)sys->index][1] = sys->delta[1][(int)sys->index][1] + sys->shift[(int)sys->index][1];
		// sys->scale[0][(int)sys->index] = sys->scale[1][(int)sys->index];
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
		sys->cursorcomp.real = (x - (MAIN_W - MENU_W) / 2) / (double)sys->scale[1][(int)sys->index];
		sys->cursorcomp.img = -(y - MAIN_H / 2) / (double)sys->scale[1][(int)sys->index];
		sys->k[(int)sys->index] = sys->cursorcomp;
		draw_image(sys);
		write_k(sys);
		return (0);
	}

	if (x >= 0 && x < MAIN_W - MENU_W && y >= 0 && y < MAIN_H)
	{
		sys->cursor[0] = x;
		sys->cursor[1] = y;

		sys->cursorcomp.real = (x - (MAIN_W - MENU_W) / 2) / (double)sys->scale[1][(int)sys->index];
		sys->cursorcomp.img = -(y - MAIN_H / 2) / (double)sys->scale[1][(int)sys->index];
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

		if (x >= 0 && x < MAIN_W - MENU_W && y >= 0 && y < MAIN_H)
		{
			sys->k[(int)sys->index] = sys->cursorcomp;
			sys->bitset ^= 0b00000001;
			draw_image(sys);

			write_k(sys);

			return (0);
		}

		if (x >= MAIN_W - MENU_W && y >= sys->rgbtris_y[0] && y <= sys->rgbtris_y[1] &&
			sys->mnuout[x - (MAIN_W - MENU_W) + MENU_W * y] != MENU_C)
		{
			if (!(sys->bitset & 0b00000100))
			{
				redraw_image(sys, x, y);
				return (0);
			}
			sys->color = sys->mnuout[x - (MAIN_W - MENU_W) + MENU_W * y];
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

		sys->str_k[(int)sys->index][4] = '\0';
		sys->str_k[(int)sys->index] = ft_strcat(sys->str_k[(int)sys->index], "0.000 + 0.000i");

		draw_stat(sys);
		return (0);
	}

	if (button == 3)
	{
		scale_reset(sys);
		sys->str_scale[(int)sys->index][8] = '\0';
		sys->str_scale[(int)sys->index] = ft_strcat(sys->str_scale[(int)sys->index], "1.000");
		draw_stat(sys);
		// sys->scale[0][(int)sys->index] = DEF_SCALE;
		// sys->scale[1][(int)sys->index] = DEF_SCALE;
		// sys->shift[(int)sys->index][0] = 0;
		// sys->shift[(int)sys->index][1] = 0;
		// sys->delta[0][(int)sys->index][0] = 0;
		// sys->delta[0][(int)sys->index][1] = 0;
		// sys->delta[1][(int)sys->index][0] = 0;
		// sys->delta[1][(int)sys->index][1] = 0;
		// draw_image(sys);
		return (0);	
	}

	if (button == 4)
	{
		scale_down(sys);
		set_deltazero(sys);
		
		write_scale(sys);

		// if (sys->scale[1][(int)sys->index] == MIN_SCALE)
		// 	return (0);
		// sys->scale[1][(int)sys->index] -= ADD_SCALE;
		// if (sys->scale[1][(int)sys->index] < MIN_SCALE)
		// 	sys->scale[1][(int)sys->index] = MIN_SCALE;
		// def_delta(sys);
		// draw_image(sys);
		// sys->delta[0][(int)sys->index][0] = sys->delta[1][(int)sys->index][0] + sys->shift[(int)sys->index][0];
		// sys->delta[0][(int)sys->index][1] = sys->delta[1][(int)sys->index][1] + sys->shift[(int)sys->index][1];
		// sys->scale[0][(int)sys->index] = sys->scale[1][(int)sys->index];
		return (0);
	}

	if (button == 5)
	{
		scale_up(sys);
		set_deltazero(sys);
		
		write_scale(sys);

		// sys->scale[1][(int)sys->index] += ADD_SCALE;

		// def_delta(sys);
		// draw_image(sys);
		// sys->delta[0][(int)sys->index][0] = sys->delta[1][(int)sys->index][0] + sys->shift[(int)sys->index][0];
		// sys->delta[0][(int)sys->index][1] = sys->delta[1][(int)sys->index][1] + sys->shift[(int)sys->index][1];
		// sys->scale[0][(int)sys->index] = sys->scale[1][(int)sys->index];
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


void	write_k(t_sys *sys)
{
	char	*real;
	char	*img;
	char	*pointer;
	char	i;

	real = double_to_str(sys->cursorcomp.real);
	img = double_to_str(sys->cursorcomp.img);
	pointer = real;
	
	i = 4;
	while (*pointer != '\0')
	{
		sys->str_k[(int)sys->index][(int)i] = *pointer;
		pointer += 1;
		i += 1;
	}
	sys->str_k[(int)sys->index][(int)i] = ' ';
	sys->str_k[(int)sys->index][(int)i + 1] = '+';
	sys->str_k[(int)sys->index][(int)i + 2] = ' ';
	i += 3;

	pointer = img;
	while (*pointer != '\0')
	{
		sys->str_k[(int)sys->index][(int)i] = *pointer;
		pointer += 1;
		i += 1;
	}
	sys->str_k[(int)sys->index][(int)i] = 'i';
	sys->str_k[(int)sys->index][(int)i + 1] = '\0';
	draw_stat(sys);
}

void	write_scale(t_sys *sys)
{
	char	*scale;
	char	*pointer;
	char	i;

	scale = double_to_str(sys->scale[1][(int)sys->index] / (double)DEF_SCALE);
	pointer = scale;
	i = 8;
	while (*pointer != '\0')
	{
		sys->str_scale[(int)sys->index][(int)i] = *pointer;
		pointer += 1;
		i += 1;
	}
	sys->str_scale[(int)sys->index][(int)i] = '\0';
	draw_stat(sys);
}






















