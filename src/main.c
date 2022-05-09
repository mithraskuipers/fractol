/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 23:32:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/05/09 14:32:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	mandelbrot(t_env *env, int row, int col)
{
	;
}

void	pixel_loop(t_env *env, void (*f)())
{
	int	row;
	int	col;

	row = 0;
	while (row < HEIGHT)
	{
		col = 0;
		while (col < WIDTH)
		{
			f(env, row, col);
			col++;
		}
		row++;
	}
}

int		main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		exit_failure("Specify whether you want the 'julia'/'mandelbrot' set.");
	if (validate_input(argv[1]) == -1)
		exit_failure("Specify whether you want the 'julia'/'mandelbrot' set.");
	env = ft_calloc(1, sizeof(t_env));
	if (!(env))
		exit_failure("Could not allocate memory for the env struct.");
	get_fractal_type(env, argv[1]);
	//ft_putnbr_fd(env->fractal.type, 2);

	env->mlx.instance = mlx_init();
	env->mlx.win = mlx_new_window(env->mlx.instance, 800, 600, "fract-ol");
	//mlx_clear_window(env->mlx.instance, env->mlx.win);
	//env->mlx.img = mlx_new_image(env->mlx.instance, 800, 600);
	mlx_hook(env->mlx.win, 17, 0L, stop_env, env);
	init_fractal(env);
	mlx_pixel_put(env->mlx.instance, env->mlx.win, 30, 30, env->fractal.colors.red);
	mlx_loop(env->mlx.instance);
	return (0);
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
	{
		exit_failure("Could not configure chosen fractal", EXIT_FAILURE);
		return (1);
	}
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
