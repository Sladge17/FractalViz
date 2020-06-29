/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 10:45:36 by student           #+#    #+#             */
/*   Updated: 2020/06/29 10:45:39 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	click_lmb(t_sys *sys, int button, int x, int y)
{
	if (button != 1)
		return (0);
	if (x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H)
	{
		sys->k[F_ID] = sys->cursorcomp;
		sys->bitset ^= 0b00000001;
		draw_image(sys);
		write_k(sys);
		return (1);
	}
	if (x >= IMAGE_W && y >= sys->rgbtris_y[0] && y <= sys->rgbtris_y[1]
		&& sys->mlxset->mnuout[x - IMAGE_W + MENU_W * y] != MENU_C)
	{
		if (sys->bitset & 0b00000100)
		{
			redraw_image(sys, x, y);
			write_color(sys);
			return (1);
		}
		sys->color = sys->mlxset->mnuout[x - IMAGE_W + MENU_W * y];
		draw_image(sys);
		write_color(sys);
	}
	return (1);
}

char	click_rmb(t_sys *sys, int button, int x, int y)
{
	if (button != 2)
		return (0);
	if (!(x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H)
		|| (sys->k[F_ID].real == 0 && sys->k[F_ID].img == 0))
		return (1);
	sys->k[F_ID].real = 0;
	sys->k[F_ID].img = 0;
	draw_image(sys);
	sys->str_k[F_ID][4] = '\0';
	sys->str_k[F_ID] = ft_strcat(sys->str_k[F_ID], "0.000 + 0.000i");
	draw_stat(sys);
	return (1);
}

char	click_mmb(t_sys *sys, int button, int x, int y)
{
	if (button != 3 && button != 4 && button != 5)
		return (0);
	if (!(x >= 0 && x < IMAGE_W && y >= 0 && y < MAIN_H))
		return (1);
	if (button == 4)
	{
		scale_down(sys);
		write_scale(sys);
		set_deltazero(sys);
		return (1);
	}
	if (button == 5)
	{
		scale_up(sys);
		write_scale(sys);
		set_deltazero(sys);
		return (1);		
	}
	scale_reset(sys);
	return (1);	
}

void	cursor_outside(t_sys *sys)
{
	sys->str_cursor[0][7] = '\0';
	sys->str_cursor[0] = ft_strcat(sys->str_cursor[0], "not def");
	sys->str_cursor[1][6] = '\0';
	sys->str_cursor[1] = ft_strcat(sys->str_cursor[1], "not def");
	draw_stat(sys);
	sys->bitset ^= 0b100000000;
}

void	cursor_inttocomp(t_sys *sys, int x, int y)
{
	sys->cursorcomp.real = (x - IMAGE_CENTRX) / (double)sys->scale[1][F_ID];
	sys->cursorcomp.img = -(y - IMAGE_CENTRY) / (double)sys->scale[1][F_ID];
}

