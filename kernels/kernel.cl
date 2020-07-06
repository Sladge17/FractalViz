__kernel	void test(__global int *buffer, int num1, int num2, int flag)
{
	int 	i;

	i = get_global_id(0);
	buffer[i] = num1;
}

__kernel void	Zulia(__global int *buffer,
						int img_c,
						int img_w,
						int img_cx,
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
	double	z[2];
	// double	c[2];
	double	tmp[2];

	isol_mode = bitset & 0b100 ? 1 : 0;

	id = get_global_id(0);
	i = id - img_c;
	i2d[0] = i % img_w;
	i2d[1] = i / img_w;

	if (i < 0 && -i2d[0] > img_cx)
	{
		i2d[0] += delta_x + img_w;
		i2d[1] += delta_y - 1;
	}
	else if (i > 0 && i2d[0] >= img_cx)
	{
		i2d[0] += delta_x - img_w;
		i2d[1] += delta_y + 1;
	}
	else
	{
		i2d[0] += delta_x;
		i2d[1] += delta_y;
	}

	z[0] = i2d[0] / (double)scale;
	z[1] = -i2d[1] / (double)scale;
	// c[0] = z[0];
	// c[1] = z[1];

	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			tmp[0] = z[0];
			tmp[1] = z[1];
			z[0] = tmp[0] * tmp[0] - tmp[1] * tmp[1];
			z[1] = 2 * tmp[0] * tmp[1];
			// z[0] += c[0] + k_real;
			// z[1] += c[1] + k_img;
			z[0] += k_real;
			z[1] += k_img;
		}
		if (sqrt(z[0] * z[0] + z[1] * z[1]) > 4)
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
							int img_c,
							int img_w,
							int img_cx,
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
	double	z[2];
	double	c[2];
	double	tmp[2];

	isol_mode = bitset & 0b100 ? 1 : 0;

	id = get_global_id(0);
	i = id - img_c;
	i2d[0] = i % img_w;
	i2d[1] = i / img_w;

	if (i < 0 && -i2d[0] > img_cx)
	{
		i2d[0] += delta_x + img_w;
		i2d[1] += delta_y - 1;
	}
	else if (i > 0 && i2d[0] >= img_cx)
	{
		i2d[0] += delta_x - img_w;
		i2d[1] += delta_y + 1;
	}
	else
	{
		i2d[0] += delta_x;
		i2d[1] += delta_y;
	}

	z[0] = i2d[0] / (double)scale;
	z[1] = -i2d[1] / (double)scale;
	c[0] = z[0];
	c[1] = z[1];

	itr = 0;
	while (itr < iter)
	{
		if (itr)
		{
			tmp[0] = z[0];
			tmp[1] = z[1];
			z[0] = tmp[0] * tmp[0] - tmp[1] * tmp[1];
			z[1] = 2 * tmp[0] * tmp[1];
			z[0] += c[0] + k_real;
			z[1] += c[1] + k_img;
		}
		if (sqrt(z[0] * z[0] + z[1] * z[1]) > 4)
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


