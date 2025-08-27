/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:17 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/27 20:14:53 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_arguments(int argc);

int	main(int argc, char **argv)
{
	t_game	game;

	check_arguments(argc);
	initialize_data(&game);
	game.mlx = mlx_init();
	if (parse_cub(&game, argv[1]))
		return (1);
	count_doors(&game);
	add_doors(&game);
	create_screen(&game);
	mlx_do_key_autorepeatoff(game.mlx);
	game.player.camera = mult_scalar(game.player.camera, P_POV);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0L, close_game, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
}

static void	check_arguments(int argc)
{
	if (argc < 2)
	{
		printf("Error: no map file.\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		printf("Error: too many arguments.\n");
		exit(EXIT_FAILURE);
	}
	else
		return ;
}
//for map viewing and debug purposes
//
/* void	print_map(char **arr, int height)
{
	int	index;

	index = 0;
	if (arr == NULL)
		return ;
	while (index < height)
	{
		write(1, arr[index], ft_strlen(arr[index]));
		write(1, "\n", 1);
		index++;
	}
} */
