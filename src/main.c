/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 23:32:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/22 23:46:42 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		exit_failure("Specify whether you want the Julia or Mandelbrot set.")
		

	game = ft_calloc(1, sizeof(t_game));
	if (!(game))
		exit_failure("Could not allocate memory for the game struct.");

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
