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

int		main()
// int		main(int argc, char **argv)
{
	t_sys	sys;

	// if (!(sys = (t_sys *)malloc(sizeof(t_sys))))
	// 	exit(0);

	set_system(&sys);
	fill_screen(&sys);
	

	mlx_put_image_to_window(sys.mlx, sys.win, sys.img, 0, 0);
	mlx_put_image_to_window(sys.mlx, sys.win, sys.mnu, WIDTH - MENU_W, 0);

	mlx_hook(sys.win, 2, 0, key_press, &sys);
	// mlx_hook(setting.sys.win, 3, 0, key_release, &setting);
	// mlx_hook(setting.sys.win, 4, 0, mouse_press, &setting);
	// mlx_hook(setting.sys.win, 5, 0, mouse_release, &setting);
	// mlx_hook(setting.sys.win, 6, 0, mouse_move, &setting);
	mlx_hook(sys.win, 17, 0, close_fractol, &sys);

	mlx_loop(sys.mlx);


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









