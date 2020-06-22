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

typedef struct	s_comp
{
	double		real;
	double		img;
}				t_comp;

typedef struct	s_sys
{
	void		*mlx;
	void		*win_main;
	void		*win_set;

	int			imgvol;
	void		*img;
	int			img_s[3];
	int			*imgout;

	int			mnuvol;
	void		*mnu;
	int			mnu_s[3];
	int			*mnuout;

	int			statvol;
	void		*stat;
	int			stat_s[3];
	int			*statout;

	int			setvol;
	void		*set;
	int			set_s[3];
	int			*setout;
	
	char		bitset;

	char		index;
	char		*name;
	int			color;
	int			shift[8][2];

	int			rgbtris_y[2];

	int			cursor[2];
	t_comp		cursorcomp;
	// int			scale[8];
	// int			delta[8][2];

	// int			delta0[8][2];
	// int			scale0[8];

	int			scale[2][8];
	int			delta[2][8][2];
	

	t_comp		k[8];


}				t_sys;