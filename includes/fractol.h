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

# include "constants.h"
# include "structs.h"
# include "forbidden.h"


/*
** fractol.c
*/
void	fractol_discr();
void	set_deltazero(t_sys *sys);
void	def_delta(t_sys *sys);


/*
** set_system.c
*/
void	set_system(t_sys *sys);
void	set_consts(t_sys *sys);
void	set_mlxset(t_sys *sys);
void	set_tabparam(t_sys *sys);
char	*set_fractname(t_sys *sys);

/*
** calc_fractal.c
*/
void	calc_fractal(t_sys	*sys);
void	calc_fractal_nest(t_sys *sys);
t_comp	int_to_comp(t_sys *sys, int id);
void	conv_1d_2d(t_sys *sys, int id, int *id2d);
void	draw_fractal(int itr, int i, t_sys *sys);

/*
** rgb_triangle.c
*/
void	draw_rgbtriangle(t_sys *sys, int x0, int offset_x);
void	fill_triangle(t_sys *sys, int *tris, int height, int widthhalf);
void	def_rgbset(char *rgb_set, int color0, int color1);
int		set_color(char *rgb_set, int color0, double int_xc);
void	draw_horline(t_sys *system, int *v0, int *v1);

/*
** clearing.c
*/
void	clear_image(t_sys *sys);
void	clear_stat(t_sys *sys);
void	clear_settings(t_sys *sys);
int		close_setting(void *param);
int		close_fractol(void *param);

/*
** drawing.c
*/
void	draw_winmain(t_sys *sys, int argc, char *argv);
void	draw_image(t_sys *sys);
void	draw_menu(t_sys *sys);
void	draw_stat(t_sys *sys);
void	redraw_image(t_sys *sys, int x, int y);

/*
** complex_axis.c
*/
void	draw_axis(t_sys *sys);
void	draw_realstroks(t_sys *sys, int *startcrd, int *numbpxl, int *k);
void	draw_imgstroks(t_sys *sys, int *startcrd, int *numbpxl, int *k);
void	draw_axtitle(t_sys *sys);

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
int		key_release(int keycode, void *param);
int		mouse_press(int button, int x, int y, void *param);
int		mouse_release(int button, int x, int y, void *param);
int		mouse_move(int x, int y, void *param);

/*
** controls_keyb_1.c
*/
char	change_fractal(int keycode, t_sys *sys);
char	select_fractal_1(int keycode, t_sys *sys);
char	select_fractal_2(int keycode, t_sys *sys);
char	select_fractal_3(int keycode, t_sys *sys);
char	select_fractal_4(int keycode, t_sys *sys);

/*
** controls_keyb_2.c
*/
char	shift_fractal_k(int keycode, t_sys *sys);
char	check_shiftfractal(int keycode, t_sys *sys);
char	check_unshiftfractal(int keycode, t_sys *sys);
char	scale_fractal_k(int keycode, t_sys *sys);

/*
** controls_keyb_3.c
*/
char	isolation_mode(int keycode, t_sys *sys);
char	complex_axis(int keycode, t_sys *sys);
char	open_winsett(int keycode, t_sys *sys);
void	write_settings(t_sys *sys);

/*
** controls_mouse.c
*/
char	click_lmb(t_sys *sys, int button, int x, int y);
char	click_rmb(t_sys *sys, int button, int x, int y);
char	click_mmb(t_sys *sys, int button, int x, int y);
void	cursor_outside(t_sys *sys);
void	cursor_inttocomp(t_sys *sys, int x, int y);

/*
** shift_fractal.c
*/
void	shift_fractal(t_sys *sys);
char	shift_ortho(t_sys *sys, unsigned char shift);
char	shift_diagonal(t_sys *sys, unsigned char shift);
void	shifting_fractal(t_sys *sys, char shift_x, char shift_y);
void	shift_reset(t_sys *sys);

/*
** scale_fractal.c
*/
void	scale_up(t_sys *sys);
void	scale_down(t_sys *sys);
void	scale_reset(t_sys *sys);

/*
** write_stats.c
*/
void	write_cursor(t_sys *sys, char drawing);
void	write_k(t_sys *sys);
void	write_scale(t_sys *sys);
void	write_color(t_sys *sys);

/*
** double_to_str.c
*/
void	double_to_str(double input, char *str);
int		intlen(int integer);
void	write_intpart(char *str, int integer, int i, char sign);
void	write_fractpart(char *str, int fraction, int i);

/*
** NEED_DELL.c
*/
size_t	ft_strlen(const char *str);
char	*ft_strcat(char *dst, const char *src);
void	ft_bzero(void *dest, size_t count);
char	*ft_strnew(size_t size);
int		ft_atoi(const char *str);

#endif

