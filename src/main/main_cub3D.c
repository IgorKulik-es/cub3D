/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:17 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 12:19:39 by ikulik           ###   ########.fr       */
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
	load_doors(&game);
	load_animations(&game);
	create_screen(&game);
	setup_textures(&game);
	mlx_do_key_autorepeatoff(game.mlx);
	game.player.camera = mult_scalar(game.player.camera, P_POV);
	//mlx_mouse_hide(game.mlx, game.win);
	mlx_hook(game.win, MotionNotify, PointerMotionMask, mouse_move, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_hook(game.win, DestroyNotify, NoEventMask, close_game, &game);
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
