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

	
	if (keycode == 49)
	{
		sys->bitset ^= 0b00000010;
		if (sys->bitset & 0b00000010)
		{
			WINSETT = mlx_new_window(MLX, SETT_W, SETT_H, "settings");
			mlx_put_image_to_window(MLX, WINSETT, SETT, 0, 0);
			mlx_string_put(MLX, WINSETT, 20, 20, TITLE_C, "Available fractals:");
			mlx_string_put(MLX, WINSETT, 20, 45, STR_C, "1 - Zulia");
			mlx_string_put(MLX, WINSETT, 20, 70, STR_C, "2 - Mandelbrot");
			mlx_string_put(MLX, WINSETT, 20, 95, STR_C, "3 - BurningShip");
			mlx_string_put(MLX, WINSETT, 20, 120, STR_C, "4 - Mandelbar");
			mlx_string_put(MLX, WINSETT, 20, 145, STR_C, "5 - AbsReal");
			mlx_string_put(MLX, WINSETT, 20, 170, STR_C, "6 - AbsImg");
			mlx_string_put(MLX, WINSETT, 20, 195, STR_C, "7 - Power3");
			mlx_string_put(MLX, WINSETT, 20, 220, STR_C, "8 - AbsRealP4");
			mlx_string_put(MLX, WINSETT, 20, 260, STR_C, "LMB + move - transform fractal");
			mlx_string_put(MLX, WINSETT, 20, 285, STR_C, "RMB - reset transform");
			mlx_string_put(MLX, WINSETT, 20, 325, STR_C, "SMB - scale fractal to cursor");
			mlx_string_put(MLX, WINSETT, 20, 350, STR_C, "MMB - reset scale");
			mlx_string_put(MLX, WINSETT, 20, 390, STR_C, "ARROWS - shift fractal");
			mlx_string_put(MLX, WINSETT, 20, 415, STR_C, "C or <- + -> - centred fractal");
			mlx_string_put(MLX, WINSETT, 170, 440, STR_C, "(white complex axis)");
			mlx_string_put(MLX, WINSETT, 20, 480, STR_C, "~ - ON / OFF isolation mode");
			mlx_string_put(MLX, WINSETT, 20, 505, STR_C, "TAB - ON / OFF complex axis");
			mlx_string_put(MLX, WINSETT, 20, 530, STR_C, "SPACE - ON / OFF settings window");
			mlx_string_put(MLX, WINSETT, 20, 560, STR_C, "ESC - exit fractol");
			mlx_hook(sys->mlxset->win_set, 2, 0, key_press, sys);
			mlx_hook(sys->mlxset->win_set, 17, 0, close_setting, sys);
		}
		else
			mlx_destroy_window(MLX, WINSETT);
		return (0);
	}


	if (keycode == 12)
	{
		if (sys->cursor[0] >= 0 && sys->cursor[0] < (MAIN_W - MENU_W) && sys->cursor[1] >= 0 && sys->cursor[1] < MAIN_H)
		{
			scale_up(sys);
			write_scale(sys);
		}
		// scale_up(sys);
		// sys->scale[1][(int)sys->index] += ADD_SCALE;
		// def_delta(sys);
		// draw_image(sys);
		return (0);
	}

	if (keycode == 13)
	{
		if (sys->cursor[0] >= 0 && sys->cursor[0] < MAIN_W - MENU_W && sys->cursor[1] >= 0 && sys->cursor[1] < MAIN_H)
		{
			scale_down(sys);
			write_scale(sys);
		}
		// scale_down(sys);
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

	sys->cursor[0] = x;
	sys->cursor[1] = y;

	if (sys->bitset & 0b00000001)
	{
		sys->cursorcomp.real = (x - (MAIN_W - MENU_W) / 2) / (double)sys->scale[1][(int)sys->index];
		sys->cursorcomp.img = -(y - MAIN_H / 2) / (double)sys->scale[1][(int)sys->index];
		sys->k[(int)sys->index] = sys->cursorcomp;
		draw_image(sys);
		
		write_cursor(sys, 0);
		write_k(sys);
		return (0);
	}

	if (x >= 0 && x < MAIN_W - MENU_W && y >= 0 && y < MAIN_H)
	{
		// sys->cursor[0] = x;
		// sys->cursor[1] = y;

		sys->cursorcomp.real = (x - (MAIN_W - MENU_W) / 2) / (double)sys->scale[1][(int)sys->index];
		sys->cursorcomp.img = -(y - MAIN_H / 2) / (double)sys->scale[1][(int)sys->index];

		write_cursor(sys, 1);
		// draw_image(sys);
		// draw_stat(sys);
		return (0);
	}
	sys->str_cursor[0][7] = '\0';
	sys->str_cursor[0] = ft_strcat(sys->str_cursor[0], "not def");
	sys->str_cursor[1][6] = '\0';
	sys->str_cursor[1] = ft_strcat(sys->str_cursor[1], "not def");
	draw_stat(sys);

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
			sys->mlxset->mnuout[x - (MAIN_W - MENU_W) + MENU_W * y] != MENU_C)
		{
			if (sys->bitset & 0b00000100)
			{
				redraw_image(sys, x, y);
				write_color(sys);
				return (0);
			}
			sys->color = sys->mlxset->mnuout[x - (MAIN_W - MENU_W) + MENU_W * y];
			draw_image(sys);
			write_color(sys);
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

	if (button == 4 && x >= 0 && x < MAIN_W - MENU_W && y >= 0 && y < MAIN_H)
	{
		scale_down(sys);
		write_scale(sys);
		set_deltazero(sys);

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

	if (button == 5 && x >= 0 && x < MAIN_W - MENU_W && y >= 0 && y < MAIN_H)
	{
		scale_up(sys);
		write_scale(sys);
		set_deltazero(sys);

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

	// x = 0;
	// y = 0;
	sys = (t_sys *)param;

	if (button == 1 && sys->bitset & 0b00000001)
	{
		sys->bitset ^= 0b00000001;
		if (!(x >= 0 && x < MAIN_W - MENU_W && y >= 0 && y < MAIN_H))
		{
			sys->str_cursor[0][7] = '\0';
			sys->str_cursor[0] = ft_strcat(sys->str_cursor[0], "not def");
			sys->str_cursor[1][6] = '\0';
			sys->str_cursor[1] = ft_strcat(sys->str_cursor[1], "not def");
			draw_stat(sys);
		}
	}
	
	return (0);
}

void	write_cursor(t_sys *sys, char drawing)
{
	char	*pointer;
	char	i;

	double_to_str(sys->cursorcomp.real, sys->cursorstr[0]);
	pointer = sys->cursorstr[0];
	i = 7;
	while (*pointer != '\0')
	{
		sys->str_cursor[0][(int)i] = *pointer;
		pointer += 1;
		i += 1;
	}
	sys->str_cursor[0][(int)i] = '\0';
	double_to_str(sys->cursorcomp.img, sys->cursorstr[1]);
	pointer = sys->cursorstr[1];
	i = 6;
	while (*pointer != '\0')
	{
		sys->str_cursor[1][(int)i] = *pointer;
		pointer += 1;
		i += 1;
	}
	sys->str_cursor[1][(int)i] = '\0';
	if (drawing)
		draw_stat(sys);
}


void	write_k(t_sys *sys)
{
	char	*pointer;
	char	i;

	pointer = sys->cursorstr[0];
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
	pointer = sys->cursorstr[1];
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
	char	*pointer;
	char	i;

	double_to_str(sys->scale[1][(int)sys->index] / (double)DEF_SCALE, sys->scalestr);
	pointer = sys->scalestr;
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

void	write_color(t_sys *sys)
{
	int		dec;
	char	i;

	dec = sys->color;
	i = 20;
	while (dec)
	{
		sys->str_color[(int)i] = sys->hexnumbs[dec % 16];
		dec /= 16;
		i -= 1;
	}
	while (i != 14)
	{
		sys->str_color[(int)i] = '0';
		i -= 1;
	}
	draw_stat(sys);
}






















