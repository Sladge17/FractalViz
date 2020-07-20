/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 12:11:58 by student           #+#    #+#             */
/*   Updated: 2020/06/29 12:12:01 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calc_fractal(t_sys *sys)
{
	if (sys->bitset & 0b1000000000)
	{
		exe_kernel(sys);
		return ;
	}
	if (sys->index == 0)
	{
		calc_zulia(sys);
		return ;
	}
	if (sys->index == 1)
	{
		calc_mandelbrot(sys);
		return ;
	}
	if (sys->index == 2)
	{
		calc_burningship(sys);
		return ;
	}
	calc_fractal_nest(sys);
}

void	calc_fractal_nest(t_sys *sys)
{
	if (sys->index == 3)
	{
		calc_mandelbar(sys);
		return ;
	}
	if (sys->index == 4)
	{
		calc_absreal(sys);
		return ;
	}
	if (sys->index == 5)
	{
		calc_absimg(sys);
		return ;
	}
	if (sys->index == 6)
	{
		calc_power3(sys);
		return ;
	}
	calc_absrealp4(sys);
}

t_comp	int_to_comp(t_sys *sys, int id)
{
	t_comp	complex;
	int		id2d[2];

	id -= IMAGE_CENTER;
	conv_1d_2d(sys, id, &id2d[0]);
	complex = init_comp(id2d[0] / (double)sys->scale[1][F_ID],
		-id2d[1] / (double)sys->scale[1][F_ID]);
	return (complex);
}

void	conv_1d_2d(t_sys *sys, int id, int *id2d)
{
	id2d[0] = id % IMAGE_W;
	id2d[1] = id / IMAGE_W;
	if (id < 0 && -id2d[0] > IMAGE_CENTRX)
	{
		id2d[0] += sys->delta[1][F_ID][0] + IMAGE_W;
		id2d[1] += sys->delta[1][F_ID][1] - 1;
		return ;
	}
	if (id > 0 && id2d[0] >= IMAGE_CENTRX)
	{
		id2d[0] += sys->delta[1][F_ID][0] - IMAGE_W;
		id2d[1] += sys->delta[1][F_ID][1] + 1;
		return ;
	}
	id2d[0] += sys->delta[1][F_ID][0];
	id2d[1] += sys->delta[1][F_ID][1];
}

void	draw_fractal(int itr, int i, t_sys *sys)
{
	if (itr == ITER)
	{
		sys->mlxset->imgout[i] = sys->color;
		return ;
	}
	if (!(sys->bitset & 0b00000100))
	{
		sys->mlxset->imgout[i] = itr * 1000;
		return ;
	}
	sys->mlxset->imgout[i] = 0;
}
