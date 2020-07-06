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
	set_kernelsrc(sys->cl);
	clGetPlatformIDs(1, &sys->cl->platform, NULL);
	clGetDeviceIDs(sys->cl->platform, CL_DEVICE_TYPE_CPU, 1, &sys->cl->device, NULL);

	sys->cl->properties[0] = CL_CONTEXT_PLATFORM;
	sys->cl->properties[1] = (cl_context_properties)sys->cl->platform;
	sys->cl->properties[2] = 0;

	sys->cl->context = clCreateContext(sys->cl->properties, 1, &sys->cl->device, NULL, NULL, NULL);
	sys->cl->queue = clCreateCommandQueue(sys->cl->context, sys->cl->device, 0, NULL);
	
	sys->cl->program = clCreateProgramWithSource(sys->cl->context, 1, &sys->cl->kernelsrc, NULL, NULL);
	clBuildProgram(sys->cl->program, 0, NULL, NULL, NULL, NULL);

	sys->cl->kernel = clCreateKernel(sys->cl->program, "Mandelbrot", NULL);
	// sys->cl->buffer = clCreateBuffer(sys->cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * IMAGE_VOL, sys->mlxset->imgout, NULL);
	sys->cl->buffer = clCreateBuffer(sys->cl->context, CL_MEM_READ_WRITE, sizeof(int) * IMAGE_VOL, NULL, NULL);

	sys->cl->kernelrange = IMAGE_VOL;
}

void	set_kernelsrc(t_cl *cl)
{
	int		fd;;
	int		len_src;
	char	*kernelpath;

	kernelpath = ft_strnew(18);
	kernelpath = ft_strcat(kernelpath, "./kernel/kernel.cl");
	len_src = set_lensrc(kernelpath);
	// if (!(cl->kernelsrc = (char *)malloc(sizeof(char) * (len_src + 1))))
	// 	exit(0);
	cl->kernelsrc = ft_strnew(len_src);
	if ((fd = open(kernelpath, O_RDONLY)) == -1)
		exit(0);
	read(fd, (void *)cl->kernelsrc, len_src);
	close(fd);
}

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

