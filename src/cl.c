/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:54:49 by student           #+#    #+#             */
/*   Updated: 2020/07/03 12:54:54 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_cl(t_sys *sys)
{
	if (!(sys->cl = (t_cl *)malloc(sizeof(t_cl))))
		exit(0);
	// set_kernelsrc(sys);
	clGetPlatformIDs(1, &PLATFORM, NULL);
	clGetDeviceIDs(PLATFORM, CL_DEVICE_TYPE_CPU, 1, &DEVICE, NULL);

	PROPERTIES[0] = CL_CONTEXT_PLATFORM;
	PROPERTIES[1] = (cl_context_properties)PLATFORM;
	PROPERTIES[2] = 0;

	CONTEXT = clCreateContext(PROPERTIES, 1, &DEVICE, NULL, NULL, NULL);
	QUEUE = clCreateCommandQueue(CONTEXT, DEVICE, 0, NULL);


	set_kernelprog(sys);
	// PROGRAM = clCreateProgramWithSource(CONTEXT, 1, &KERNELSRC, NULL, NULL);
	clBuildProgram(PROGRAM, 0, NULL, NULL, NULL, NULL);

	BUFFER = clCreateBuffer(CONTEXT, CL_MEM_READ_WRITE, IMG_INT, NULL, NULL);
	// KERNEL = clCreateKernel(PROGRAM, "Mandelbrot", NULL);
	// sys->cl->buffer = clCreateBuffer(sys->cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * IMAGE_VOL, sys->mlxset->imgout, NULL
	RANGE = IMAGE_VOL;
}

void	set_kernelprog(t_sys *sys)
{
	char		*path;
	int			len;
	const char	*source;
	int			fd;

	path = ft_strnew(19);
	path = ft_strcat(path, "./kernels/kernel.cl");
	len = set_lensrc(path);
	source = ft_strnew(len);
	if ((fd = open(path, O_RDONLY)) == -1)
		exit(0);
	read(fd, (void *)source, len);
	close(fd);
	PROGRAM = clCreateProgramWithSource(CONTEXT, 1, &source, NULL, NULL);
}


// void	test(char *path, char *prog)
// {
// 	int			len_src;
// 	// const char	*text_src;
// 	int			fd;

// 	len_src = set_lensrc(path);

// 	prog = ft_strnew(len_src);
// 	if ((fd = open(path, O_RDONLY)) == -1)
// 		exit(0);
// 	read(fd, (void *)prog, len_src);
// 	close(fd);
// 	// PROGRAM = clCreateProgramWithSource(CONTEXT, 1, &text_src, NULL, NULL);
// }



int		set_lensrc(char *kernelpath)
{
	int		fd;
	int		len_src;
	char	symbol;
	char	end;

	if ((fd = open(kernelpath, O_RDONLY)) == -1)
		exit(0);
	len_src = 0;
	read(fd, &symbol, 1);
	while (1)
	{
		end = symbol == '}' ? 1 : 0;
		len_src += 1;
		read(fd, &symbol, 1);
		if (end && symbol == ';')
		{
			// len_src += 1;
			break ;
		}
	}
	close(fd);
	return (len_src);
}

void	exe_kernel(t_sys *sys)
{
	clSetKernelArg(KERNEL, 0, sizeof(cl_mem), (void *)&sys->cl->buffer);
	clSetKernelArg(KERNEL, 1, sizeof(int), (void *)&IMAGE_CENTER);
	clSetKernelArg(KERNEL, 2, sizeof(int), (void *)&IMAGE_W);
	clSetKernelArg(KERNEL, 3, sizeof(int), (void *)&IMAGE_CENTRX);
	clSetKernelArg(KERNEL, 4, sizeof(int), (void *)&sys->delta[1][F_ID][0]);
	clSetKernelArg(KERNEL, 5, sizeof(int), (void *)&sys->delta[1][F_ID][1]);
	clSetKernelArg(KERNEL, 6, sizeof(int), (void *)&sys->scale[1][F_ID]);
	clSetKernelArg(KERNEL, 7, sizeof(int), (void *)&ITER);
	clSetKernelArg(KERNEL, 8, sizeof(double), (void *)&sys->k[F_ID].real);
	clSetKernelArg(KERNEL, 9, sizeof(double), (void *)&sys->k[F_ID].img);
	clSetKernelArg(KERNEL, 10, sizeof(int), (void *)&sys->color);
	clSetKernelArg(KERNEL, 11, sizeof(char), (void *)&sys->bitset);

	clEnqueueNDRangeKernel(QUEUE, KERNEL, 1, NULL, &RANGE, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(QUEUE, BUFFER, CL_TRUE, 0, IMG_INT, sys->mlxset->imgout, 0, NULL, NULL);


}








