/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 17:21:07 by student           #+#    #+#             */
/*   Updated: 2020/06/06 17:21:10 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct				s_cl
{
	cl_platform_id			platform;
	cl_device_id			device;
	cl_context_properties	properties[3];
	cl_context				context;
	cl_command_queue		queue;
	cl_program				program;
	cl_kernel				kernel;
	cl_mem					buffer;
	size_t					range;
}							t_cl;

typedef struct s_consts
{
	int			iter;
	int			image_w;
	int			image_vol;
	int			menu_vol;
	int			stat_vol;
	int			sett_vol;
	int			image_centrx;
	int			image_centry;
	int			image_center;

	int			menu_xoffset;

	int			image_int;
}				t_consts;

typedef struct s_mlxset
{
	void		*mlx;
	void		*win_main;
	void		*win_sett;

	void		*img;
	int			img_s[3];
	int			*imgout;

	void		*mnu;
	int			mnu_s[3];
	int			*mnuout;

	void		*stat;
	int			stat_s[3];
	int			*statout;

	void		*sett;
	int			sett_s[3];
	int			*settout;	
}				t_mlxset;

typedef struct	s_comp
{
	double		real;
	double		img;
}				t_comp;

typedef struct	s_sys
{
	t_cl		*cl;

	t_consts	*consts;
	t_mlxset	*mlxset;

	char		index;
	short		bitset;
	int			color;
	int			cursor[2];
	t_comp		cursorcomp;

	int			rgbtris_y[2];

	int			shift[8][2];
	int			delta[2][8][2];
	int			scale[2][8];
	int			axis_c[8];
	t_comp		k[8];

	char		*str_name;
	char		*str_k[8];
	char		*cursorstr[2];
	char		*str_cursor[2];
	char		*scalestr;
	char		*str_scale[8];
	char		*hexnumbs;
	char		*str_color;
}				t_sys;
