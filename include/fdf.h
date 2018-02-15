/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:51:23 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/30 15:51:23 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/include/libft.h"
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>


typedef struct	s_mlx
{
	void			*mlx;
	void			*win;
	int				window;
	unsigned long	fill;
	int				fd;
	char			*str;
}				t_mlx;

#endif
