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

typedef struct s_consts
{
	int			image_w;
	int			image_vol;
	int			menu_vol;
	int			stat_vol;
	int			sett_vol;
	int			image_centrx;
	int			image_centry;
	int			image_center;

	int			menu_xoffset;
}				t_consts;

typedef struct s_mlxset
{
	void		*mlx;
	void		*win_main;
	void		*win_set;

	void		*img;
	int			img_s[3];
	int			*imgout;

	void		*mnu;
	int			mnu_s[3];
	int			*mnuout;

	void		*stat;
	int			stat_s[3];
	int			*statout;

	void		*set;
	int			set_s[3];
	int			*setout;	
}				t_mlxset;

typedef struct	s_comp
{
	double		real;
	double		img;
}				t_comp;

typedef struct	s_sys
{
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
