/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 23:32:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/23 13:25:50 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		validate_input(char	*argv);
void	exit_failure(char *s);
int		get_fractal_type(t_game *game, char *argv);
int		stop_game(t_game *game);

int		main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		exit_failure("Specify whether you want the 'julia'/'mandelbrot' set.");
	if (validate_input(argv[1]) == -1)
		exit_failure("Specify whether you want the 'julia'/'mandelbrot' set.");
	game = ft_calloc(1, sizeof(t_game));
	if (!(game))
		exit_failure("Could not allocate memory for the game struct.");
	get_fractal_type(game, argv[1]);
	//ft_putnbr_fd(game->fractal.type, 2);
	game->mlx.instance = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.instance, 800, 600, "fract-ol");
	mlx_clear_window(game->mlx.instance, game->mlx.win);
	game->mlx.img = mlx_new_image(game->mlx.instance, 800, 600);
	mlx_hook(game->mlx.win, 17, 0L, stop_game, game);
	mlx_loop(game->mlx.instance);
	return (0);
}

int		stop_game(t_game *game)
{
	mlx_destroy_window(game->mlx.instance, game->mlx.win);
	exit(EXIT_SUCCESS);
	return (1);
}

int		init_fractal(t_game *game)
{
	game->fractal.colors.red = 0xFF0000;
	game->fractal.colors.green = 0x00FF00;
	game->fractal.colors.blue = 0x0000FF;
	return (0);
}

int		get_fractal_type(t_game *game, char *argv)
{
	if (ft_strncmp("mandelbrot", argv, ft_strlen("mandelbrot")) == 0)
		game->fractal.type = 1;
	else if (ft_strncmp("julia", argv, ft_strlen("julia")) == 0)
		game->fractal.type = 2;
	else
	{
		exit_failure("Could not configure chosen fractal");
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

void	exit_failure(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	//system("leaks fract-ol");
	exit (EXIT_FAILURE);
}
