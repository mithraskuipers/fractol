/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 23:32:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/05/10 14:16:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

# include <math.h>

int		validate_input(char	*argv);
void	exit_failure(char *s, int exit_code);
int		get_fractal_type(t_env *env, char *argv);
int		stop_env(t_env *env);

int		init_fractal(t_env *env)
{
	env->fractal.colors.red = 0x00FF0000;
	env->fractal.colors.green = 0x00FF00;
	env->fractal.colors.blue = 0x0000FF;
	return (0);
}

//void	pixel_loop(t_env *env, void (*f)())



void	pixel_loop(t_env *env)
{


	double MinRe = -2.0;
	double MaxRe = 1.0;
	double MinIm = -1.2;
	double MaxIm = 1.2;
	//double MaxIm = MinIm+(MaxRe-MinRe)*HEIGHT/WIDTH;
	unsigned MaxIterations = 100;
	double c_im;

	int	y;
	int x;
	double Z_re2;
	double Z_im2;
	double Z_re;
	double Z_im;
	y = 0;
	while (y < HEIGHT)
	{
		c_im = MaxIm - y * (MaxIm - MinIm) / (HEIGHT - 1);

		x = 0;
		while (x < WIDTH)
		{
			double c_re = MinRe + x * ((MaxRe-MinRe)/(WIDTH - 1));

			Z_re = c_re;
			Z_im = c_im;
			int isInside = 1;
			for(unsigned n = 0; n < MaxIterations; ++n)
			{
				if(sqrt(Z_re * Z_re + Z_im * Z_im) > 2)
				{
					isInside = 0;
					break;
				}
				Z_re2 = Z_re * Z_re;
				Z_im2 = Z_im * Z_im;
				Z_im = 2 * Z_re * Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
			}
			if(isInside) 
				mlx_pixel_put(env->mlx.instance, env->mlx.win, x, y, env->fractal.colors.blue);
			x++;
		}
		y++;
	}

}

int		stop_env(t_env *env)
{
	mlx_destroy_window(env->mlx.instance, env->mlx.win);
	exit(EXIT_SUCCESS);
	return (1);
}

// 1 is mandelbrot
// 2 is julia

int		get_fractal_type(t_env *env, char *argv)
{
	if (ft_strncmp("mandelbrot", argv, ft_strlen("mandelbrot")) == 0)
		env->fractal.type = 1;
	else if (ft_strncmp("julia", argv, ft_strlen("julia")) == 0)
		env->fractal.type = 2;
	else
		exit_failure("Could not configure chosen fractal", EXIT_FAILURE);
	return (0);
}

int		validate_input(char	*s)
{
	if ((ft_strncmp("mandelbrot", s, ft_strlen("mandelbrot")) == 0) && \
	ft_strlen("mandelbrot") == ft_strlen(s))
		return (0);
	if ((ft_strncmp("julia", s, ft_strlen("julia")) == 0) && \
	ft_strlen("julia") == ft_strlen(s))
		return (0);
	return (-1);
}

void	exit_failure(char *s, int exit_code)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	//system("leaks fract-ol");
	exit (exit_code);
}



int		main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		exit_failure("Specify whether you want the 'julia'/'mandelbrot' set.", EXIT_FAILURE);
	if (validate_input(argv[1]) == -1)
		exit_failure("Specify whether you want the 'julia'/'mandelbrot' set.", EXIT_FAILURE);
	env = ft_calloc(1, sizeof(t_env));
	if (!(env))
		exit_failure("Could not allocate memory for the env struct.", EXIT_FAILURE);
	get_fractal_type(env, argv[1]);
	//ft_putnbr_fd(env->fractal.type, 2);
	env->mlx.instance = mlx_init();
	env->mlx.win = mlx_new_window(env->mlx.instance, 800, 600, "fract-ol");
	//mlx_clear_window(env->mlx.instance, env->mlx.win);
	//env->mlx.img = mlx_new_image(env->mlx.instance, 800, 600);
	mlx_hook(env->mlx.win, 17, 0L, stop_env, env);
	init_fractal(env);
	pixel_loop(env);
	//mlx_pixel_put(env->mlx.instance, env->mlx.win, 30, 30, env->fractal.colors.red);
	mlx_loop(env->mlx.instance);
	return (0);
}


/*
x-axis:
	dimension of real numbers
y-axis:
	dimension of imaginary numbers

All parts of the Mandelbrot set are within this frame.

http://warp.povusers.org/Mandelbrot/
*/