__kernel	void test(__global int *buffer, int num1, int num2, int flag)
{
	int 	i;

	i = get_global_id(0);
	buffer[i] = num1;
}

__kernel	void Mandelbrot(__global int *buffer, int img_c, int img_w, int img_cx, int delta_x, int delta_y, int scale, int iter, double k_real, double k_img, int color, char bitset)
{

	// int 	i;
	// double		clr[2];

	// clr[0] =0;
	// clr[1] = 0xFF0000;

	// i = get_global_id(0);
	// if (i % 2)
	// 	buffer[i] = (int)clr[0];
	// else
	// 	buffer[i] = (int)clr[1];


	int		i;
	int		id;
	// t_comp	z;
	// t_comp	c;
	int		itr;
	int		i2d[2];
	double	z[2];
	double	c[2];
	double	tmp[2];

	bool	isol_mode;

	isol_mode = bitset & 0b100 ? 1 : 0;


	id = get_global_id(0);
	// z = int_to_comp(sys, i);

	i = id - img_c;

	// conv_1d_2d(sys, i, &id2d[0]);

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


	// z = init_comp(id2d[0] / (double)sys->scale[1][F_ID],
	// -id2d[1] / (double)sys->scale[1][F_ID]);

	z[0] = i2d[0] / (double)scale;
	z[1] = -i2d[1] / (double)scale;

	// c = z;

	c[0] = z[0];
	c[1] = z[1];


	itr = 0;
	while (itr < iter)
	{
		if (itr)
			// z = add_comp(pow2_comp(z),
			// 	add_comp(c, sys->k[F_ID]));
		{
			tmp[0] = z[0];
			tmp[1] = z[1];

			z[0] = tmp[0] * tmp[0] - tmp[1] * tmp[1];
			z[1] = 2 * tmp[0] * tmp[1];


			// tmp[0] = c[0] + sys->k[F_ID].real;
			// tmp[1] = c[1] + sys->k[F_ID].img;

			// z[0] += c[0];
			// z[1] += c[1];

			z[0] += c[0] + k_real;
			z[1] += c[1] + k_img;
		}
		// if (len_comp(z) > 4)
		// 	break ;
		if (sqrt(z[0] * z[0] + z[1] * z[1]) > 4)
			break ;
		itr += 1;
	}
	// draw_fractal(itr, j, sys);
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


