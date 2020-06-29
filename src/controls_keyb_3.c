/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyb_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 09:11:03 by student           #+#    #+#             */
/*   Updated: 2020/06/29 09:11:06 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	isolation_mode(int keycode, t_sys *sys)
{
	if (keycode != 50)
		return (0);
	sys->bitset ^= 0b00000100;
	draw_image(sys);
	draw_stat(sys);
	return (1);
}

char	complex_axis(int keycode, t_sys *sys)
{
	if (keycode != 48)
		return (0);
	sys->bitset ^= 0b00001000;
	if (sys->bitset & 0b00001000)
		draw_axis(sys);
	else
		draw_image(sys);
	draw_stat(sys);
	return (1);
}

char	open_winsett(int keycode, t_sys *sys)
{
	if (keycode != 49)
		return (0);
	sys->bitset ^= 0b00000010;
	if (sys->bitset & 0b00000010)
	{
		WINSETT = mlx_new_window(MLX, SETT_W, SETT_H, "settings");
		mlx_put_image_to_window(MLX, WINSETT, SETT, 0, 0);
		write_settings(sys);
		mlx_hook(sys->mlxset->win_sett, 2, 0, key_press, sys);
		mlx_hook(sys->mlxset->win_sett, 17, 0, close_setting, sys);
	}
	else
		mlx_destroy_window(MLX, WINSETT);
	return (1);
}

void	write_settings(t_sys *sys)
{
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
}
