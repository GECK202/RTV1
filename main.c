/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:24:06 by vabraham          #+#    #+#             */
/*   Updated: 2019/11/15 14:24:08 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		kp(int key, void *l)
{
	t_lst	*lst;

	lst = (t_lst*)l;
	printf("%d\n", key);
	if (key == 53)
		exit(1);
	else if (key == 123)
		lst->x -= 1;
	else if (key == 124)
		lst->x += 1;
	else if (key == 125)
		lst->y -= 1;
	else if (key == 126)
		lst->y += 1;
	else if (key == 0)
		lst->z -= 1;
	else if (key == 2)
		lst->z += 1;
	else if (key == 13)
		lst->r += 1;
	else if (key == 1)
		lst->r -= 1;
	else if (key == 34)
		lst->l1 -= 5;
	else if (key == 31)
		lst->l1 += 5;
	else if (key == 40)
		lst->l2 -= 5;
	else if (key == 37)
		lst->l2 += 5;
	else if (key == 47)
		lst->l3 -= 5;
	else if (key == 43)
		lst->l3 += 5;
	pixel(lst);
	mlx_put_image_to_window(lst->mlx, lst->win, lst->img, 0, 0);
	return (0);
}

int		close_my(void *lst)
{
	(void)lst;
 	exit(0);
}

// float	color(t_lst *lst, float a, float b, float c, float x, float y, float z)
// {
// 	float n1 = (x + a);
// 	float n2 = (y + b);
// 	float n3 = (z + c);
// 	float len = sqrt(n1 * n1 + n2 * n2 + n3 * n3);
// 	n1 /= len;
// 	n2 /= len;
// 	n3 /= len;
// 	float l1 = lst->l1;
// 	float l2 = lst->l2;
// 	float l3 = lst->l3;
// 	float lv1 = (l1 - x);
// 	float lv2 = (l2 - y);
// 	float lv3 = (l3 - z);
// 	float distance = sqrt(lv1 * lv1 + lv2 * lv2 + lv3 * lv3);
// 	len = sqrt(lv1 * lv1 + lv2 * lv2 + lv3 * lv3);
// 	lv1 /= len;
// 	lv2 /= len;
// 	lv3 /= len;
// 	float diffuse = n1 * lv1 + n2 * lv2 + n3 * lv3;
// 	if (diffuse < 0)
// 		diffuse = 0;
// 	if (distance / 80 < 1)
// 		distance = 80;
// 	diffuse *= 1 / (distance / 80);//0.6;
// 	return (diffuse + 0);
// }

int		ray(t_lst *lst, float x, float y, float z)
{
	float t1;
	float t2;
	float k1;
	float k2;
	float k3;
	float d;
	float len;
	float col;
	t_fig *fig;
	t_fig *fig0;

	t_vec3 pos;
	t_vec3 normal;
	t_vec3 minvec;

	fig = lst->scn->figs;
	float a = fig->pos.x;
	float b = fig->pos.y;
	float c = fig->pos.z;
	float r = fig->rad;

	t1 = -1;
	t2 = -1;
	float check = 1;
	while (fig)
	{
		a = -fig->pos.x;
		b = -fig->pos.y;
		c = -fig->pos.z;
		r = fig->rad;

		k1 = x * x + y * y + z * z;
		k2 = a * x + b * y + c * z;
		k3 = a * a + b * b + c * c - r * r;
		d = k2 * k2 - k1 * k3;
		if (d >= 0 && 
		(((-k2 + sqrt(d)) / k1 > 1 && (check || (-k2 + sqrt(d)) / k1 < t1 || (-k2 + sqrt(d)) / k1 < t2)) ||
		((-k2 - sqrt(d)) / k1 > 1 && (check || (-k2 - sqrt(d)) / k1 < t1 || (-k2 - sqrt(d)) / k1 < t2))))
		{
			fig0 = fig;
			check = 0;
			t1 = (-k2 + sqrt(d)) / k1;
			t2 = (-k2 - sqrt(d)) / k1;
		}
		fig = fig->next;
	}

	len = sqrt(x * x + y * y + z * z);
	minvec.x = -x / len;
	minvec.y = -y / len;
	minvec.z = -z / len;
	// color(lst, &pos, &normal, &minvec, fig0);
	if (t1 < t2 && t1 > 1)
	{
		pos.x = x * t1;
		pos.y = y * t1;
		pos.z = z * t1;
		len = sqrt(pow(pos.x + a, 2) + pow(pos.y + b, 2) + pow(pos.z + c, 2));
		normal.x = (pos.x + a) / len;
		normal.y = (pos.y + b) / len;
		normal.z = (pos.z + c) / len;
		return ((int)(0xFF * color(lst, &pos, &normal, &minvec, fig0)));//color(lst, a, b, c, x * t1, y * t1, z * t1)) << 0);
	}
	else if (t2 > 1)
	{
		pos.x = x * t2;
		pos.y = y * t2;
		pos.z = z * t2;
		len = sqrt(pow(pos.x + a, 2) + pow(pos.y + b, 2) + pow(pos.z + c, 2));
		normal.x = (pos.x + a) / len;
		normal.y = (pos.y + b) / len;
		normal.z = (pos.z + c) / len;
		return ((int)(0xFF * color(lst, &pos, &normal, &minvec, fig0)));//color(lst, a, b, c, x * t2, y * t2, z * t2)) << 0);
	}
	return (0);
}

// int		ray(t_lst *lst, float x, float y, float a, float b, float c, float r)
// {
// 	float t1;
// 	float t2;
// 	float k1;
// 	float k2;
// 	float k3;
// 	float z;
// 	float d;

// 	z = 2;
// 	k1 = x * x + y * y + z * z;
// 	k2 = x * lst->l1 + y * lst->l2 + z * lst->l3;
// 	k3 = lst->l1 * lst->l1 + lst->l2 * lst->l2 + lst->l3 * lst->l3 - 0.5;
// 	d = k2 * k2 - k1 * k3;
// 	if (d > 0)
// 		return (0xFFFFFF);
// 	k2 = a * x + b * y + c * z;
// 	k3 = a * a + b * b + c * c - r * r;
// 	d = k2 * k2 - k1 * k3;
// 	if (d < 0)
// 		return (0);
// 	t1 = (-k2 + sqrt(d)) / k1;
// 	t2 = (-k2 - sqrt(d)) / k1;

// 	if (t1 > 1 && t2 > 1)
// 	{
// 		if (t1 < t2)
// 			return ((int)(0xFF * color(lst, a, b, c, x * t1, y * t1, z * t1)) << 0);
// 		else
// 			return ((int)(0xFF * color(lst, a, b, c, x * t2, y * t2, z * t2)) << 0);
// 	}
// 	return (0);
// }

void	pixel(t_lst *lst)
{
	int i;
	int j;

	i = -WIDTH / 2 - 1;
	while (++i < WIDTH / 2)
	{
		j = -HEIGHT / 2 - 1;
		while (++j < HEIGHT / 2)
		{
			// printf("i = %d    j = %d\n", i, j);
			// ft_putnbr((i) * (j));
			lst->data[(i + WIDTH / 2) * WIDTH + j + HEIGHT / 2] = ray(lst, (float)j / (WIDTH / 2), (float)i / (HEIGHT / 2), 1);
		}
	}
}

int		mm(int x, int y, void *l)
{
	t_lst *lst;

	lst = (t_lst*)l;
	if (!lst->change)
		return (0);
	lst->scn->lghts->pos.x = ((float)x - WIDTH / 2) / (WIDTH / 2) * (lst->scn->lghts->pos.z / 2);
	lst->scn->lghts->pos.y = ((float)y - HEIGHT / 2) / (HEIGHT / 2) * (lst->scn->lghts->pos.z / 2);
	pixel(lst);
	mlx_put_image_to_window(lst->mlx, lst->win, lst->img, 0, 0);
	return (0);
}

int		mp(int b, int x, int y, void *l)
{
	t_lst *lst;

	lst = (t_lst*)l;
	if (b == 4)
	{
		lst->scn->lghts->pos.z += 3;
		lst->scn->lghts->pos.x = ((float)x - WIDTH / 2) / (WIDTH / 2) * (lst->scn->lghts->pos.z / 2);
		lst->scn->lghts->pos.y = ((float)y - HEIGHT / 2) / (HEIGHT / 2) * (lst->scn->lghts->pos.z / 2);
	}
	else if (b == 5)
	{
		lst->scn->lghts->pos.z -= 3;
		lst->scn->lghts->pos.x = ((float)x - WIDTH / 2) / (WIDTH / 2) * (lst->scn->lghts->pos.z / 2);
		lst->scn->lghts->pos.y = ((float)y - HEIGHT / 2) / (HEIGHT / 2) * (lst->scn->lghts->pos.z / 2);
	}
	else if (b == 1 && lst->change)
		lst->change = 0;
	else if (b == 1)
		lst->change = 1;
	pixel(lst);
	mlx_put_image_to_window(lst->mlx, lst->win, lst->img, 0, 0);
	return (0);
}

int		main()
{
	t_lst	*lst;

	lst = malloc(sizeof(t_lst));
	lst->mlx = mlx_init();
	lst->win = mlx_new_window(lst->mlx, WIDTH, HEIGHT, "RTV1");
	lst->img = mlx_new_image(lst->mlx, WIDTH, HEIGHT);
	lst->data = (int *)mlx_get_data_addr(lst->img,
		&(lst->n0), &(lst->n1), &(lst->n2));
	mlx_hook(lst->win, 2, 0, kp, (void *)lst);
	mlx_hook(lst->win, 17, 0, close_my, (void *)0);
	mlx_hook(lst->win, 6, 0, mm, (void *)lst);
	mlx_hook(lst->win, 4, 0, mp, (void *)lst);

	lst->scn = malloc(sizeof(t_scn));
	lst->scn->figs = malloc(sizeof(t_fig));
	lst->scn->figs->next = NULL;
	lst->scn->figs->type = sphere;
	lst->scn->figs->pos.x = 0;
	lst->scn->figs->pos.y = 0;
	lst->scn->figs->pos.z = 120;
	lst->scn->figs->rad = 25;
	lst->scn->figs->spec = 500;

	lst->scn->lghts = malloc(sizeof(t_lght));
	lst->scn->lghts->type = point;
	lst->scn->lghts->pos.x = 0;
	lst->scn->lghts->pos.y = 0;
	lst->scn->lghts->pos.z = -100;
	lst->scn->lghts->ints = 1;
	lst->scn->lghts->next = NULL;

	// lst->scn->figs->next = malloc(sizeof(t_fig));
	// lst->scn->figs->next->next = NULL;
	// lst->scn->figs->next->type = sphere;
	// lst->scn->figs->next->pos.x = 50;
	// lst->scn->figs->next->pos.y = 50;
	// lst->scn->figs->next->pos.z = 120;
	// lst->scn->figs->next->rad = 25;

	lst->x = 00;
	lst->y = 0;
	lst->z = 120;
	lst->r = 25;
	lst->l1 = 0;
	lst->l2 = 0;
	lst->l3 = 70;
	lst->change = 0;
	pixel(lst);
	mlx_put_image_to_window(lst->mlx, lst->win, lst->img, 0, 0);
	mlx_loop(lst->mlx);
	return (0);
}
