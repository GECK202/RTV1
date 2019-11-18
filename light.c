#include "rtv1.h"

float	dot(t_vec3 *v1, t_vec3 *v2)
{
	float d;

	d = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return (d);
}

float	len_vec3(t_vec3 *v)
{
	float len;

	len = sqrt(dot(v, v));
	return (len);
}

void	refl_r(t_vec3 *r, t_vec3 *l, t_vec3 *n)
{
	float k;

	k = 2 * dot(n, l);
	r->x = k * l->x - n->x;
	r->y = k * l->y - n->y;
	r->z = k * l->z - n->z;
}

float	color(t_lst *lst, t_vec3 *p, t_vec3 *n, t_vec3 *v, t_fig *fg)
{
	float	ints;
	t_vec3	l;
	t_vec3	r;
	float	t_max;
	float	n_dot;
	float	r_dot;
	float	spec;
	t_lght	*c_lght;
	//t_intr	*shdw;

	ints = 0.0f;
	c_lght = lst->scn->lghts;
	while (c_lght)
	{
		if (c_lght->type == ambient)
			ints += c_lght->ints;
		else
		{
			if (c_lght->type == point)
			{
				l.x = c_lght->pos.x - p->x;
				l.y = c_lght->pos.y - p->y;
				l.z = c_lght->pos.z - p->z;
				t_max = 1.0f;
				// printf("%f    %f     %f\n", l.x, l.y, l.z);
			}
			else if (c_lght->type == direct)
			{
				l.x = c_lght->dir.x;
				l.y = c_lght->dir.y;
				l.z = c_lght->dir.z;
				t_max = 1000000;
			}
			//*
			//shdw = cls_intr(p, l, 0.001, t_max, sph);
			//if (shdw->sph != NULL)
			//{
			//	++j;
			//	continue;
			//}
			n_dot = dot(n, &l);
			if (n_dot > 0)
				ints += (c_lght->ints * n_dot) / (len_vec3(n) * len_vec3(&l));
			if (fg->spec > 0)
			{
				refl_r(&r, &l, n);
				r_dot = dot(&r, v);
				if (r_dot > 0)
				{
					spec = r_dot / (len_vec3(&r) * len_vec3(v));
					spec = pow(spec, fg->spec);
					ints += c_lght->ints * spec;
				}
			}
		}
		c_lght = c_lght->next;
	}
	return (ints);
}