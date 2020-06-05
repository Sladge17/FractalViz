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
# include "forbidden.h"

typedef struct	s_comp
{
	double		real;
	double		img;
}				t_comp;

typedef struct	s_sys
{
	void		*mlx;
	void		*win;

	int			imgvol;
	void		*img;
	int			img_s[3];
	int			*imgout;

	int			mnuvol;
	void		*mnu;
	int			mnu_s[3];
	int			*mnuout;

	int			scale;
	char		bitset;

	char		index;
	char		*name;
	t_comp		cursor;		
	t_comp		k[8];


}				t_sys;


/*
** fractol.c
*/
void	set_system(t_sys *sys);
void	set_k(t_sys *sys);
void	clear_screen(t_sys *sys);
int		close_fractol(void *param);
t_comp	int_to_comp(int idx);
void	calc_fractal(t_sys	*sys);
void	calc_fractal_nest(t_sys *sys);

/*
** rgb_triangle.c
*/
void	draw_rgbtriangle(t_sys *sys, int x0, int y0, int offset);
void	fill_triangle(t_sys *sys, int *tris, int height, int widthhalf);
void	def_rgbset(char *rgb_set, int color0, int color1);
int		set_color(char *rgb_set, int color0, double int_xc);
void	draw_horline(t_sys *system, int *v0, int *v1);

/*
** drawing.c
*/
void	draw_image(t_sys *sys);
void	draw_fractal(int itr, int i, t_sys *sys);
void	draw_axis(t_sys *sys);



/*
** complex_actions1.c
*/
t_comp	init_comp(double real, double img);
t_comp	add_comp(t_comp comp, t_comp comp_add);
t_comp	mult_comp(t_comp comp_1, t_comp comp_2);
t_comp	pow2_comp(t_comp comp);
t_comp	ppow_comp(t_comp comp, int power);

/*
** complex_actions2.c
*/
t_comp	abs_comp(t_comp comp);
t_comp	absreal_comp(t_comp comp);
t_comp	absimg_comp(t_comp comp);
double	len_comp(t_comp comp);
void	scale_comp(t_comp *comp, int scale);

/*
** fractals1.c
*/
void	calc_Zulia(t_sys *sys);
void	calc_Mandelbrot(t_sys *sys);
void	calc_BurningShip(t_sys *sys);
void	calc_Mandelbar(t_sys *sys);

/*
** fractals2.c
*/
void	calc_AbsReal(t_sys *sys);
void	calc_AbsImg(t_sys *sys);
void	calc_Power3(t_sys *sys);
void	calc_AbsRealP4(t_sys *sys);

/*
** controls_main.c
*/
int		key_press(int keycode, void *param);
char	change_fractal(int keycode, t_sys *sys);
int		mouse_move(int x, int y, void *param);
int		mouse_press(int button, int x, int y, void *param);
int		mouse_release(int button, int x, int y, void *param);

#endif

























