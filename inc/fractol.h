/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 13:13:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/23 12:44:25 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

// VERWIJDER?
# define KEY_UP 13
# define KEY_DOWN 1
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define RESET 15
# define ESC 53

typedef struct s_mlx
{
	void		*instance;
	void		*win;
	void		*img;
}				t_mlx;

typedef struct s_colors
{
	int		red;
	int		green;
	int		blue;
}				t_colors;

typedef struct s_fractal
{
	int			type;
	t_colors	colors;
}				t_fractal;

typedef struct s_game
{
	t_mlx		mlx;
	t_fractal	fractal;
}				t_game;

#endif
