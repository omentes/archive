/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 12:11:36 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/07 12:11:36 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		matrix_fill_one2(t_fill *g) /// best??
{
	int a;
	int b;

	a = 0;
	int c;
	if (g->xo == 'X')
	{
		while (a < g->map_size[0])
		{
			c = g->map_size[1] + g->map_size[0] - a;
			b = 0;
			while (b < g->map_size[1])
			{		
				g->matrix[a][b] = c;
				b++;
				if (c == 0)
					c = 0;
				else
					c--;
			}
			c--;
			a++;
		}
		return ;
	}
	while (a < g->map_size[0])
	{
		b = 0;
		while (b < g->map_size[1])
		{		
			if (a < g->map_size[0] / 2 + 1)
				g->matrix[a][b] = a;
			else
				g->matrix[a][b] = c;
			b++;
		}
		if (a < g->map_size[0] / 2)
			c++;
		else
			c--;
		a++;
	}
}



void		find_lst(t_fill *g)
{
	t_spt	*lstsp;
	int		temp;

	temp = lstsp->summ;
	lstsp = g->spot;
	if (g->xo == 'X')
	{
		while (lstsp)
		{
			if (lstsp->summ > temp)
			{
				g->a_loc = lstsp->locx;
				g->b_loc = lstsp->locy;
			}
			if (lstsp->next)
				lstsp = lstsp->next;
			else
				break ;
		}
		return ;
	}
	while (lstsp)
	{
		if (lstsp->summ <= temp)
		{
			g->a_loc = lstsp->locx;
			g->b_loc = lstsp->locy;
		}
		if (lstsp->next)
			lstsp = lstsp->next;
		else
			break ;
	}
}

void		find_loc(t_fill *g)
{
	t_bit	*p;
	size_t	temp;
	t_spt	*lstsp;

	p = g->next;
	temp = 0;
	g->spot = (t_spt*)malloc(sizeof(t_spt));
	ft_bzero(lstsp, sizeof(t_spt));
	lstsp = g->spot;
	while (p->next)
	{
		if (p->bit_error == 0 && p->my_point == 1)
		{
			if (lstsp->summ != 0)
			{
				lstsp->next = (t_spt*)malloc(sizeof(t_spt));
				dprintf(g->fd, "test\n");
				lstsp = lstsp->next;
				ft_bzero(lstsp, sizeof(t_spt));
				lstsp->next = NULL;	
			}
			lstsp->summ = p->count;
			lstsp->locx = p->ap;
			lstsp->locy = p->bp;
		}
		p = p->next;
	}
	dprintf(g->fd, "-----FIND_LOC------\n");
}
void		print_list(t_fill *g)
{
	t_spt *p;

	p = g->spot;
	dprintf(g->fd, "List: a[%i] b[%i] count[%d]\n", p->locx, p->locy, p->summ);
	while (p->next)
	{
		p = p->next;
		dprintf(g->fd, "List: a[%i] b[%i] count[%d]\n", p->locx, p->locy, p->summ);
	}

}

t_bit		*check_bit_struct(t_bit *tbit, int a, int b)
{
	while (tbit->next)
		tbit = tbit->next;
	if (tbit->ap != a || tbit->bp != b)
	{
		tbit->next = (t_bit*)malloc(sizeof(t_bit));
		tbit->next->ap = a;
		tbit->next->bp = b;
		tbit = tbit->next;
		tbit->next = NULL;
	}
	return (tbit);
}

void		check_bit(t_fill *g, t_bit *tbit, int a, int b)
{
	int i;
	int j;
	t_bit *p;

	p = check_bit_struct(tbit, a, b);
	//dprintf(g->fd, "check_bit a:%i b:%i p->ap:%i p->pb:%i\n", a, b , p->ap, p->bp);
	if (a + g->bit_size[0] <= g->map_size[0] && b + g->bit_size[1] <= g->map_size[1])
	{
		i = 0;
		while (i < g->bit_size[0])
		{
			j = 0;
			while (j < g->bit_size[1])
			{
		//	dprintf(g->fd, "check_bit i:%i j:%i g0:%i g1:%i\n", i, j, g->bit_size[0], g->bit_size[1]);
				if ((g->bit[i][j] != '.' && g->map[a + i][b + j] == g->enemy) ||
				(g->bit[i][j] != '.' && g->map[a + i][b + j] == g->enemy + 32))
					p->bit_error++;
				if (g->bit[i][j] != '.' && g->map[a + i][b + j] == g->xo)
					p->my_point++;
				if (g->bit[i][j] != '.')
					p->count += g->matrix[a + i][b + j];
				j++;
			}
			i++;
		}
	}
	// dprintf(g->fd, "check_bit2\n");
}

void		find_spot(t_fill *g)
{
	int		a;
	int		b;
	size_t	temp;
	t_bit	*tbit;

	a = 0;
	tbit = (t_bit*)malloc(sizeof(t_bit));
	ft_bzero(tbit, sizeof(t_bit));
	g->next = tbit;
	tbit->next = NULL;
	temp = g->xo * g->map_size[1] * g->map_size[0];
	dprintf(g->fd, "find_spot1\n");
	while (a < g->map_size[0])
	{
		b = 0;
		while (b < g->map_size[1])
		{
			//dprintf(g->fd, "fcheck_bit(%i, %i)\n", a, b);
			check_bit(g, tbit, a, b);
			b++;
		}
		a++;
	}
	dprintf(g->fd, "find_spot2\n");
}

void		matrix_map(t_fill *g)
{
	int a;
	int b;

	a = 0;
	g->matrix = (size_t**)malloc(sizeof(size_t*) * g->map_size[0]);
	ft_bzero(g->matrix, sizeof(size_t*) * g->map_size[0]);
	while (a < g->map_size[0])
	{
		g->matrix[a] = (size_t*)malloc(sizeof(size_t) * g->map_size[1]);
		ft_bzero(g->matrix[a], sizeof(size_t) * g->map_size[1]);
		b = 0;
		while (b < g->map_size[1])
		{
			if (g->map[a][b] == '.')
				g->matrix[a][b] = 0;
			else if (g->map[a][b] == g->xo)
				g->matrix[a][b] = g->xo * g->map_size[1] * g->map_size[0];
			else if (g->map[a][b] == g->enemy)
				g->matrix[a][b] = g->enemy * g->map_size[1] * g->map_size[0];
			b++;
		}
		a++;
	}
}

int			fill_point(t_fill *g, size_t *i, int a, int b)
{
	int ret;

	ret = 0;
	if (a - 1 >= 0 && a - g->map_size[0])
	{
		if (g->matrix[a - 1][b] == 0 && ++ret)
			g->matrix[a - 1][b] = (*i) + 1;
		if (b + 1 < g->map_size[1] && g->matrix[a - 1][b + 1] == 0 && ++ret)
			g->matrix[a - 1][b + 1] = (*i) + 1;
		if (b - 1 >= 0 && g->matrix[a - 1][b - 1] == 0  && ++ret)
			g->matrix[a - 1][b - 1] = (*i) + 1;
	}
	if (a + 1 < g->map_size[0])
	{
		if (g->matrix[a + 1][b] == 0 && ++ret)
			g->matrix[a + 1][b] = (*i) + 1;
		if (b + 1 < g->map_size[1] && g->matrix[a + 1][b + 1] == 0 && ++ret)
			g->matrix[a + 1][b + 1] = (*i) + 1;
		if (b - 1 >= 0 && g->matrix[a + 1][b - 1] == 0 && ++ret)
			g->matrix[a + 1][b - 1] = (*i) + 1;
	}
	if (b - 1 >= 0 && g->matrix[a][b - 1] == 0 && ++ret)
		g->matrix[a][b - 1] = (*i) + 1;
	if (b + 1 < g->map_size[1] && g->matrix[a][b + 1] == 0 && ++ret)
		g->matrix[a][b + 1] = (*i) + 1;
	return (ret);
}

void		matrix_fill_two(t_fill *g, size_t *i, char *flag)
{
	int a;
	int b;

	a = 0;
	*flag = 0;
	while (a < g->map_size[0])
	{
		b = 0;
		while (b < g->map_size[1])
		{		
			if (g->matrix[a][b] == *i)
				if (fill_point(g, i, a, b))
					*flag = 1;
			b++;
		}
		a++;
	}
}

void		matrix_fill_one(t_fill *g, size_t *i)
{
	int a;
	int b;

	a = 0;
	while (a < g->map_size[0])
	{
		b = 0;
		while (b < g->map_size[1])
		{		
			if (g->map[a][b] == g->enemy)
				fill_point(g, i, a, b);
			b++;
		}
		a++;
	}
}

void		spot_loc(t_fill *g)
{
	char	flag;
	size_t	i;

	flag = 1;
	i = 1;
	matrix_map(g);
	matrix_fill_one2(g);
	// i++;
	// while (flag)
	// {
	// 	matrix_fill_two(g, &i, &flag);
	// 	i++;
	// }
	dprintf(g->fd, "-----1-----\n");
	for (int i = 0; i < g->map_size[0]; ++i)
	{
		for (int j = 0; j < g->map_size[1]; ++j)
			dprintf(g->fd, "%zu ", g->matrix[i][j]);
		dprintf(g->fd, "\n");
	}
	dprintf(g->fd, "-----2------\n");
	find_spot(g);
	find_loc(g);
	print_list(g);
	find_lst(g);
	dprintf(1, "%i %i\n", g->a_loc, g->b_loc);
	dprintf(g->fd, "<got (%c): [%i, %i]\n", g->xo, g->a_loc, g->b_loc);
}

// void		wait_enemy(t_fill *g)
// {
// 	char	*line;
// 	int 	w;
	
// 	w = g->map_size[0] + 2;
// 	while (w--)
// 	{
// 		get_next_line(STDIN_FILENO, &line);
// 		dprintf(g->fd, "::::%s\n", line);	// ft_strdel(&line);
// 		// ft_strdel(&line);
// 	}
// }
