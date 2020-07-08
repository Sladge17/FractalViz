
typedef struct	s_comp
{
	double		real;
	double		img;
}				t_comp;


__kernel void	Zulia(__global int *buffer,
						int IMAGE_CENTER,
						int IMAGE_W,
						int IMAGE_CENTRX,
						int delta_x,
						int delta_y,
						int scale,
						int iter,
						double k_real,
						double k_img,
						int color,
						char bitset)
{
	bool	isol_mode;
	int		id;
	int		i;
	int		itr;
	int		i2d[2];
	t_comp	z;
	t_comp	tmp;

	isol_mode = bitset & 0b100 ? 1 : 0;

	id = get_global_id(0);
	i = id - IMAGE_CENTER;
	i2d[0] = i % IMAGE_W;
	i2d[1] = i / IMAGE_W;
	if (i < 0 && -i2d[0] > IMAGE_CENTRX)
	{
		i2d[0] += delta_x + IMAGE_W;
		i2d[1] += delta_y - 1;
	}
	else if (i > 0 && i2d[0] >= IMAGE_CENTRX)
	{
		i2d[0] += delta_x - IMAGE_W;
		i2d[1] += delta_y + 1;
	}
	else
	{
		i2d[0] += delta_x;
		i2d[1] += delta_y;
	}

	z.real = i2d[0] / (double)scale;
	z.img = -i2d[1] / (double)scale;
	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			tmp = z;
			z.real = tmp.real * tmp.real - tmp.img * tmp.img;
			z.img = 2 * tmp.real * tmp.img;
			z.real += k_real;
			z.img += k_img;
		}
		if (sqrt(z.real * z.real + z.img * z.img) > 4)
			break ;
		itr += 1;
	}
	if (itr == iter)
	{
		buffer[id] = color;
		return ;
	}
	if (!isol_mode)
	{
		buffer[id] = itr * 1000;
		return ;
	}
	buffer[id] = 0;
}

__kernel void	Mandelbrot(__global int *buffer,
							int IMAGE_CENTER,
							int IMAGE_W,
							int IMAGE_CENTRX,
							int delta_x,
							int delta_y,
							int scale,
							int iter,
							double k_real,
							double k_img,
							int color,
							char bitset)
{
	bool	isol_mode;
	int		id;
	int		i;
	int		itr;
	int		i2d[2];
	t_comp	z;
	t_comp	c;
	t_comp	tmp;

	isol_mode = bitset & 0b100 ? 1 : 0;

	id = get_global_id(0);
	i = id - IMAGE_CENTER;
	i2d[0] = i % IMAGE_W;
	i2d[1] = i / IMAGE_W;

	if (i < 0 && -i2d[0] > IMAGE_CENTRX)
	{
		i2d[0] += delta_x + IMAGE_W;
		i2d[1] += delta_y - 1;
	}
	else if (i > 0 && i2d[0] >= IMAGE_CENTRX)
	{
		i2d[0] += delta_x - IMAGE_W;
		i2d[1] += delta_y + 1;
	}
	else
	{
		i2d[0] += delta_x;
		i2d[1] += delta_y;
	}

	z.real = i2d[0] / (double)scale;
	z.img = -i2d[1] / (double)scale;
	c = z;
	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			tmp = z;
			z.real = tmp.real * tmp.real - tmp.img * tmp.img;
			z.img = 2 * tmp.real * tmp.img;
			z.real += c.real + k_real;
			z.img += c.img + k_img;
		}
		if (sqrt(z.real * z.real + z.img * z.img) > 4)
			break ;
		itr += 1;
	}
	if (itr == iter)
	{
		buffer[id] = color;
		return ;
	}
	if (!isol_mode)
	{
		buffer[id] = itr * 1000;
		return ;
	}
	buffer[id] = 0;
}

__kernel void	BurningShip(__global int *buffer,
							int IMAGE_CENTER,
							int IMAGE_W,
							int IMAGE_CENTRX,
							int delta_x,
							int delta_y,
							int scale,
							int iter,
							double k_real,
							double k_img,
							int color,
							char bitset)
{
	bool	isol_mode;
	int		id;
	int		i;
	int		itr;
	int		i2d[2];
	t_comp	z;
	t_comp	c;
	t_comp	tmp;

	isol_mode = bitset & 0b100 ? 1 : 0;

	id = get_global_id(0);
	i = id - IMAGE_CENTER;
	i2d[0] = i % IMAGE_W;
	i2d[1] = i / IMAGE_W;

	if (i < 0 && -i2d[0] > IMAGE_CENTRX)
	{
		i2d[0] += delta_x + IMAGE_W;
		i2d[1] += delta_y - 1;
	}
	else if (i > 0 && i2d[0] >= IMAGE_CENTRX)
	{
		i2d[0] += delta_x - IMAGE_W;
		i2d[1] += delta_y + 1;
	}
	else
	{
		i2d[0] += delta_x;
		i2d[1] += delta_y;
	}

	z.real = i2d[0] / (double)scale;
	z.img = -i2d[1] / (double)scale;
	c = z;
	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			z.real = z.real < 0 ? -z.real : z.real;
			z.img = z.img < 0 ? -z.img : z.img;
			tmp = z;
			z.real = tmp.real * tmp.real - tmp.img * tmp.img;
			z.img = 2 * tmp.real * tmp.img;
			z.real += c.real + k_real;
			z.img += c.img + k_img;
		}
		if (sqrt(z.real * z.real + z.img * z.img) > 4)
			break ;
		itr += 1;
	}
	if (itr == iter)
	{
		buffer[id] = color;
		return ;
	}
	if (!isol_mode)
	{
		buffer[id] = itr * 1000;
		return ;
	}
	buffer[id] = 0;
}

__kernel void	Mandelbar(__global int *buffer,
							int IMAGE_CENTER,
							int IMAGE_W,
							int IMAGE_CENTRX,
							int delta_x,
							int delta_y,
							int scale,
							int iter,
							double k_real,
							double k_img,
							int color,
							char bitset)
{
	bool	isol_mode;
	int		id;
	int		i;
	int		itr;
	int		i2d[2];
	t_comp	z;
	t_comp	c;
	t_comp	tmp;

	isol_mode = bitset & 0b100 ? 1 : 0;

	id = get_global_id(0);
	i = id - IMAGE_CENTER;
	i2d[0] = i % IMAGE_W;
	i2d[1] = i / IMAGE_W;

	if (i < 0 && -i2d[0] > IMAGE_CENTRX)
	{
		i2d[0] += delta_x + IMAGE_W;
		i2d[1] += delta_y - 1;
	}
	else if (i > 0 && i2d[0] >= IMAGE_CENTRX)
	{
		i2d[0] += delta_x - IMAGE_W;
		i2d[1] += delta_y + 1;
	}
	else
	{
		i2d[0] += delta_x;
		i2d[1] += delta_y;
	}

	z.real = i2d[0] / (double)scale;
	z.img = -i2d[1] / (double)scale;
	c = z;
	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			tmp.real = z.real * z.real - z.img * z.img;
			tmp.img = z.real * z.img * -2;
			z.real = tmp.real + c.real + k_real;
			z.img = tmp.img + c.img + k_img;
		}
		if (sqrt(z.real * z.real + z.img * z.img) > 4)
			break ;
		itr += 1;
	}
	if (itr == iter)
	{
		buffer[id] = color;
		return ;
	}
	if (!isol_mode)
	{
		buffer[id] = itr * 1000;
		return ;
	}
	buffer[id] = 0;
}

__kernel void	AbsReal(__global int *buffer,
						int IMAGE_CENTER,
						int IMAGE_W,
						int IMAGE_CENTRX,
						int delta_x,
						int delta_y,
						int scale,
						int iter,
						double k_real,
						double k_img,
						int color,
						char bitset)
{
	bool	isol_mode;
	int		id;
	int		i;
	int		itr;
	int		i2d[2];
	t_comp	z;
	t_comp	c;
	t_comp	tmp;

	isol_mode = bitset & 0b100 ? 1 : 0;

	id = get_global_id(0);
	i = id - IMAGE_CENTER;
	i2d[0] = i % IMAGE_W;
	i2d[1] = i / IMAGE_W;

	if (i < 0 && -i2d[0] > IMAGE_CENTRX)
	{
		i2d[0] += delta_x + IMAGE_W;
		i2d[1] += delta_y - 1;
	}
	else if (i > 0 && i2d[0] >= IMAGE_CENTRX)
	{
		i2d[0] += delta_x - IMAGE_W;
		i2d[1] += delta_y + 1;
	}
	else
	{
		i2d[0] += delta_x;
		i2d[1] += delta_y;
	}

	z.real = i2d[0] / (double)scale;
	z.img = -i2d[1] / (double)scale;
	c = z;
	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			z.real = z.real < 0 ? -z.real : z.real;
			tmp = z;
			z.real = tmp.real * tmp.real - tmp.img * tmp.img;
			z.img = 2 * tmp.real * tmp.img;
			z.real += c.real + k_real;
			z.img += c.img + k_img;
		}
		if (sqrt(z.real * z.real + z.img * z.img) > 4)
			break ;
		itr += 1;
	}
	if (itr == iter)
	{
		buffer[id] = color;
		return ;
	}
	if (!isol_mode)
	{
		buffer[id] = itr * 1000;
		return ;
	}
	buffer[id] = 0;
}

__kernel void	AbsImg(__global int *buffer,
						int IMAGE_CENTER,
						int IMAGE_W,
						int IMAGE_CENTRX,
						int delta_x,
						int delta_y,
						int scale,
						int iter,
						double k_real,
						double k_img,
						int color,
						char bitset)
{
	bool	isol_mode;
	int		id;
	int		i;
	int		itr;
	int		i2d[2];
	t_comp	z;
	t_comp	c;
	t_comp	tmp;

	isol_mode = bitset & 0b100 ? 1 : 0;

	id = get_global_id(0);
	i = id - IMAGE_CENTER;
	i2d[0] = i % IMAGE_W;
	i2d[1] = i / IMAGE_W;

	if (i < 0 && -i2d[0] > IMAGE_CENTRX)
	{
		i2d[0] += delta_x + IMAGE_W;
		i2d[1] += delta_y - 1;
	}
	else if (i > 0 && i2d[0] >= IMAGE_CENTRX)
	{
		i2d[0] += delta_x - IMAGE_W;
		i2d[1] += delta_y + 1;
	}
	else
	{
		i2d[0] += delta_x;
		i2d[1] += delta_y;
	}

	z.real = i2d[0] / (double)scale;
	z.img = -i2d[1] / (double)scale;
	c = z;
	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			z.img = z.img < 0 ? -z.img : z.img;
			tmp = z;
			z.real = tmp.real * tmp.real - tmp.img * tmp.img;
			z.img = 2 * tmp.real * tmp.img;
			z.real += c.real + k_real;
			z.img += c.img + k_img;
		}
		if (sqrt(z.real * z.real + z.img * z.img) > 4)
			break ;
		itr += 1;
	}
	if (itr == iter)
	{
		buffer[id] = color;
		return ;
	}
	if (!isol_mode)
	{
		buffer[id] = itr * 1000;
		return ;
	}
	buffer[id] = 0;
}

__kernel void	Power3(__global int *buffer,
						int IMAGE_CENTER,
						int IMAGE_W,
						int IMAGE_CENTRX,
						int delta_x,
						int delta_y,
						int scale,
						int iter,
						double k_real,
						double k_img,
						int color,
						char bitset)
{
	bool	isol_mode;
	int		id;
	int		i;
	int		itr;
	int		i2d[2];
	t_comp	z;
	t_comp	tmp[2];

	isol_mode = bitset & 0b100 ? 1 : 0;

	id = get_global_id(0);
	i = id - IMAGE_CENTER;
	i2d[0] = i % IMAGE_W;
	i2d[1] = i / IMAGE_W;
	if (i < 0 && -i2d[0] > IMAGE_CENTRX)
	{
		i2d[0] += delta_x + IMAGE_W;
		i2d[1] += delta_y - 1;
	}
	else if (i > 0 && i2d[0] >= IMAGE_CENTRX)
	{
		i2d[0] += delta_x - IMAGE_W;
		i2d[1] += delta_y + 1;
	}
	else
	{
		i2d[0] += delta_x;
		i2d[1] += delta_y;
	}

	z.real = i2d[0] / (double)scale;
	z.img = -i2d[1] / (double)scale;
	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			tmp[0] = z;
			z.real = tmp[0].real * tmp[0].real - tmp[0].img * tmp[0].img;
			z.img = 2 * tmp[0].real * tmp[0].img;
			tmp[1] = z;
			z.real = tmp[0].real * tmp[1].real - tmp[0].img * tmp[1].img;
			z.img = tmp[0].real * tmp[1].img + tmp[1].real * tmp[0].img;
			z.real += k_real;
			z.img += k_img;
		}
		if (sqrt(z.real * z.real + z.img * z.img) > 4)
			break ;
		itr += 1;
	}
	if (itr == iter)
	{
		buffer[id] = color;
		return ;
	}
	if (!isol_mode)
	{
		buffer[id] = itr * 1000;
		return ;
	}
	buffer[id] = 0;
}

__kernel void	AbsRealP4(__global int *buffer,
							int IMAGE_CENTER,
							int IMAGE_W,
							int IMAGE_CENTRX,
							int delta_x,
							int delta_y,
							int scale,
							int iter,
							double k_real,
							double k_img,
							int color,
							char bitset)
{
	bool	isol_mode;
	int		id;
	int		i;
	int		itr;
	int		i2d[2];
	t_comp	z;
	t_comp	c;
	t_comp	tmp;

	isol_mode = bitset & 0b100 ? 1 : 0;

	id = get_global_id(0);
	i = id - IMAGE_CENTER;
	i2d[0] = i % IMAGE_W;
	i2d[1] = i / IMAGE_W;

	if (i < 0 && -i2d[0] > IMAGE_CENTRX)
	{
		i2d[0] += delta_x + IMAGE_W;
		i2d[1] += delta_y - 1;
	}
	else if (i > 0 && i2d[0] >= IMAGE_CENTRX)
	{
		i2d[0] += delta_x - IMAGE_W;
		i2d[1] += delta_y + 1;
	}
	else
	{
		i2d[0] += delta_x;
		i2d[1] += delta_y;
	}

	z.real = i2d[0] / (double)scale;
	z.img = -i2d[1] / (double)scale;
	c = z;
	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			z.real = z.real < 0 ? -z.real : z.real;
			tmp = z;
			z.real = tmp.real * tmp.real - tmp.img * tmp.img;
			z.img = 2 * tmp.real * tmp.img;
			tmp = z;
			z.real = tmp.real * tmp.real - tmp.img * tmp.img;
			z.img = 2 * tmp.real * tmp.img;
			z.real += c.real + k_real;
			z.img += c.img + k_img;

		}
		if (sqrt(z.real * z.real + z.img * z.img) > 4)
			break ;
		itr += 1;
	}
	if (itr == iter)
	{
		buffer[id] = color;
		return ;
	}
	if (!isol_mode)
	{
		buffer[id] = itr * 1000;
		return ;
	}
	buffer[id] = 0;
};
