/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:19:37 by student           #+#    #+#             */
/*   Updated: 2020/05/29 16:19:39 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calc_Zulia(t_sys *sys)
{
	int		i;
	t_comp	z;
	int		itr;

	i = 0;
	while (i < IMAGE_VOL)
	{
		z = int_to_comp(sys, i);
		itr = 0;
		while (itr < ITER)
		{
			if (itr)
				z = add_comp(pow2_comp(z), sys->k[F_ID]);
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_Mandelbrot(t_sys *sys)
{
	// cl_int	num1;
	// cl_int	num2;
	// cl_int	flag;
	// num1 = 0xEF42F5;
	// num2 = 0xE0F542;
	// flag = 1;
	// clSetKernelArg(sys->cl->kernel, 0, sizeof(cl_mem), (void *)&sys->cl->buffer);
	// clSetKernelArg(sys->cl->kernel, 1, sizeof(cl_int), (void *)&sys->color);
	// clSetKernelArg(sys->cl->kernel, 2, sizeof(cl_int), (void *)&num2);
	// clSetKernelArg(sys->cl->kernel, 3, sizeof(cl_int), (void *)&flag);

	// // clEnqueueWriteBuffer(sys->cl->queue, sys->cl->buffer, CL_TRUE, 0, sizeof(int) * IMAGE_VOL, NULL, 0, 0, 0);

	// clEnqueueNDRangeKernel(sys->cl->queue, sys->cl->kernel, 1, NULL, &sys->cl->kernelrange, NULL, 0, NULL, NULL);
	
	// // cl->dev_info->ret = clEnqueueReadBuffer(cl->context->command_queue,\
	// // 		cl->items->c_mem_obj, //Change this to the actual object which will host the result of a calculation
	// // 		CL_TRUE, 0,NDRANGE * sizeof(int), //Change type to the desired type
	// // 		res, 0, NULL, NULL);


	// clEnqueueReadBuffer(sys->cl->queue, sys->cl->buffer, CL_TRUE, 0, sizeof(int) * IMAGE_VOL, sys->mlxset->imgout, 0, NULL, NULL);




	// clSetKernelArg(sys->cl->kernel, 0, sizeof(cl_mem), (void *)&sys->cl->buffer);
	// clSetKernelArg(sys->cl->kernel, 1, sizeof(int), (void *)&IMAGE_CENTER);
	// clSetKernelArg(sys->cl->kernel, 2, sizeof(int), (void *)&IMAGE_W);
	// clSetKernelArg(sys->cl->kernel, 3, sizeof(int), (void *)&IMAGE_CENTRX);
	// clSetKernelArg(sys->cl->kernel, 4, sizeof(int), (void *)&sys->delta[1][F_ID][0]);
	// clSetKernelArg(sys->cl->kernel, 5, sizeof(int), (void *)&sys->delta[1][F_ID][1]);
	// clSetKernelArg(sys->cl->kernel, 6, sizeof(int), (void *)&sys->scale[1][F_ID]);
	// clSetKernelArg(sys->cl->kernel, 7, sizeof(int), (void *)&ITER);
	// clSetKernelArg(sys->cl->kernel, 8, sizeof(double), (void *)&sys->k[F_ID].real);
	// clSetKernelArg(sys->cl->kernel, 9, sizeof(double), (void *)&sys->k[F_ID].img);
	// clSetKernelArg(sys->cl->kernel, 10, sizeof(int), (void *)&sys->color);
	// clSetKernelArg(sys->cl->kernel, 11, sizeof(char), (void *)&sys->bitset);

	// clEnqueueNDRangeKernel(sys->cl->queue, sys->cl->kernel, 1, NULL, &sys->cl->kernelrange, NULL, 0, NULL, NULL);
	// clEnqueueReadBuffer(sys->cl->queue, sys->cl->buffer, CL_TRUE, 0, sizeof(int) * IMAGE_VOL, sys->mlxset->imgout, 0, NULL, NULL);



	int		i;
	t_comp	z;
	t_comp	c;
	int		itr;

	i = 0;
	while (i < IMAGE_VOL)
	{
		z = int_to_comp(sys, i);
		c = z;
		itr = 0;
		while (itr < ITER)
		{
			if (itr)
				z = add_comp(pow2_comp(z),
					add_comp(c, sys->k[F_ID]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_BurningShip(t_sys *sys)
{
	int		i;
	t_comp	z;
	t_comp	c;
	int		itr;

	i = 0;
	while (i < IMAGE_VOL)
	{
		z = int_to_comp(sys, i);
		c = z;
		itr = 0;
		while (itr < ITER)
		{
			z = add_comp(pow2_comp(abs_comp(z)),
				add_comp(c, sys->k[F_ID]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_Mandelbar(t_sys *sys)
{
	int		i;
	t_comp	z;
	t_comp	c;
	int		itr;
	t_comp	tmp_z;

	i = 0;
	while (i < IMAGE_VOL)
	{
		z = int_to_comp(sys, i);
		c = z;
		itr = 0;
		while (itr < ITER)
		{
			tmp_z.real = z.real * z.real - z.img * z.img;
			tmp_z.img = z.real * z.img * -2;
			z = add_comp(tmp_z, add_comp(c, sys->k[F_ID]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}
