/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:24:16 by vabraham          #+#    #+#             */
/*   Updated: 2019/11/15 14:24:17 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WIDTH 900
# define HEIGHT 900
# include "mlx.h"
# include "includes/libft/get_next_line.h"
# include <math.h>
# include "stdio.h"

typedef struct s_col
{
	int			r;
	int			g;
	int			b;
}				t_col;

typedef	struct s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef enum	e_tfig
{
	sphere,
	cylinder,
	plane,
	conus
}				t_tfig;

typedef struct	s_fig
{
	t_tfig		type;
	t_vec3		pos;
	float		rad;
	t_col		col;
	int			spec;
	float		refl;
	struct	s_fig	*next;
}				t_fig;

typedef enum	e_tlght
{
	ambient,
	point,
	direct
}				t_tlght;

typedef struct	s_lght
{
	t_tlght		type;
	t_vec3		pos;
	t_vec3		dir;
	float		ints;
	struct	s_lght		*next;
}				t_lght;

typedef struct	s_scn
{
	t_fig		*figs;
	t_lght		*lghts;
}				t_scn;

typedef struct		s_lst
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*data;
	int				n0;
	int				n1;
	int				n2;
	float			l1;
	float			l2;
	float			l3;
	int				change;
	float			x;
	float			y;
	float			z;
	float			r;
	t_scn			*scn;
}					t_lst;
void	pixel(t_lst *lst);
float	color(t_lst *lst, t_vec3 *p, t_vec3 *n, t_vec3 *v, t_fig *fg);

#endif
