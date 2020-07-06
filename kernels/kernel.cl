// __kernel	void test(__global int *buffer, int num1, int num2, int flag)
// {
// 	int 	i;

// 	i = get_global_id(0);
// 	buffer[i] = num1;
// }

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
			tmp.real = z.real;
			tmp.img = z.img;
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
	c.real = z.real;
	c.img = z.img;

	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			tmp.real = z.real;
			tmp.img = z.img;
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


