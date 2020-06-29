/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 12:50:06 by student           #+#    #+#             */
/*   Updated: 2020/06/29 12:50:09 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clear_image(t_sys *sys)
{
	int		i;
	
	i = 0;
	while (i < IMAGE_VOL)
	{
		sys->mlxset->imgout[i] = IMAGE_C;
		i += 1;
	}
}

void	clear_stat(t_sys *sys)
{
	int		i;
	
	i = 0;
	while (i < STAT_VOL)
	{
		sys->mlxset->statout[i] = 0;
		i += 1;
	}
}

void	clear_settings(t_sys *sys)
{
	int		i;

	i = 0;
	while (i < SETT_VOL)
	{
		sys->mlxset->settout[i] = MENU_C;
		i += 1;
	}
}

int		close_setting(void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;
	sys->bitset ^= 0b00000010;
	return (0);
}

int		close_fractol(void *param)
{
	(void)param;
	exit(0);
}
