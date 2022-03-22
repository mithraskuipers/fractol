/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 23:32:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/22 23:58:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if ((argc != 2) || (validate_input(argv[1] == -1)))
		exit_failure("Specify whether you want the 'julia'/'mandelbrot' set.");
	game = ft_calloc(1, sizeof(t_game));
	if (!(game))
		exit_failure("Could not allocate memory for the game struct.");
	game->mlx.instance = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.instance, 800, 600, "fract-ol");
	return (0);
}

int	validate_input(char	*argv)
{
	if (!ft_strncmp("mandelbrot", argv, ft_strlen("mandelbrot")))
		return (-1);
	if (!ft_strncmp("julia", argv, ft_strlen("julia")))
		return (-1);
	return (0);
}

void	exit_failure(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	system("leaks fract-ol");
	exit (EXIT_FAILURE);
}
