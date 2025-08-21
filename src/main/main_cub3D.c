/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:17 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/21 17:26:59 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int		dummy;

	(void)argv;
	(void)argc;
	initialize_data(&game);
	create_dummy_map(&game);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	game.screen.img = mlx_new_image(game.mlx, game.screen.win_w, game.screen.win_h);
	game.screen.pixels = (int *)mlx_get_data_addr(game.screen.img, &dummy, &dummy, &dummy);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 0, key_release, &game);
	mlx_hook(game.win, 17, 0L, close_game, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
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
