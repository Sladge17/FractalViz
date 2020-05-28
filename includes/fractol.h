/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 13:41:23 by student           #+#    #+#             */
/*   Updated: 2020/05/27 13:41:26 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdarg.h>
# include <wchar.h>

# include "settings.h"

typedef struct		s_sys
{
	void			*mlx;
	void			*win;

	int				imgvol;
	void			*img;
	int				img_s[3];
	int				*imgout;

	int				mnuvol;
	void			*mnu;
	int				mnu_s[3];
	int				*mnuout;

	
	// int				*back_buf;
	// int				*z_buf;
	// char			render;
	// char			control;
	// int				mouse_pos[2];
}					t_sys;


/*
** fractol.c
*/
void	set_system(t_sys *sys);
void	fill_screen(t_sys *sys);
int		close_fractol(void *param);

/*
** controls_main.c
*/
int		key_press(int keycode, void *param);

#endif

























