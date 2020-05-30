/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 16:35:15 by student           #+#    #+#             */
/*   Updated: 2020/05/27 16:35:18 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


// int		main()
// {
// 	t_comp	q;

// 	q = init_comp(2, 4);
// 	printf("%f %f\n", q.real, q.img);

// 	q = pow2_comp(q);
// 	printf("%f %f\n", q.real, q.img);

// 	q = add_comp(q, init_comp(0.2, 0));
// 	printf("%f %f\n", q.real, q.img);

// 	printf("%f\n", len_comp(q));


// 	return (0);
// }

// int		main()
// {
// 	t_comp	q;
// 	t_comp	w;

// 	q = init_comp(-2, 4);
// 	w = init_comp(3, -6);
// 	printf("%f %f\n", q.real, q.img);
// 	printf("%f %f\n", w.real, w.img);
// 	printf("\n");

// 	t_comp	sum = add_comp(q, w);
// 	t_comp	mult = mult_comp(q, w);
// 	t_comp	pow = pow2_comp(q);
// 	printf("%f %f\n", sum.real, sum.img);
// 	printf("%f %f\n", mult.real, mult.img);
// 	printf("%f %f\n", pow.real, pow.img);
// 	printf("\n");

// 	double len = len_comp(q);
// 	printf("%f\n", len);
// 	printf("\n");

// 	return (0);
// }

// 	return (0);
// }

// int		main()
// {
// 	t_comp	q;
// 	t_comp	w;

// 	q = init_comp(-2, 4);
// 	w = init_comp(3, -6);
// 	printf("%f %f\n", q.real, q.img);
// 	printf("%f %f\n", w.real, w.img);
// 	printf("\n");

// 	// printf("%lu\n", sizeof(double));

// 	topos_realimg(&q);
// 	topos_realimg(&w);
// 	printf("%f %f\n", q.real, q.img);
// 	printf("%f %f\n", w.real, w.img);


// 	return (0);
// }



int		main()
// int		main(int argc, char **argv)
{
	t_sys	*sys;

	if (!(sys = (t_sys *)malloc(sizeof(t_sys))))
		exit(0);

	set_system(sys);
	fill_screen(sys);

	// t_comp	c = init_comp(0.2, 0);

	calc_fractal(sys);

	mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
	mlx_put_image_to_window(sys->mlx, sys->win, sys->mnu, WIDTH - MENU_W, 0);

	mlx_hook(sys->win, 2, 0, key_press, sys);
	// mlx_hook(setting.sys.win, 3, 0, key_release, &setting);
	// mlx_hook(setting.sys.win, 4, 0, mouse_press, &setting);
	// mlx_hook(setting.sys.win, 5, 0, mouse_release, &setting);
	mlx_hook(sys->win, 6, 0, mouse_move, sys);
	mlx_hook(sys->win, 17, 0, close_fractol, sys);
	mlx_loop(sys->mlx);


	return (0);
}

void	set_system(t_sys *sys)
{
	sys->mlx = mlx_init();
	sys->win = mlx_new_window(sys->mlx, WIDTH, HEIGHT, "fractol");
	
	sys->imgvol = (WIDTH - MENU_W) * HEIGHT;
	sys->img = mlx_new_image(sys->mlx, WIDTH - MENU_W, HEIGHT);
	sys->imgout = (int *)mlx_get_data_addr(sys->img,
		&sys->img_s[0], &sys->img_s[1], &sys->img_s[2]);

	sys->mnuvol = MENU_W * HEIGHT;
	sys->mnu = mlx_new_image(sys->mlx, MENU_W, HEIGHT);
	sys->mnuout = (int *)mlx_get_data_addr(sys->mnu,
		&sys->mnu_s[0], &sys->mnu_s[1], &sys->mnu_s[2]);

	sys->scale = 200;
	sys->bitset = 0b10000001;
}

void	fill_screen(t_sys *sys)
{
	int		i;
	
	i = 0;
	while (i < sys->imgvol)
	{
		sys->imgout[i] = IMAGE_C;
		i += 1;
	}

	i = 0;
	while (i < sys->mnuvol)
	{
		sys->mnuout[i] = MENU_C;
		i += 1;
	}
}

int		close_fractol(void *param)
{
	(void)param;
	exit(0);
}

t_comp	int_to_comp(int id)
{
	t_comp	complex;

	complex.real = id % (WIDTH - MENU_W);
	complex.img = id / (WIDTH - MENU_W);
	complex.real -= (WIDTH - MENU_W) / 2;
	complex.img -= HEIGHT / 2;
	return (complex);
}

void	draw_fract(int itr, int i, t_sys *sys)
{
	if (itr == ITER)
	{
		sys->imgout[i] = FRACT_C;
		return ;
	}
	if (sys->bitset & 0b10000000)
		sys->imgout[i] = itr * 1000;
}

void	calc_fractal(t_sys	*sys)
{
	int		i;
	t_comp	z;

	t_comp	c = init_comp(0.2, 0);

	i = 0;
	while (i < sys->imgvol)
	{

		z = int_to_comp(i);
		scale_comp(&z, sys->scale);
		
		if (sys->bitset & 0b00000001)
			draw_fract(calc_Mandelbrot(z), i, sys);
		if (sys->bitset & 0b00000010)
			draw_fract(calc_Zulia(z, c), i, sys);
		if (sys->bitset & 0b00000100)
			draw_fract(calc_BurningShip(z), i, sys);
		if (sys->bitset & 0b00001000)
			draw_fract(calc_Mandelbar(z), i, sys);
		
		i += 1;
	}
}



































